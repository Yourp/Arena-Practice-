// Fill out your copyright notice in the Description page of Project Settings.

#include "TeleportBox.h"
#include "Kismet/GameplayStatics.h"
#include "Character/MyCharacter.h"

// Sets default values
ATeleportBox::ATeleportBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

    TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
    SetRootComponent(TriggerBox);
    TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ATeleportBox::OnOverlap);

}

void ATeleportBox::OnOverlap(UPrimitiveComponent * OverlappingComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
    AMyCharacter* Char = Cast<AMyCharacter>(OtherActor);

    if (Char != nullptr)
    {
        switch (Char->GetPhase())
        {
            case 0:
            {
                Char->SetCanSmartJump(false);
                TArray<AActor*> targets;

                UGameplayStatics::GetAllActorsWithTag(this, "p1", targets);

                for (auto itr : targets)
                {
                    itr->GetRootComponent()->SetVisibility(false, true);
                    itr->SetActorEnableCollision(false);
                }

                UGameplayStatics::GetAllActorsWithTag(this, "p3", targets);

                for (auto itr : targets)
                {
                    itr->GetRootComponent()->SetVisibility(true, true);
                    itr->SetActorEnableCollision(true);
                }

                Char->SetPhase(1);
                break;
            }
            case 1:
            {
                Char->SetCanSmartJump(true);
                TArray<AActor*> targets;

                UGameplayStatics::GetAllActorsWithTag(this, "p1", targets);

                for (auto itr : targets)
                {
                    itr->GetRootComponent()->SetVisibility(true, true);
                    itr->SetActorEnableCollision(true);
                }

                UGameplayStatics::GetAllActorsWithTag(this, "p3", targets);

                for (auto itr : targets)
                {
                    itr->GetRootComponent()->SetVisibility(false, true);
                    itr->SetActorEnableCollision(false);
                }

                Char->SetPhase(0);
                break;
            }
            default:
                break;
        }
    }
}
