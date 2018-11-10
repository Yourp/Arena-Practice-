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
    //FVector(800.f, 80.f, 600.f)
	Super::BeginPlay();
//     UPawnMovementComponent* dasd = GetMovementComponent();
//     dasd->Velocity += FVector(800.f, 80.f, 1800.f) - GetActorLocation();

    //FRotator NewRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), FVector(800.f, 80.f, 600.f));

//     UPawnMovementComponent* dasd = GetMovementComponent();
//     FVector point = FVector(800.f, 80.f, 600.f);
//     FVector actorLoc = GetActorLocation();
// 
//     //float dist = FVector::Distance(point, actorLoc);
//     //         magnet.X /= 40;
//     //         magnet.Y /= 40;
//     //         magnet.Z /= 15;
//     //point.Z /= 5;
// 
// 
//     dasd->Velocity = FVector(1000.f, 1000.f, 1000);
    //PrimaryActorTick.TickInterval = 1.f;
}

void AMyCharacter::Landed(const FHitResult & Hit)
{
    Super::Landed(Hit);
    //UE_LOG(LogTemp, Warning, TEXT("Timer: %f"), timer);
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
// 
//     if (LandTarget != nullptr)
//     {
//         timer += DeltaTime;
//         FVector point = LandTarget->GetActorLocation();
//         FVector actorLoc = GetActorLocation();
//         float curDist = FVector::Dist2D(point, actorLoc);
//         
//         UE_LOG(LogTemp, Warning, TEXT("timer: %f"), timer);
//         if (curDist > maxDist2D)
//         {
//             UE_LOG(LogTemp, Warning, TEXT("timer: %f"), timer);
//             LandTarget = nullptr;
//             return;
//         }
//         maxDist2D = curDist;
// //         if (FVector::Distance(point, actorLoc) < 1100.f)
// //         {
// //             LandTarget = nullptr;
// //             UE_LOG(LogTemp, Warning, TEXT("Sync OFF"));
// //         }
// //         float DistPct = 1.f - (curDist / maxDist2D);
// //         float curZMastBe = 0;
// // 
// //         FVector vel = GetCharacterMovement()->Velocity;
// // 
// //         if (DistPct < 0.5f)
// //         {
// //             DistPct *= 2.f;
// //             curZMastBe = ((maxJumpZ - startZ) * DistPct) + startZ;
// //         }
// //         else
// //         {
// //             DistPct -= 0.5f;
// //             DistPct *= 2.f;
// //             curZMastBe = ((point.Z - maxJumpZ) * DistPct) + maxJumpZ;
// //         }
// //         float finalZ = curZMastBe - actorLoc.Z;
// // 
// //         GetCharacterMovement()->Velocity.Z += finalZ;
// // 
// // //         FVector vel = GetCharacterMovement()->Velocity;
// // // 
// // // //         if (FVector::Distance(point, actorLoc) < 500.f)
// // // //         {
// // // //             LandTarget = nullptr;
// // // //             UE_LOG(LogTemp, Warning, TEXT("Sync OFF"));
// // // //         }
// // // 
// // //         FVector realVect = point - actorLoc;
// // //         FVector diff = vel - realVect;
// // // 
// // //         float modXY = 0.03f;
// // //         diff.X *= modXY;
// // //         diff.Y *= modXY;
// // // // 
// // // //         if (realVect.Z >= 0.f)
// // // //         {
// // // //             diff.Z *= 0.0001f;
// // // //         }
// // // //         else
// // // //             diff.Z = 0.f;
// // // //         
// // // //         GetCharacterMovement()->Velocity -= diff;
// // //         GetCharacterMovement()->Velocity.X -= diff.X;
// // //         GetCharacterMovement()->Velocity.Y -= diff.Y;
//     }
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
        float bonusHeight = 800.f/* + FVector::Dist2D(point, actorLoc) / 3.f*/;
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
        //GetCharacterMovement()->Velocity = FVector(0, 0, 1000);
        GetCharacterMovement()->Velocity = FVector(FillTarget.X, FillTarget.Y, startSpeedZ);
    }
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
}

void AMyCharacter::MoveForward(float Value)
{
    if (Value != 0.f)
    {
        AddMovementInput(GetActorForwardVector(), Value);
    }
    //GetMovementBase()->SetAllPhysicsLinearVelocity(FVector(0.f, 0.f, 2000.f));

//     if (Value != 0.0f)
//     {
//         // find out which way is forward
//         const FRotator Rotation = GetControlRotation();
//         const FRotator YawRotation(0, Rotation.Yaw, 0);
// 
//         // get forward vector
//         const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
//         AddMovementInput(Direction, Value);
//     }
}

void AMyCharacter::MoveRight(float Value)
{
    if (Value != 0.f)
    {
        AddMovementInput(GetActorRightVector(), Value);
    }
}

