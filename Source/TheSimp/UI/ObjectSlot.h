// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ObjectSlot.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class THESIMP_API UObjectSlot : public UUserWidget
{
	GENERATED_BODY()

public:
	void Set(const FText Text, UTexture2D* Image) const;

private:
	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	class UTextBlock* NameText;

	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	class UImage* ObjectImage;
};
