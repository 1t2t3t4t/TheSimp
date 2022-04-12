// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TheSimpPlayerController.generated.h"

UCLASS()
class THESIMP_API ATheSimpPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category="UI")
	TSubclassOf<UUserWidget> BuildModeWidgetClass;

	UPROPERTY(VisibleAnywhere, Category="UI")
	UUserWidget* BuildModeWidget;
	
	// Sets default values for this actor's properties
	ATheSimpPlayerController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	void ShowBuildWidget();
	void HideBuildWidget() const;
};
