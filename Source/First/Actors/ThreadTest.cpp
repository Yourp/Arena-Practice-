// Fill out your copyright notice in the Description page of Project Settings.

#include "ThreadTest.h"


// Sets default values
AThreadTest::AThreadTest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    Me = Cast<AActor>(this);
    triggerLock = false;
    canTrigger = true;
}

// Called when the game starts or when spawned
void AThreadTest::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AThreadTest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AThreadTest::RunPrimeTask()
{
    if (Me && !triggerLock && canTrigger)
    {
        canTrigger = false;
        (new FAutoDeleteAsyncTask<PrimeSearchTask>(Me))->StartBackgroundTask();
        canTrigger = true;
    }
}

void AThreadTest::RunPrimeTaskOnMain()
{
    if (Me && !triggerLock && canTrigger)
    {
        canTrigger = false;
        PrimeSearchTask* task = new PrimeSearchTask(Me);

        task->DoWorkMain();

        delete task;
        canTrigger = true;
    }
}

PrimeSearchTask::PrimeSearchTask(AActor* actor)
{
    _actor = actor;
}

PrimeSearchTask::~PrimeSearchTask()
{
    UE_LOG(LogTemp, Warning, TEXT("Task Finished!!!"));
}

void PrimeSearchTask::DoWork()
{
    if (_actor)
    {
        // do some code
        
    }
}

void PrimeSearchTask::DoWorkMain()
{
    DoWork();
}
