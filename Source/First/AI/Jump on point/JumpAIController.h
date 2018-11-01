// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "JumpPathFollowingComponent.h"
#include "JumpAIController.generated.h"

/**
 * 
 */
UCLASS()
class FIRST_API AJumpAIController : public AAIController
{
	GENERATED_BODY()
	
public:
    AJumpAIController(const FObjectInitializer & ObjectInitializer);

    virtual void BeginPlay() override;

};
