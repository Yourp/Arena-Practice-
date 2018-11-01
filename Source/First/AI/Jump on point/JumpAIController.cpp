// Fill out your copyright notice in the Description page of Project Settings.

#include "JumpAIController.h"


AJumpAIController::AJumpAIController(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer.SetDefaultSubobjectClass<UJumpPathFollowingComponent>(TEXT("PathFollowingComponent")))
{
}

void AJumpAIController::BeginPlay()
{
    Super::BeginPlay();

    //     if (ACharacter* CameraMgr = UGameplayStatics::GetPlayerCharacter(this, 0))
    //     {
    //         if (AMyCharacter* Char = Cast<AMyCharacter>(CameraMgr))
    //             MoveToActor(Char);
    //     }

    MoveToLocation(FVector(790.f, 80.f, 580.f));

}

