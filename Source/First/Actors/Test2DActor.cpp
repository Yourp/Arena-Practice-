// Fill out your copyright notice in the Description page of Project Settings.

#include "Test2DActor.h"
#include "Character/MyCharacter.h"
#include "Camera/PlayerCameraManager.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ATest2DActor::ATest2DActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    
    Text = CreateDefaultSubobject<UTextRenderComponent>(TEXT("FacingText"));
}

// Called when the game starts or when spawned
void ATest2DActor::BeginPlay()
{
	Super::BeginPlay();
	
    PrimaryActorTick.TickInterval = 0.0f;
}

// Called every frame
void ATest2DActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if (APlayerCameraManager* CameraMgr = UGameplayStatics::GetPlayerCameraManager(this, 0))
    {
        FRotator NewRotation = CameraMgr->GetCameraRotation();
        NewRotation.Yaw += 180.f;
        NewRotation.Pitch *= -1.f;
        Text->SetRelativeRotation(NewRotation);
//         FVector Loc = CameraMgr->GetCameraLocation();
//         FVector TextLoc = GetActorLocation();
//         FRotator NewRotation = UKismetMathLibrary::FindLookAtRotation(TextLoc, Loc);
//         SetActorRotation(NewRotation);
    }
}

