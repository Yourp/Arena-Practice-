// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/TextRenderComponent.h"
#include "Camera/PlayerCameraManager.h"
#include "Test2DActor.generated.h"

UCLASS()
class FIRST_API ATest2DActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATest2DActor();

    APlayerCameraManager* CameraMgr;

protected:
	// Called when the game starts or when spawned

public:	

    virtual void BeginPlay() override;
    // Called every frame
	virtual void Tick(float DeltaTime) override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    UTextRenderComponent* Text;
	
};
