// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/SkeletalMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Pawn.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Components/CapsuleComponent.h"
#include "MyCharacter.generated.h"

#define JumpHight 1100.f
#define FallSpeed 2900.f
#define HealthDropEffectTimer   0.5f

USTRUCT()
struct FHealthDriver
{
    GENERATED_BODY()

    FHealthDriver();

    float CurHealth;
    float CurHealthDropEffect;
    float Timer;
};

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

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    float GetHealth() const;
    float GetHealthDropEffect() const;

    void SetCanSmartJump(bool val);
    void SetPhase(uint8 val);
    uint8 GetPhase() const;
    uint8 GetLastPhaseCuratorIndex() const;
    void SetLastPhaseCuratorIndex(uint8 val);

private:
    void MoveForward(float Value);
    void MoveRight(float Value);
    void SmartJump();
    void SetDamage(float damage = 0.1f);
    void HandleDamage();
    void RestoreHealth();

    FHealthDriver bHealthDriver;
    bool bCanSmartJump;
    uint8 Phase;
    uint8 LastPhaseCuratorIndex;
};
