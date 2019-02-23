// Fill out your copyright notice in the Description page of Project Settings.

#include "Planet.h"

APlanet::APlanet()
{
//     MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
//     SetRootComponent(MeshComp);
//     StaticMeshComponent = MeshComp;

//     SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
//     SphereComp->SetCollisionProfileName("Trigger");
//     SphereComp->SetupAttachment(RootComponent);
//     //SphereComp->bGenerateOverlapEvents = false;
//     SphereComp->OnComponentBeginOverlap.AddDynamic(this, &APlanet::OnOverlap);
//     SphereComp->OnComponentEndOverlap.AddDynamic(this, &APlanet::OnEndOverlap);
    
    PrimaryActorTick.bCanEverTick = false;
}

void APlanet::Tick(float DeltaSeconds)
{
    TSet<AActor*> temp;
    SphereComp->GetOverlappingActors(temp);

    
    for (auto itr : temp)
    {
        if (APawnForPlanet* Char = Cast<APawnForPlanet>(itr))
        {
            
            FVector PlanerLoc = GetActorLocation();
            FRotator rot = UKismetMathLibrary::FindLookAtRotation(PlanerLoc, Char->GetActorLocation());
            PlanerLoc = UKismetMathLibrary::GetForwardVector(rot);

            Char->SetActorRotation(UKismetMathLibrary::MakeRotFromZX(PlanerLoc, Char->CapsuleComp->GetForwardVector()));

            Char->CapsuleComp->SetPhysicsLinearVelocity(PlanerLoc * -1.f * Char->MoveAxeleration, true);
        }
    }
    
}

void APlanet::OnOverlap(UPrimitiveComponent * OverlappingComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
//     if (APawnForPlanet* Char = Cast<APawnForPlanet>(OtherActor))
//     {
//         Char->GetCharacterMovement()->GravityScale = 0.f;
//     }
}

void APlanet::OnEndOverlap(UPrimitiveComponent * OverlappingComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
//     if (APawnForPlanet* Char = Cast<APawnForPlanet>(OtherActor))
//     {
//         Char->GetCharacterMovement()->GravityScale = 1.f;
//     }
}
