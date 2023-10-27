// Fill out your copyright notice in the Description page of Project Settings.


#include "TrackCharacter.h"
#include <EnhancedInputComponent.h>
#include <EnhancedInputSubsystems.h>
#include <Camera/CameraComponent.h>
#include <GameFramework/PlayerController.h>
#include <Kismet/GameplayStatics.h>
#include <EnhancedInputSubsystemInterface.h>
#include "TrackActor.h"
#include <Components/SplineComponent.h>
#include "PopUpZombieActor.h"
#include "ZombieGameInstance.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/Components/SphereComponent.h>

// Sets default values
ATrackCharacter::ATrackCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


    CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
    CameraComponent->SetupAttachment(RootComponent);
    // TrackSegmentSpeeds.SetNum(TrackSplineComponent->GetNumberOfSplineSegments());
}

// Called when the game starts or when spawned
void ATrackCharacter::BeginPlay()
{
	Super::BeginPlay();

    TrackActor = Cast<ATrackActor>(UGameplayStatics::GetActorOfClass(GetWorld(), ATrackActor::StaticClass()));
	
    //Add Input Mapping Context
    if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
    {
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
        {
            Subsystem->AddMappingContext(DefaultMappingContext, 0);
        }
    }

    GameInstance = Cast<UZombieGameInstance>(GetGameInstance());
    if (!GameInstance) {
        UE_LOG(LogTemp, Error, TEXT("Failed to get GameInstance"));
        return;
    }

}

// Called every frame
void ATrackCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    MoveAlongTrack(DeltaTime);
    return;
}

void ATrackCharacter::MoveAlongTrack(float DeltaTime)
{
	if (!TrackActor) {
		UE_LOG(LogTemp, Warning, TEXT("TrackActor Null"));
		return;
	}

	USplineComponent* TrackSplineComponent = TrackActor->TrackSplineComponent;

	float SplineLength = TrackSplineComponent->GetSplineLength();
	TractDistanceAlhpa += DeltaTime * TrackSpeed;

	float CurrentLocation = FMath::Lerp(0.0f, SplineLength, TractDistanceAlhpa);
	// UE_LOG(LogTemp, Warning, TEXT("%f"), CurrentLocation);
	FVector CameraLocation = TrackSplineComponent->GetLocationAtDistanceAlongSpline(CurrentLocation, ESplineCoordinateSpace::World);
    SetActorLocation(CameraLocation);
}

// Called to bind functionality to input
void ATrackCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

    // Set up action bindings
    if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
        EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ATrackCharacter::Look);
        EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Triggered, this, &ATrackCharacter::Shoot);
    }
}


void ATrackCharacter::Look(const FInputActionValue& Value)
{
    // input is a Vector2D
    FVector2D LookAxisVector = Value.Get<FVector2D>();

    if (Controller != nullptr)
    {
        // add yaw and pitch input to controller
        AddControllerYawInput(LookAxisVector.X);
        AddControllerPitchInput(LookAxisVector.Y);
    }
}

void ATrackCharacter::Shoot(const FInputActionValue& Value)
{
    APlayerController* PlayerController = Cast<APlayerController>(GetController());

    if (!PlayerController)
    {
        UE_LOG(LogTemp, Warning, TEXT("PlayerController Null"));
        return;
    }

    // Check if enough time has passed since the last shot.
    float CurrentTime = GetWorld()->GetTimeSeconds();
    if (CurrentTime - LastShotTime >= ShotCooldown)
    {
        // Perform the shooting action here.
        UE_LOG(LogTemp, Warning, TEXT("Shoot"));

        // Update the last shot time.
        LastShotTime = CurrentTime;

        // Perform a raycast from the camera to where the player is aiming.
        FVector CameraLocation;
        FRotator CameraRotation;
        PlayerController->GetPlayerViewPoint(CameraLocation, CameraRotation);

        FVector TraceEnd = CameraLocation + (CameraRotation.Vector() * 10000.0f);  // Adjust the range as needed.

        TArray<FHitResult> HitResult;

        FCollisionQueryParams TraceParams;
        TraceParams.bTraceComplex = true;

        // Perform the raycast.
        bool bHit = GetWorld()->LineTraceMultiByChannel(HitResult, CameraLocation, TraceEnd, ECC_Visibility, TraceParams);

        if (!bHit)
        {
            UE_LOG(LogTemp, Warning, TEXT("Nothing Was Hit"));
            return;
        }

        for (auto HitActor : HitResult) {
            APopUpZombieActor* PopUpZombieActor = Cast<APopUpZombieActor>(HitActor.GetActor());
            if (PopUpZombieActor)
            {
                if (!PopUpZombieActor->bHasPoppedUp) {
                    break;
                }

                if (Cast<USphereComponent>(HitActor.GetComponent()) == PopUpZombieActor->HeadSphereComponent) {
                    GameInstance->Score += 200;
                    UE_LOG(LogTemp, Warning, TEXT("%d"), GameInstance->Score);
                    PopUpZombieActor->Destroy();
                    break;
                }

                if (Cast<USphereComponent>(HitActor.GetComponent()) == PopUpZombieActor->BodySphereComponent) {
                    GameInstance->Score += 100;
                    UE_LOG(LogTemp, Warning, TEXT("%d"), GameInstance->Score);
                    PopUpZombieActor->Destroy();
                    break;
                }
            }
        }
    }
    
}