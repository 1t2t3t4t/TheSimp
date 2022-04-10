// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IPlayerState.h"
#include "Components/ActorComponent.h"
#include "TheSimp/TheSimpGameModeBase.h"
#include "PlayerStateMachineComponent.generated.h"

UCLASS(ClassGroup=(StateMachine), meta=(BlueprintSpawnableComponent))
class THESIMP_API UPlayerStateMachineComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UPlayerStateMachineComponent();

	void Click(const FHitResult Result);
	void InteractWorld(const FHitResult Result);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	void UpdateState();

	virtual EPlayerMode GetCurrentPlayerMode() const;

public:
	TUniquePtr<IPlayerState> CurrentState;
	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

private:
	ATheSimpGameModeBase* GetGameMode() const;
};