// void AMyCharacter::SmartJump()
// {
//     if (fCurveZ)
//     {
//         //FVector point = FVector(950.f, 8980.f, 50240.f);
// 
//         GetCharacterMovement()->SetMovementMode(MOVE_Falling);
// 
//         TArray<AActor*> targets;
//         UGameplayStatics::GetAllActorsWithTag(this, FName("111"), targets);
// 
//         for (auto itr : targets)
//         {
//             FVector point = itr->GetActorLocation();
//             FVector actorLoc = GetActorLocation();
// 
//             point -= actorLoc;
//             point.X /= 2;
//             point.Y /= 2;
// 
//             if (point.Z < 0.f)
//                 point.Z = 0.f;
// 
//             UE_LOG(LogTemp, Warning, TEXT("Z: %f"), point.Z);
//             point.Z /= fCurveZ->GetFloatValue(point.Z);
// 
//             point.Z += 800.f;
// 
//             GetCharacterMovement()->Velocity = FVector(point.X, point.Y, point.Z);
//             return;
//         }
//     }
// }

// AMyProjectCharacter::AMyProjectCharacter()
// {
//     // Set size for collision capsule
//     GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
// 
//     // set our turn rates for input
//     BaseTurnRate = 45.f;
//     BaseLookUpRate = 45.f;
// 
//     // Don't rotate when the controller rotates. Let that just affect the camera.
//     bUseControllerRotationPitch = false;
//     bUseControllerRotationYaw = false;
//     bUseControllerRotationRoll = false;
// 
//     // Configure character movement
//     GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
//     GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
//     GetCharacterMovement()->JumpZVelocity = 600.f;
//     GetCharacterMovement()->AirControl = 0.2f;
// 
//     // Create a camera boom (pulls in towards the player if there is a collision)
//     CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
//     CameraBoom->SetupAttachment(RootComponent);
//     CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
//     CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller
// 
//                                                 // Create a follow camera
//     FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
//     FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
//     FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
// 
//                                                    // Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
//                                                    // are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
// }
// 
// //////////////////////////////////////////////////////////////////////////
// // Input
// 
// void AMyProjectCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
// {
//     // Set up gameplay key bindings
//     check(PlayerInputComponent);
//     PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
//     PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
// 
//     PlayerInputComponent->BindAxis("MoveForward", this, &AMyProjectCharacter::MoveForward);
//     PlayerInputComponent->BindAxis("MoveRight", this, &AMyProjectCharacter::MoveRight);
// 
//     // We have 2 versions of the rotation bindings to handle different kinds of devices differently
//     // "turn" handles devices that provide an absolute delta, such as a mouse.
//     // "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
//     PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
//     PlayerInputComponent->BindAxis("TurnRate", this, &AMyProjectCharacter::TurnAtRate);
//     PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
//     PlayerInputComponent->BindAxis("LookUpRate", this, &AMyProjectCharacter::LookUpAtRate);
// 
//     // handle touch devices
//     PlayerInputComponent->BindTouch(IE_Pressed, this, &AMyProjectCharacter::TouchStarted);
//     PlayerInputComponent->BindTouch(IE_Released, this, &AMyProjectCharacter::TouchStopped);
// 
//     // VR headset functionality
//     PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &AMyProjectCharacter::OnResetVR);
// }
// 
// 
// void AMyProjectCharacter::OnResetVR()
// {
//     UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
// }
// 
// void AMyProjectCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
// {
//     Jump();
// }
// 
// void AMyProjectCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
// {
//     StopJumping();
// }
// 
// void AMyProjectCharacter::TurnAtRate(float Rate)
// {
//     // calculate delta for this frame from the rate information
//     AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
// }
// 
// void AMyProjectCharacter::LookUpAtRate(float Rate)
// {
//     // calculate delta for this frame from the rate information
//     AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
// }
// 
// void AMyProjectCharacter::MoveForward(float Value)
// {
//     if ((Controller != NULL) && (Value != 0.0f))
//     {
//         // find out which way is forward
//         const FRotator Rotation = Controller->GetControlRotation();
//         const FRotator YawRotation(0, Rotation.Yaw, 0);
// 
//         // get forward vector
//         const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
//         AddMovementInput(Direction, Value);
//     }
// }
// 
// void AMyProjectCharacter::MoveRight(float Value)
// {
//     if ((Controller != NULL) && (Value != 0.0f))
//     {
//         // find out which way is right
//         const FRotator Rotation = Controller->GetControlRotation();
//         const FRotator YawRotation(0, Rotation.Yaw, 0);
// 
//         // get right vector 
//         const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
//         // add movement in that direction
//         AddMovementInput(Direction, Value);
//     }
// }

