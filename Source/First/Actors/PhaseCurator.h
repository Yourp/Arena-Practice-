// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "Components/BoxComponent.h"
#include "PhaseCurator.generated.h"

/**
 * 
 */
UCLASS()
class FIRST_API APhaseCurator : public AStaticMeshActor
{
	GENERATED_BODY()

public:
    APhaseCurator();

    UFUNCTION()
        void OnOverlap(class UPrimitiveComponent* OverlappingComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


    UBoxComponent* TriggerBox;

    UPROPERTY(EditAnywhere, Category = "Index")
    uint8 index;
	
};
