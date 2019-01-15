// Fill out your copyright notice in the Description page of Project Settings.

#include "MyHUD.h"
#include "CanvasItem.h"
#include "Engine/Canvas.h"
#include "CanvasTypes.h"

AMyHUD::AMyHUD()
{
    PrimaryActorTick.bCanEverTick = true;
}

void AMyHUD::BeginPlay()
{
    if (PlayerOwner != nullptr)
    {
        Char = Cast<AMyCharacter>(PlayerOwner->AcknowledgedPawn);
    }
}

void AMyHUD::DrawHUD()
{
    if (IsCanvasValid_WarnIfNot() && Char != nullptr)
    {
        FCanvasTileItem TileItem
        (
            FVector2D(HealthBorderStartPosX, HealthBorderStartPosY), 
            GWhiteTexture, 
            FVector2D(HealthBorderLength, HealthBorderWidth), 
            FLinearColor(0.f, 0.f, 0.f, 0.4f)
        );

        TileItem.BlendMode = SE_BLEND_Translucent;
        Canvas->DrawItem(TileItem);

        TileItem.Position = FVector2D(HealthStartPosX, HealthStartPosY);

        float dropEffect = Char->GetHealthDropEffect();
        float health = Char->GetHealth();

        if (dropEffect != health)
        {
            TileItem.Size = FVector2D(HealthLength * dropEffect, HealthWidth);
            TileItem.SetColor(FLinearColor(0.4f, 0.f, 0.f, 1.f));
            Canvas->DrawItem(TileItem);
        }
        else
        {
            TileItem.Size.Y = HealthWidth;
        }

        TileItem.Size.X = health * HealthLength;
        TileItem.SetColor(FLinearColor(0.f, 0.4f, 0.f, 1.f));
        Canvas->DrawItem(TileItem);
    }

//     
//     DrawRect(FLinearColor(0.f, 0.f, 0.f, 0.4f), 47.f, 47.f, 306.f, 26.f);
//     DrawRect(FLinearColor(0.5f, 0.f, 0.f, 1.f), 50.f, 50.f, 250.f, 20);
//     DrawRect(FLinearColor(0.f, 0.4f, 0.f, 1.f), 50.f, 50.f, 200.f, 20);
}
