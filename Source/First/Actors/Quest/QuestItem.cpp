// Fill out your copyright notice in the Description page of Project Settings.

#include "QuestItem.h"
#include "Character/MyCharacter.h"

// Sets default values
AQuestItem::AQuestItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

    SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
    SphereComp->OnComponentBeginOverlap.AddDynamic(this, &AQuestItem::OnOverlap);
    SetRootComponent(SphereComp);

    StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    StaticMesh->SetupAttachment(SphereComp);

    Light = CreateDefaultSubobject<UPointLightComponent>(TEXT("PointLight"));
    Light->SetupAttachment(SphereComp);

    bActive = true;
}

void AQuestItem::OnOverlap(UPrimitiveComponent * OverlappingComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
    if (!bActive)
        return;

    AMyCharacter* Char = Cast<AMyCharacter>(OtherActor);

    if (Char != nullptr)
    {
        bActive = false;
        Char->DoPickupItem(ItemID);
        Light->SetVisibility(false);
        Char->HandleQuestComplete();
    }
}

