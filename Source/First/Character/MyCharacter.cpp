// Fill out your copyright notice in the Description page of Project Settings.

#include "MyCharacter.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    CharCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    CharCamera->SetupAttachment(RootComponent);
    CharCamera->bUsePawnControlRotation = true;
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();

}

void AMyCharacter::Landed(const FHitResult & Hit)
{
    Super::Landed(Hit);
    //UE_LOG(LogTemp, Warning, TEXT("Timer: %f"), timer);
    float speed = -(GetCharacterMovement()->Velocity.Z);

    if (speed > JumpHight && bHealthDriver.CurHealth)
    {
        SetDamage((speed - JumpHight) / FallSpeed);
    }
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if (bHealthDriver.Timer == 0.f)
    {
        if (bHealthDriver.CurHealth < bHealthDriver.CurHealthDropEffect)
        {
            bHealthDriver.CurHealthDropEffect -= DeltaTime;

            if (bHealthDriver.CurHealth > bHealthDriver.CurHealthDropEffect)
                bHealthDriver.CurHealthDropEffect = bHealthDriver.CurHealth;
        }
    }
    else if (bHealthDriver.Timer > 0.f)
    {
        bHealthDriver.Timer -= DeltaTime;

        if (bHealthDriver.Timer < 0.f)
            bHealthDriver.Timer = 0.f;
    }

    //DrawDebugCapsule(GetWorld(), GetActorLocation(), GetCapsuleComponent()->GetScaledCapsuleHalfHeight(), GetCapsuleComponent()->GetScaledCapsuleRadius(), GetCapsuleComponent()->GetComponentQuat(), FColor::Blue);
}

void AMyCharacter::SmartJump()
{
    GetCharacterMovement()->SetMovementMode(MOVE_Falling);

    TArray<AActor*> targets;
    UGameplayStatics::GetAllActorsWithTag(this, FName("111"), targets);

    FVector FillTarget;
    float MaxFill = -2.f;
    FVector Dir = CharCamera->GetForwardVector();

    for (auto itr : targets)
    {
        FVector const& targetLoc = itr->GetActorLocation();
        FVector Offset = targetLoc - CharCamera->GetComponentLocation();
        Offset = Offset.GetSafeNormal();
        float curAngle = FVector::DotProduct(Dir, Offset);

        if (curAngle > MaxFill)
        {
            MaxFill = curAngle;
            FillTarget = targetLoc;
        }
    }

    if (!FillTarget.IsZero())
    {
        FVector actorLoc = GetActorLocation();
        float bonusHeight = 800.f;
        float landSpeed = 980.f;
        float time = 1.f;
        float startSpeedZ = 0.f;

        if (FillTarget.Z >= actorLoc.Z)
        {
            float height = FillTarget.Z + bonusHeight - actorLoc.Z;
            startSpeedZ = FMath::Sqrt(2.f * landSpeed * height);
            time = startSpeedZ / landSpeed + FMath::Sqrt((2.f * bonusHeight) / landSpeed);
        }
        else
        {
            startSpeedZ = FMath::Sqrt(2.f * landSpeed * bonusHeight);
            time = startSpeedZ / landSpeed;
            float landSpeedCap = 4000.000244f;
            float distBeforeCap = ((landSpeedCap / landSpeed) * landSpeedCap) / 2.f;
            float height = actorLoc.Z + bonusHeight - FillTarget.Z;

            if (height > distBeforeCap)
            {
                height -= distBeforeCap;
                time += landSpeedCap / landSpeed;
                time += height / landSpeedCap;
            }
            else
            {
                time += FMath::Sqrt(2.f * height / landSpeed);
            }
        }

        FillTarget.X = (FillTarget.X - actorLoc.X) / time;
        FillTarget.Y = (FillTarget.Y - actorLoc.Y) / time;
        GetCharacterMovement()->Velocity = FVector(FillTarget.X, FillTarget.Y, startSpeedZ);
    }
}

void AMyCharacter::SetDamage(float damage)
{
    if (bHealthDriver.CurHealth && bHealthDriver.CurHealth == bHealthDriver.CurHealthDropEffect && !bHealthDriver.Timer)
        bHealthDriver.Timer = HealthDropEffectTimer;

    bHealthDriver.CurHealth -= damage;

    if (bHealthDriver.CurHealth < 0.f)
        bHealthDriver.CurHealth = 0.f;
}

void AMyCharacter::HandleDamage()
{
    SetDamage();
}

void AMyCharacter::RestoreHealth()
{
    bHealthDriver.CurHealth = 1.f;
    bHealthDriver.CurHealthDropEffect = 1.f;
}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

    check(PlayerInputComponent);
    PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
    PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
    PlayerInputComponent->BindAxis("MoveForward", this, &AMyCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &AMyCharacter::MoveRight);

    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMyCharacter::Jump);
    PlayerInputComponent->BindAction("Jump", IE_Released, this, &AMyCharacter::StopJumping);

    PlayerInputComponent->BindAction("SmartJump", IE_Pressed, this, &AMyCharacter::SmartJump);
    PlayerInputComponent->BindAction("HandleDamage", IE_Pressed, this, &AMyCharacter::HandleDamage);
        PlayerInputComponent->BindAction("RestoreHealth", IE_Pressed, this, &AMyCharacter::RestoreHealth);
}

void AMyCharacter::MoveForward(float Value)
{
    if (Value != 0.f)
    {
        AddMovementInput(GetActorForwardVector(), Value);
    }
}

void AMyCharacter::MoveRight(float Value)
{
    if (Value != 0.f)
    {
        AddMovementInput(GetActorRightVector(), Value);
    }
}

FHealthDriver::FHealthDriver()
{
    CurHealth = 1.f;
    CurHealthDropEffect = 1.f;
    Timer = 0.f;
}

float AMyCharacter::GetHealth()
{
    return bHealthDriver.CurHealth;
}

float AMyCharacter::GetHealthDropEffect()
{
    return bHealthDriver.CurHealthDropEffect;
}
