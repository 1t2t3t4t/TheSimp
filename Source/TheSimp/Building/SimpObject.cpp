// Fill out your copyright notice in the Description page of Project Settings.


#include "SimpObject.h"


// Sets default values
ASimpObject::ASimpObject()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Object Mesh"));
}

void ASimpObject::Init(const UBaseBuildingAsset* Asset) const
{
	UStaticMesh* LoadedMesh = Asset->Mesh.LoadSynchronous();
	if (LoadedMesh)
	{
		StaticMeshComponent->SetStaticMesh(LoadedMesh);
	}
}

void ASimpObject::SetMaterial(const UMaterialAsset* Material) const
{
	if (StaticMeshComponent)
	{
		for (int32 i = 0; i < StaticMeshComponent->GetNumMaterials(); i++)
		{
			StaticMeshComponent->SetMaterial(i, Material->Material);
		}
	}
}

// Called when the game starts or when spawned
void ASimpObject::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASimpObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

