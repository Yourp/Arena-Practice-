// Fill out your copyright notice in the Description page of Project Settings.

#include "MyHUD.h"


void AMyHUD::DrawHUD()
{
    
    DrawRect(FLinearColor(0.f, 0.f, 0.f, 0.4f), 43, 68, 204, 14);
    DrawRect(FLinearColor(0.5f, 0.f, 0.f, 1.f), 45, 70, 150, 10);
    DrawRect(FLinearColor(0.1f, 0.1f, 0.7f, 1.f), 45, 70, 120, 10);
}
