// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SplineComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Curves/CurveFloat.h"
#include "SplineTest.generated.h"

UCLASS()
class FIRST_API ASplineTest : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASplineTest();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    USceneComponent* SceneComp;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    USplineComponent* SplineComp;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    UStaticMeshComponent* BoxComp;

    UPROPERTY(EditAnywhere)
    UCurveFloat* fCurve;

    float timer;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
