// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PopUpZombieActor.generated.h"

UCLASS()
class GDC_ZOMBIESHOOTOUT_API APopUpZombieActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APopUpZombieActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnTriggerEnter(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* ZombieMeshComponent;

	UPROPERTY(EditAnywhere, Category = "Spline")
	class USphereComponent* HeadSphereComponent;

	UPROPERTY(EditAnywhere, Category = "Spline")
	class USphereComponent* BodySphereComponent;

	class UZombieGameInstance* GameInstance;

	UPROPERTY(EditAnywhere)
	class UBoxComponent* TriggerBox;

	bool bHasPoppedUp = false;
};
