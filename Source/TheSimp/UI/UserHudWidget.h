// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "TheSimp/Character/SimpNeed.h"
#include "UserHudWidget.generated.h"

class USimpNeed;

UCLASS(Abstract)
class THESIMP_API UUserHudWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void Report(const USimpNeed* Needs) const;
	
private:
	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	UProgressBar* HungerBar;
};
