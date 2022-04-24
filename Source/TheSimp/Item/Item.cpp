// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"


// Sets default values
AItem::AItem()
{
	PrimaryActorTick.bCanEverTick = false;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	StaticMeshComponent->SetCollisionProfileName("IgnoreOnlyPawn");
	StaticMeshComponent->SetupAttachment(RootComponent);

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger Box"));
	TriggerBox->SetupAttachment(RootComponent);
}

void AItem::Interact(ASimp* InteractActor)
{
}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();
}
