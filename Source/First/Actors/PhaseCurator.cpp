// Fill out your copyright notice in the Description page of Project Settings.

#include "PhaseCurator.h"

APhaseCurator::APhaseCurator()
{
    PrimaryActorTick.bCanEverTick = false;
    TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
    SetRootComponent(TriggerBox);
    TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &APhaseCurator::OnOverlap);
}

void APhaseCurator::OnOverlap(UPrimitiveComponent * OverlappingComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{

}