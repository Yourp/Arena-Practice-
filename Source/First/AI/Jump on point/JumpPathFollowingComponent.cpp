// Fill out your copyright notice in the Description page of Project Settings.

#include "JumpPathFollowingComponent.h"

void UJumpPathFollowingComponent::SetMoveSegment(int32 SegmentStartIndex)
{
    Super::SetMoveSegment(SegmentStartIndex);

    if (CharacterMoveComp == NULL)
    {
        if (UCharacterMovementComponent* Nav = Cast<UCharacterMovementComponent>(UPathFollowingComponent::MovementComp))
        {
            CharacterMoveComp = Nav;
        }
    }

    if (CharacterMoveComp != NULL)
    {
        const TArray<FNavPathPoint>& PathPoints = Path->GetPathPoints();
        const FNavPathPoint& SegmentStart = PathPoints[MoveSegmentStartIndex];

        if (FNavAreaHelper::HasJumpFlag(SegmentStart))
        {
            // jump! well... fly-in-straight-line!
            CharacterMoveComp->SetMovementMode(MOVE_Flying);
            CharacterMoveComp->GravityScale = 0.f;
        }
        else
        {
            CharacterMoveComp->GravityScale = 1.f;
            // regular move
            CharacterMoveComp->SetMovementMode(MOVE_Walking);
        }
    }
}