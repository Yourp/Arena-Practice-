// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Character/MyCharacter.h"
#include "MyHUD.generated.h"

class AMyCharacter;
/**
 * 
 */

#define HealthStartPosX         50.f
#define HealthStartPosY         50.f
#define HealthLength            300.f
#define HealthWidth             20.f
#define HealthBorderSize        3.f

#define HealthBorderStartPosX   (HealthStartPosX - HealthBorderSize)
#define HealthBorderStartPosY   (HealthStartPosY - HealthBorderSize)
#define HealthBorderWidth       (HealthWidth + HealthBorderSize * 2.f)
#define HealthBorderLength      (HealthLength + HealthBorderSize * 2.f)

UCLASS()
class FIRST_API AMyHUD : public AHUD
{
    GENERATED_BODY()

public:

    AMyHUD();

    void BeginPlay() override;
    void DrawHUD() override;

    void ActivateItemInHUD(uint8 itemID);


    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<UMaterialInterface*> Materials;

private:

    UPROPERTY()
    AMyCharacter* Char;

    UPROPERTY()
    TArray<UMaterialInstanceDynamic*> MaterialsInstanceDynamic;
};
