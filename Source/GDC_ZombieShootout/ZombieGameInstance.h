// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ZombieGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class GDC_ZOMBIESHOOTOUT_API UZombieGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	int Score = 0;
};
