// Fill out your copyright notice in the Description page of Project Settings.

#include "SplineTrap.h"
#include "Character/MyCharacter.h"

// Sets default values
ASplineTrap::ASplineTrap()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    SceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
    SetRootComponent(SceneComp);
    SceneComp->bHiddenInGame = true;

    SplineComp = CreateDefaultSubobject<USplineComponent>(TEXT("SplineComponent"));
    SplineComp->SetupAttachment(SceneComp);
    SplineComp->bHiddenInGame = true;

    SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
    SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ASplineTrap::OnOverlap);
    SphereComp->SetupAttachment(SceneComp);

    StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    StaticMesh->SetupAttachment(SphereComp);

    timer = 0.f;
    maxTime = 1.f;
    bReturn = false;
}

// Called when the game starts or when spawned
void ASplineTrap::BeginPlay()
{
	Super::BeginPlay();
    timer = FMath::RandRange(0.f, maxTime);
    bReturn = FMath::RandBool();
}

void ASplineTrap::OnOverlap(UPrimitiveComponent * OverlappingComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
    AMyCharacter* Char = Cast<AMyCharacter>(OtherActor);

    if (Char != nullptr)
    {
        Char->TeleportToSavePosition();
    }
}

// Called every frame
void ASplineTrap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if (bReturn)
    {
        timer -= DeltaTime;

        if (0.f > timer)
        {
            timer = 0.f;
            bReturn = false;
        }
    }
    else
    {
        timer += DeltaTime;

        if (maxTime < timer)
        {
            timer = maxTime;
            bReturn = true;
        }
    }

    if (timer >= 0.f)
    {
        float getDistance = SplineComp->GetSplineLength() / maxTime * timer;
        SphereComp->SetWorldTransform(FTransform(FRotator(0.f), SplineComp->GetLocationAtDistanceAlongSpline(getDistance, ESplineCoordinateSpace::World), SphereComp->GetComponentScale()));
    }
}

