// Fill out your copyright notice in the Description page of Project Settings.

#include "TimelineTest.h"

ATimelineTest::ATimelineTest()
{
    MyTimeLine = CreateDefaultSubobject<UTimelineComponent>(TEXT("Timeline"));

    InterpFunction.BindUFunction(this, FName("TimelineFloatReturn"));
    TimelineFinished.BindUFunction(this, FName("OnTimelineFinished"));

    ZOffset = 50.f;
}

void ATimelineTest::BeginPlay()
{
    Super::BeginPlay();

    if (fCurve)
    {
        MyTimeLine->AddInterpFloat(fCurve, InterpFunction, FName("Alpha"));
        MyTimeLine->SetTimelineFinishedFunc(TimelineFinished);

        StartLocation = GetActorLocation();
        EndLocation = FVector(StartLocation.X, StartLocation.Y, StartLocation.Z + ZOffset);

        MyTimeLine->SetLooping(false);
        MyTimeLine->SetIgnoreTimeDilation(true);

        MyTimeLine->Play();
    }
}

void ATimelineTest::TimelineFloatReturn(float value)
{
    SetActorLocation(FMath::Lerp(StartLocation, EndLocation, value));
}

void ATimelineTest::OnTimelineFinished()
{
    if (MyTimeLine->GetPlaybackPosition() == 0.f)
    {
        GLog->Log("PLAY");
        MyTimeLine->Play();
    }
    else if (MyTimeLine->GetPlaybackPosition() == MyTimeLine->GetTimelineLength())
    {
        GLog->Log("REVERSE");
        MyTimeLine->Reverse();
    }
}
