// Fill out your copyright notice in the Description page of Project Settings.

#include "PawnForPlanet.h"


// Sets default values
APawnForPlanet::APawnForPlanet()
{
    CapsuleComp = CreateDefaultSubobject<UStaticMeshComponent>("Capsule");
    SetRootComponent(CapsuleComp);

    NoseComp = CreateDefaultSubobject<UStaticMeshComponent>("Nose");
    NoseComp->SetupAttachment(CapsuleComp);

    SpringArm = CreateDefaultSubobject<USpringArmComponent>("Spring Arm");
    SpringArm->SetupAttachment(CapsuleComp);

    CameraComp = CreateDefaultSubobject<UCameraComponent>("Camera");
    CameraComp->SetupAttachment(SpringArm);

 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    MoveAxeleration = 10.f;
}

// Called when the game starts or when spawned
void APawnForPlanet::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APawnForPlanet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APawnForPlanet::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

//     check(PlayerInputComponent);
    PlayerInputComponent->BindAxis("LookUp", this, &APawnForPlanet::CamereUp);
    PlayerInputComponent->BindAxis("Turn", this, &APawnForPlanet::CamereRight);
    PlayerInputComponent->BindAxis("MoveForward", this, &APawnForPlanet::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &APawnForPlanet::MoveRight);

    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &APawnForPlanet::DoJump);
//     PlayerInputComponent->BindAction("Jump", IE_Released, this, &APawnForPlanet::StopJumping);
}

void APawnForPlanet::MoveForward(float Value)
{
    if (Value != 0.f)
    {
        CapsuleComp->SetPhysicsLinearVelocity((CapsuleComp->GetForwardVector() * Value * MoveAxeleration), true);
    }
}

void APawnForPlanet::MoveRight(float Value)
{
    if (Value != 0.f)
    {
        CapsuleComp->SetPhysicsLinearVelocity((CapsuleComp->GetRightVector() * Value * MoveAxeleration), true);
    }
}

void APawnForPlanet::CamereUp(float Value)
{
    if (Value != 0.f)
    {
        
        SpringArm->AddLocalRotation(FRotator(-(Value), 0, 0));
    }
}

void APawnForPlanet::CamereRight(float Value)
{
    if (Value != 0.f)
    {
        AddActorLocalRotation(FRotator(0, Value, 0));
    }
}

void APawnForPlanet::DoJump()
{
    CapsuleComp->SetPhysicsLinearVelocity((CapsuleComp->GetUpVector() * 1500.f), true);
}

