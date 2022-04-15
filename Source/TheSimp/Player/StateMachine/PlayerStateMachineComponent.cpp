// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerStateMachineComponent.h"

#include "DrawDebugHelpers.h"
#include "BuildState.h"
#include "UPlayState.h"
#include "Kismet/GameplayStatics.h"
#include "TheSimp/EnumHelper.h"
#include "TheSimp/Player/TheSimpPlayerController.h"

UPlayerStateMachineComponent::UPlayerStateMachineComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UPlayerStateMachineComponent::SetupInput(UInputComponent* InputComponent)
{
	InputComponent->BindAction(TEXT("ToggleBuild"), IE_Pressed, this, &UPlayerStateMachineComponent::ToggleBuildMode);
}

void UPlayerStateMachineComponent::ToggleBuildMode()
{
	const EPlayerMode CurrentMode = GetCurrentPlayerMode();
	const EPlayerMode NewMode = [&]()
	{
		switch (CurrentMode)
		{
		case EPlayerMode::Unknown:
			return EPlayerMode::Build;
		case EPlayerMode::Play:
			return EPlayerMode::Build;
		case EPlayerMode::Build:
			return EPlayerMode::Play;
		}
		return EPlayerMode::Unknown;
	}();
	GetGameMode()->CurrentMode = NewMode;
	UpdateState();
}

void UPlayerStateMachineComponent::Click(const FHitResult Result, const FPlayerContext Context) const
{
	if (CurrentState)
	{
		CurrentState->Click(Result, Context, this);
	}
}

void UPlayerStateMachineComponent::InteractWorld(const FHitResult Result, const FPlayerContext Context) const
{
	DrawDebugSphere(GetWorld(), Result.ImpactPoint, 30.f, 6.f, FColor::Red, false, 10);
	
	if (CurrentState)
	{
		CurrentState->InteractWorld(Result, Context, this);
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
	ATheSimpPlayerController* PlayerController = GetPlayerController();
	switch (Mode)
	{
	case EPlayerMode::Play:
		CurrentState = NewObject<UPlayState>();
		PlayerController->HideBuildWidget();
		break;
	case EPlayerMode::Build:
		CurrentState = NewObject<UBuildState>();
		PlayerController->ShowBuildWidget();
		break;
	default: ;
	}

	if (GEngine)
	{
		const FString Text = FString::Printf(TEXT("Current mode update: %s"), *EnumHelper::ToString(GetCurrentPlayerMode()));
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green, Text);
	}
	CurrentState->Begin();
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

ATheSimpPlayerController* UPlayerStateMachineComponent::GetPlayerController() const
{
	if (const APawn* PawnOwner = Cast<APawn>(GetOwner()))
	{
		return Cast<ATheSimpPlayerController>(PawnOwner->GetController());
	}
	return nullptr;
}

AActor* UPlayerStateMachineComponent::SpawnActor(
	UClass* Class,
	FTransform const& Transform,
	const FActorSpawnParameters& SpawnParameters) const
{
	return GetWorld()->SpawnActor(Class, &Transform, SpawnParameters);
}
