// Fill out your copyright notice in the Description page of Project Settings.

#include "PositionSaver.h"
#include "Character/MyCharacter.h"

// Sets default values
APositionSaver::APositionSaver()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

    TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
    SetRootComponent(TriggerBox);
    TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &APositionSaver::OnOverlap);
}

void APositionSaver::OnOverlap(UPrimitiveComponent * OverlappingComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
    AMyCharacter* Char = Cast<AMyCharacter>(OtherActor);

    if (Char != nullptr && !SavePoint.IsZero())
    {
        Char->SetSavePosition(SavePoint);
    }
}

