// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/PointLightComponent.h"
#include "QuestItem.generated.h"

UCLASS()
class FIRST_API AQuestItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AQuestItem();

    UFUNCTION()
    void OnOverlap(class UPrimitiveComponent* OverlappingComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    UPROPERTY(EditAnywhere)
    uint8 ItemID;

protected:

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    USphereComponent* SphereComp;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    UStaticMeshComponent* StaticMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    UPointLightComponent* Light;

    UPROPERTY()
    bool bActive;
};
