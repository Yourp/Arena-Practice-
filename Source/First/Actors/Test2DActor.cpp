// Fill out your copyright notice in the Description page of Project Settings.

#include "Test2DActor.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ATest2DActor::ATest2DActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    PrimaryActorTick.TickInterval = 0.05f;
    Text = CreateDefaultSubobject<UTextRenderComponent>(TEXT("FacingText"));
}

// Called when the game starts or when spawned
void ATest2DActor::BeginPlay()
{
	Super::BeginPlay();

    CameraMgr = UGameplayStatics::GetPlayerCameraManager(this, 0);
}

// Called every frame
void ATest2DActor::Tick(float DeltaTime)
{
    if (WasRecentlyRendered())
    {
	    //Super::Tick(DeltaTime);

        PrimaryActorTick.TickInterval = DeltaTime - 0.004f;

        if (CameraMgr != nullptr)
        {
            FRotator NewRotation = CameraMgr->GetCameraRotation();
            NewRotation.Yaw += 180.f;
            NewRotation.Pitch *= -1.f;
            Text->SetRelativeRotation(NewRotation);
        }
    }
    else
    {
        PrimaryActorTick.TickInterval = 0.05f;
    }
}

