// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "GameFramework/Actor.h"
#include "ConsumableItem.generated.h"

UCLASS()
class THESIMP_API AConsumableItem : public AItem
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AConsumableItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Interact(ASimp* InteractActor) override;

private:
	UPROPERTY(EditDefaultsOnly)
	float HungerFill = 10.f;
};
