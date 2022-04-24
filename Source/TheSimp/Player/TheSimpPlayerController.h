// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TheSimp/Character/Simp.h"
#include "TheSimp/UI/ScrollSlotWidget.h"
#include "TheSimp/UI/UserHudWidget.h"
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

	UPROPERTY(EditDefaultsOnly, Category="UI")
	TSubclassOf<UUserHudWidget> UserHudClass;

	UPROPERTY(VisibleAnywhere, Category="UI")
	UUserHudWidget* UserHud;
	
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
	
	void ShowHudWidget();
	void HideHudWidget() const;

	UScrollSlotWidget* GetBuildModeScrollSlotWidget() const;

	ASimp* GetControlledSimp() const;
};
