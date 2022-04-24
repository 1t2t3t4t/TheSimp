// Fill out your copyright notice in the Description page of Project Settings.


#include "ConsumableItem.h"

#include "TheSimp/Character/Simp.h"
#include "TheSimp/Character/SimpNeed.h"


// Sets default values
AConsumableItem::AConsumableItem()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AConsumableItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AConsumableItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AConsumableItem::Interact(ASimp* InteractActor)
{
	Super::Interact(InteractActor);

	if (USimpNeed* Needs = InteractActor->GetNeeds())
	{
		Needs->Hunger += HungerFill;
	}
	
	Destroy();
}

