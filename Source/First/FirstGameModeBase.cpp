// Fill out your copyright notice in the Description page of Project Settings.

#include "FirstGameModeBase.h"
#include "Character/MyCharacter.h"
#include "Blueprint/UserWidget.h"

void AFirstGameModeBase::BeginPlay()
{
    Super::BeginPlay();

    if (PlayerHUDClass != nullptr)
    {
        CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), PlayerHUDClass);

        if (CurrentWidget != nullptr)
        {
            CurrentWidget->AddToViewport();
        }
    }
}
