// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerStateMachineComponent.h"

#include "DrawDebugHelpers.h"
#include "FBuildState.h"
#include "FPlayState.h"
#include "Kismet/GameplayStatics.h"

UPlayerStateMachineComponent::UPlayerStateMachineComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UPlayerStateMachineComponent::Click(const FHitResult Result) const
{
	if (CurrentState)
	{
		CurrentState->Click(Result);
	}
}

void UPlayerStateMachineComponent::InteractWorld(const FHitResult Result) const
{
	DrawDebugSphere(GetWorld(), Result.ImpactPoint, 30.f, 6.f, FColor::Red, false, 10);
	
	if (CurrentState)
	{
		CurrentState->InteractWorld(Result);
	}
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
		CurrentState = MakeUnique<FBuildState>();
		break;
	default: ;
	}

	const AActor* Owner = GetOwner();
	if (CurrentState && Owner && Owner->InputComponent)
	{
		CurrentState->SetUpInput(Owner->InputComponent);
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

