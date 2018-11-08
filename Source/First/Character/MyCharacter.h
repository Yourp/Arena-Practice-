// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/SkeletalMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Pawn.h"
#include "Components/InputComponent.h"
#include "Curves/CurveFloat.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "MyCharacter.generated.h"

UCLASS()
class FIRST_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

    virtual void Landed(const FHitResult& Hit) override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    UCameraComponent* CharCamera;

    AActor* LandTarget;

    float maxDist2D;
    float maxJumpZ;
    float startZ;

    float timer;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    void MoveForward(float Value);
    void MoveRight(float Value);
    void SmartJump();

    UPROPERTY(EditAnywhere, Category = "Curves")
    UCurveFloat* fCurveXY;

    UPROPERTY(EditAnywhere, Category = "Curves")
    UCurveFloat* fCurveZ;
};
