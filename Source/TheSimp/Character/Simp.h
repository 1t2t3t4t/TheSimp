// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Simp.generated.h"

class USimpNeed;
class USimpNeedComponent;

UCLASS()
class THESIMP_API ASimp : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASimp();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintPure)
	float GetSpeedPerc() const;

	UFUNCTION(BlueprintPure)
	USimpNeed* GetNeeds() const;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere)
	USimpNeedComponent* NeedsComponent;
};
