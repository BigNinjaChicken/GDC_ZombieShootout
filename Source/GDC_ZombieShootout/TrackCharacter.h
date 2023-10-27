// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include <../../../../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/InputActionValue.h>
#include "TrackCharacter.generated.h"

UCLASS()
class GDC_ZOMBIESHOOTOUT_API ATrackCharacter : public ACharacter
{
	GENERATED_BODY()

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* ShootAction;

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	/** Called for looking input */
	void Shoot(const FInputActionValue& Value);

public:
	// Sets default values for this character's properties
	ATrackCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void MoveAlongTrack(float DeltaTime);

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, Category = "Spline")
	class UCameraComponent* CameraComponent;

	UPROPERTY(EditAnywhere, Category = "Spline")
	class ATrackActor* TrackActor;

	UPROPERTY(EditAnywhere, Category = "Spline")
	TArray<float> TrackSegmentSpeeds;

	float TractDistanceAlhpa = 0.0f;

	UPROPERTY(EditAnywhere, Category = "Spline")
	float TrackSpeed = 1.0f;

	float ShotCooldown = 1.0f;
	float LastShotTime = 0.0f;

	class UZombieGameInstance* GameInstance;
};
