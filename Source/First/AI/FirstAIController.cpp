// Fill out your copyright notice in the Description page of Project Settings.

#include "FirstAIController.h"
#include "Kismet/GameplayStatics.h"
#include "Character/MyCharacter.h"
#include "AICharacter.h"
#include "Classes/AITypes.h"




void AFirstAIController::BeginPlay()
{
    Super::BeginPlay();

//     if (ACharacter* CameraMgr = UGameplayStatics::GetPlayerCharacter(this, 0))
//     {
//         if (AMyCharacter* Char = Cast<AMyCharacter>(CameraMgr))
//             MoveToActor(Char);
//     }

    MoveToLocation(FVector(1080.f, -50.f, 142.f));
    
}

void AFirstAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    EPathFollowingStatus::Type ad = GetMoveStatus();

    bool asd = false;
}
