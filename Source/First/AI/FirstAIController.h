// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "FirstAIController.generated.h"

/**
 * 
 */
UCLASS()
class FIRST_API AFirstAIController : public AAIController
{
	GENERATED_BODY()

public:

    virtual void BeginPlay() override;

    virtual void Tick(float DeltaTime) override;
	
	
};
