// Fill out your copyright notice in the Description page of Project Settings.

#include "FirstGameModeBase.h"


AFirstGameModeBase::AFirstGameModeBase()
{
    
}

void AFirstGameModeBase::SetStartLocation(FVector Pos, FRotator Rot)
{
    Position = Pos;
    Rotation = Rot;
}
