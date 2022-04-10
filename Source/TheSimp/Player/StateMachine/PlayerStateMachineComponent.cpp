// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerStateMachineComponent.h"

#include "FPlayState.h"
#include "Kismet/GameplayStatics.h"

UPlayerStateMachineComponent::UPlayerStateMachineComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UPlayerStateMachineComponent::BeginPlay()
{
	Super::BeginPlay();
	UpdateState();
}

void UPlayerStateMachineComponent::UpdateState()
{
	const EPlayerMode Mode = GetCurrentPlayerMode();
	switch (Mode)
	{
	case EPlayerMode::Play:
		CurrentState = MakeUnique<FPlayState>();
		break;
	case EPlayerMode::Build:
		break;
	default: ;
	}
}

EPlayerMode UPlayerStateMachineComponent::GetCurrentPlayerMode() const
{
	if (const ATheSimpGameModeBase* GameMode = GetGameMode())
	{
		return GameMode->CurrentMode;
	}

	return EPlayerMode::Unknown;
}

// Called every frame
void UPlayerStateMachineComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                        FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
}

ATheSimpGameModeBase* UPlayerStateMachineComponent::GetGameMode() const
{
	return Cast<ATheSimpGameModeBase>(UGameplayStatics::GetGameMode(this));
}

