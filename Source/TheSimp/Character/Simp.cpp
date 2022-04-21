// Fill out your copyright notice in the Description page of Project Settings.


#include "Simp.h"

#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ASimp::ASimp()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ASimp::BeginPlay()
{
	Super::BeginPlay();
}

float ASimp::GetSpeedPerc() const
{
	const UCharacterMovementComponent* Movement = GetCharacterMovement();
	return GetVelocity().Size() / Movement->MaxWalkSpeed;
}

// Called every frame
void ASimp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}