// Fill out your copyright notice in the Description page of Project Settings.


#include "SimpNeedComponent.h"

#include "SimpNeed.h"

static constexpr float StatsReductionRate = 0.5f;

USimpNeedComponent::USimpNeedComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.TickInterval = 1.0f;
}

// Called when the game starts
void USimpNeedComponent::BeginPlay()
{
	Super::BeginPlay();
	Needs = NewObject<USimpNeed>();
	GetWorld()->GetTimerManager().SetTimer(NeedsReductionHandle, this, &USimpNeedComponent::NeedsReducer, StatsReductionRate, true);
}


// Called every frame
void USimpNeedComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                        FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (Needs)
	{
		UE_LOG(LogTemp, Warning, TEXT("Needs Report %s"), *Needs->ToString());
	}
}

void USimpNeedComponent::NeedsReducer()
{
	if (Needs)
	{
		Needs->Hunger -= 0.3f;
	}
}

USimpNeed* USimpNeedComponent::GetNeeds() const
{
	return Needs;
}

