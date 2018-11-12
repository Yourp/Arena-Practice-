// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "Components/SphereComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Character/MyCharacter.h"
#include "Planet.generated.h"

/**
 * 
 */
UCLASS()
class FIRST_API APlanet : public AStaticMeshActor
{
	GENERATED_BODY()
	
private:
    APlanet();

    virtual void Tick(float DeltaSeconds) override;

public:

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    USphereComponent* SphereComp;

    UFUNCTION()
    void OnOverlap(class UPrimitiveComponent* OverlappingComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    UFUNCTION()
    void OnEndOverlap(class UPrimitiveComponent* OverlappingComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex/*, bool bFromSweep, const FHitResult& SweepResult*/);

};
