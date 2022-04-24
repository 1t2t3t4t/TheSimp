// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TheSimp/TheSimpGameModeBase.h"
#include "SimpNeedComponent.generated.h"

class USimpNeed;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class THESIMP_API USimpNeedComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	USimpNeedComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintPure)
	USimpNeed* GetNeeds() const;
	ATheSimpGameModeBase* GetGameMode() const;

private:
	UPROPERTY(VisibleAnywhere)
	USimpNeed* Needs;

	FTimerHandle NeedsReductionHandle;

	UFUNCTION()
	void NeedsReducer();
};
