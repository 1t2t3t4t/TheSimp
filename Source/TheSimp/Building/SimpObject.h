// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseBuildingAsset.h"
#include "GameFramework/Actor.h"
#include "TheSimp/MaterialAsset.h"
#include "SimpObject.generated.h"

UCLASS()
class THESIMP_API ASimpObject : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASimpObject();

	void Init(UBaseBuildingAsset* Asset);
	void SetMaterial(const UMaterialAsset* Material) const;

	UStaticMeshComponent* GetMesh() const { return StaticMeshComponent; }
	
	template<class TAsset>
	TAsset* GetAsset() const
	{
		return Cast<TAsset>(AssignedAsset);
	}
	
private:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(VisibleAnywhere)
	UBaseBuildingAsset* AssignedAsset;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
