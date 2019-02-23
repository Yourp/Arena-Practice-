// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FirstGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class FIRST_API AFirstGameModeBase : public AGameModeBase
{
    GENERATED_BODY()

    AFirstGameModeBase();

public:

    void SetStartLocation(FVector Pos, FRotator Rot);

private:
    FVector Position;
    FRotator Rotation;
};
