// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TheSimpGameModeBase.generated.h"

UENUM(BlueprintType)
enum class EPlayerMode : uint8
{
	Unknown,
	Play,
	Build
};

UCLASS()
class THESIMP_API ATheSimpGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly)
	EPlayerMode CurrentMode;

	friend class UPlayerStateMachineComponent;
};
