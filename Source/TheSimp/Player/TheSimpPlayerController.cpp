﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "TheSimpPlayerController.h"


// Sets default values
ATheSimpPlayerController::ATheSimpPlayerController()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ATheSimpPlayerController::BeginPlay()
{
	Super::BeginPlay();

	bShowMouseCursor = true;
}

// Called every frame
void ATheSimpPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
