// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ThreadTest.generated.h"

UCLASS()
class FIRST_API AThreadTest : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AThreadTest();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

    UFUNCTION(BlueprintCallable)
    void RunPrimeTask();
	
    UFUNCTION(BlueprintCallable)
    void RunPrimeTaskOnMain();

    AActor* Me;
    bool triggerLock;
    bool canTrigger;
};

class PrimeSearchTask : public FNonAbandonableTask
{
public:
    PrimeSearchTask(AActor* actor);

    ~PrimeSearchTask();

    FORCEINLINE TStatId GetStatId() const
    {
        RETURN_QUICK_DECLARE_CYCLE_STAT(PrimeSearchTask, STATGROUP_ThreadPoolAsyncTasks);
    }

    AActor* _actor;

    void DoWork();

    void DoWorkMain();
};

