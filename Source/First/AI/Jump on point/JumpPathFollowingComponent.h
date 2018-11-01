// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Navigation/PathFollowingComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "UObject/Object.h"
#include "NavArea_Jump.h"
#include "AI/Navigation/NavigationData.h"
//#include "GameFramework/NavMovementComponent.h"
#include "JumpPathFollowingComponent.generated.h"

/**
 * 
 */
UCLASS()
class FIRST_API UJumpPathFollowingComponent : public UPathFollowingComponent
{
    GENERATED_BODY()

    protected:
    /** cached UCharacterMovementComponent */
    UPROPERTY(Transient)
    UCharacterMovementComponent* CharacterMoveComp;

    public:
    // used to detect properties of a path's segment a character is about to follow
    virtual void SetMoveSegment(int32 SegmentStartIndex) override;

    
    // used to cache UCharacterMovementComponent we're using in SetMoveSegment implementation
    //virtual void SetMovementComponent(UNavMovementComponent* MoveComp) override;
	
};
