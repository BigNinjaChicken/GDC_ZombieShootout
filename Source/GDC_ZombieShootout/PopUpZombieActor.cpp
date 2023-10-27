// Fill out your copyright notice in the Description page of Project Settings.


#include "PopUpZombieActor.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/Components/MeshComponent.h>
#include <../../../../../../../Source/Runtime/Engine/Classes/Engine/StaticMesh.h>
#include <../../../../../../../Source/Runtime/Engine/Classes/Components/StaticMeshComponent.h>
#include <../../../../../../../Source/Runtime/Engine/Classes/Components/BoxComponent.h>
#include <../../../../../../../Source/Runtime/Engine/Classes/GameFramework/Character.h>
#include <../../../../../../../Source/Runtime/Engine/Classes/Components/SphereComponent.h>
#include "ZombieGameInstance.h"

// Sets default values
APopUpZombieActor::APopUpZombieActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ZombieMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	RootComponent = ZombieMeshComponent;

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	TriggerBox->SetupAttachment(RootComponent);

	BodySphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("BodySphereComponent"));
	BodySphereComponent->SetupAttachment(RootComponent);

	HeadSphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("HeadSphereComponent"));
	HeadSphereComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void APopUpZombieActor::BeginPlay()
{
	Super::BeginPlay();
	
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &APopUpZombieActor::OnTriggerEnter);

	GameInstance = Cast<UZombieGameInstance>(GetGameInstance());
	if (!GameInstance) {
		UE_LOG(LogTemp, Error, TEXT("Failed to get GameInstance"));
		return;
	}
}

// Called every frame
void APopUpZombieActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APopUpZombieActor::OnTriggerEnter(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	if (!OtherActor->IsA(ACharacter::StaticClass())) {
		UE_LOG(LogTemp, Warning, TEXT("OtherActor is not ACharacter"));
		return;
	}

	SetActorRotation(FRotator(-90.0f, 0.0f, 180.0f));
	bHasPoppedUp = true;
}


