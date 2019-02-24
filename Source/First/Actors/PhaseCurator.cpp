// Fill out your copyright notice in the Description page of Project Settings.

#include "PhaseCurator.h"
#include "Character/MyCharacter.h"
#include "Kismet/GameplayStatics.h"

APhaseCurator::APhaseCurator()
{
    PrimaryActorTick.bCanEverTick = false;
    TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
    SetRootComponent(TriggerBox);
    TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &APhaseCurator::OnOverlap);
    index = 0;
}

void APhaseCurator::OnOverlap(UPrimitiveComponent * OverlappingComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
    AMyCharacter* Char = Cast<AMyCharacter>(OtherActor);

    if (Char != nullptr)
    {
        if (Char->GetLastPhaseCuratorIndex() == index)
            return;


        switch (index)
        {
            case 0:
            {
                TArray<AActor*> targets;

                UGameplayStatics::GetAllActorsWithTag(this, "p2", targets);

                for (auto itr : targets)
                {
                    itr->GetRootComponent()->SetVisibility(true, true);
                    itr->SetActorEnableCollision(true);
                }

                UGameplayStatics::GetAllActorsWithTag(this, "p0", targets);

                for (auto itr : targets)
                {
                    itr->GetRootComponent()->SetVisibility(false, true);
                    itr->SetActorEnableCollision(false);
                }
                break;
            }
            case 1:
            {
                TArray<AActor*> targets;

                UGameplayStatics::GetAllActorsWithTag(this, "p0", targets);

                for (auto itr : targets)
                {
                    itr->GetRootComponent()->SetVisibility(true, true);
                    itr->SetActorEnableCollision(true);
                }

                UGameplayStatics::GetAllActorsWithTag(this, "p2", targets);

                for (auto itr : targets)
                {
                    itr->GetRootComponent()->SetVisibility(false, true);
                    itr->SetActorEnableCollision(false);
                }
                break;
            }
            default:
            {
                break;
            }
        }
        Char->SetLastPhaseCuratorIndex(index);
    }
}