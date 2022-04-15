// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseBuildingAsset.h"
#include "GameFramework/Actor.h"
#include "SimpObject.generated.h"

UCLASS()
class THESIMP_API ASimpObject : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASimpObject();

	void Init(const UBaseBuildingAsset* Asset) const; 

private:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* StaticMeshComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
