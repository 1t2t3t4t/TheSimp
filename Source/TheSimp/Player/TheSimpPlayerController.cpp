// Fill out your copyright notice in the Description page of Project Settings.


#include "TheSimpPlayerController.h"

#include "PlayerControl.h"
#include "Blueprint/UserWidget.h"
#include "TheSimp/UI/ScrollSlotWidget.h"


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
	ShowHudWidget();
}

// Called every frame
void ATheSimpPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (UserHud && GetControlledSimp())
	{
		UserHud->Report(GetControlledSimp()->GetNeeds());
	}
}

#pragma region UI Handle

UScrollSlotWidget* ATheSimpPlayerController::GetBuildModeScrollSlotWidget() const
{
	if (!BuildModeWidget)
	{
		return nullptr;
	}
	
	UWidget* ScrollSlot = BuildModeWidget->GetWidgetFromName(TEXT("ScrollSlot"));
	return Cast<UScrollSlotWidget>(ScrollSlot);
}

ASimp* ATheSimpPlayerController::GetControlledSimp() const
{
	if (const APlayerControl* Control = Cast<APlayerControl>(GetPawn()))
	{
		if (Control->GetControlSimp())
		{
			return Control->GetControlSimp();
		}
	}
	return nullptr;
}

void ATheSimpPlayerController::ShowBuildWidget()
{
	if (!BuildModeWidget)
	{
		BuildModeWidget = CreateWidget(this, BuildModeWidgetClass);
	}
	
	BuildModeWidget->AddToViewport();
}

void ATheSimpPlayerController::HideBuildWidget() const
{
	if (BuildModeWidget)
	{
		BuildModeWidget->RemoveFromViewport();
	}
}

void ATheSimpPlayerController::ShowHudWidget()
{
	if (!UserHud)
	{
		UserHud = CreateWidget<UUserHudWidget>(this, UserHudClass);
	}
	
	UserHud->AddToViewport();
}

void ATheSimpPlayerController::HideHudWidget() const
{
	if (UserHud)
	{
		UserHud->RemoveFromViewport();
	}
}

#pragma endregion 

