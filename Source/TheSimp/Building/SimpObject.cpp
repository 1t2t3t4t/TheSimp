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
	if (Asset->Mesh.IsValid())
	{
		StaticMeshComponent->SetStaticMesh(Asset->Mesh.Get());
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

