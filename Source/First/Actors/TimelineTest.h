// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "Components/TimelineComponent.h"
#include "TimelineTest.generated.h"

/**
 * 
 */
UCLASS()
class FIRST_API ATimelineTest : public AStaticMeshActor
{
    GENERATED_BODY()

public:
    ATimelineTest();

    virtual void BeginPlay() override;

    UFUNCTION()
    void TimelineFloatReturn(float value);

    UFUNCTION()
    void OnTimelineFinished();

    UPROPERTY(EditAnywhere, Category = "Timeline")
    class UCurveFloat* fCurve;

    UTimelineComponent* MyTimeLine;

    FOnTimelineFloat InterpFunction;
    FOnTimelineEvent TimelineFinished;

    UPROPERTY()
    FVector StartLocation;

    UPROPERTY()
    FVector EndLocation;

    UPROPERTY(EditAnywhere, Category = "Timeline")
    float ZOffset;

	
};
