// Fill out your copyright notice in the Description page of Project Settings.

#include "SplineTest.h"


// Sets default values
ASplineTest::ASplineTest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    SceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
    SetRootComponent(SceneComp);

    SplineComp = CreateDefaultSubobject<USplineComponent>(TEXT("SplineComponent"));
    SplineComp->SetupAttachment(SceneComp);

    BoxComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CubeComponent"));
    BoxComp->SetupAttachment(SceneComp);

    timer = 0.f;
}

// Called when the game starts or when spawned
void ASplineTest::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASplineTest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if (fCurve)
    {
        timer += DeltaTime;
        float getDistance = SplineComp->GetSplineLength() * fCurve->GetFloatValue(timer);
        
        BoxComp->SetWorldTransform(FTransform(BoxComp->GetComponentRotation(), SplineComp->GetLocationAtDistanceAlongSpline(getDistance, ESplineCoordinateSpace::World), BoxComp->GetComponentScale()));
    }
}

