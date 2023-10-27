// Fill out your copyright notice in the Description page of Project Settings.


#include "TrackActor.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/Components/SplineComponent.h>

// Sets default values
ATrackActor::ATrackActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create the SplineComponent and set it as the RootComponent
	TrackSplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("SplineComponent"));
	SetRootComponent(TrackSplineComponent);
}

// Called when the game starts or when spawned
void ATrackActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATrackActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

