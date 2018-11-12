// Fill out your copyright notice in the Description page of Project Settings.

#include "Planet.h"

APlanet::APlanet()
{
//     MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
//     SetRootComponent(MeshComp);
//     StaticMeshComponent = MeshComp;

    SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
    SphereComp->SetCollisionProfileName("Trigger");
    SphereComp->SetupAttachment(RootComponent);
    //SphereComp->bGenerateOverlapEvents = false;
    SphereComp->OnComponentBeginOverlap.AddDynamic(this, &APlanet::OnOverlap);
    SphereComp->OnComponentEndOverlap.AddDynamic(this, &APlanet::OnEndOverlap);
    
    PrimaryActorTick.bCanEverTick = true;
}

void APlanet::Tick(float DeltaSeconds)
{
    TSet<AActor*> temp;
    SphereComp->GetOverlappingActors(temp);

    
    for (auto itr : temp)
    {
        if (AMyCharacter* Char = Cast<AMyCharacter>(itr))
        {
            FVector addVelocity = (GetActorLocation() - itr->GetActorLocation()) * DeltaSeconds;
            if (Char->GetCharacterMovement()->MovementMode == MOVE_Falling)
            {
                
                Char->GetCharacterMovement()->Velocity += addVelocity;
            }
            Char->SetActorRotation(addVelocity.Rotation());
        }
    }
    
}

void APlanet::OnOverlap(UPrimitiveComponent * OverlappingComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
    if (AMyCharacter* Char = Cast<AMyCharacter>(OtherActor))
    {
        Char->GetCharacterMovement()->GravityScale = 0.f;
    }
}

void APlanet::OnEndOverlap(UPrimitiveComponent * OverlappingComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
    if (AMyCharacter* Char = Cast<AMyCharacter>(OtherActor))
    {
        Char->GetCharacterMovement()->GravityScale = 1.f;
    }
}
