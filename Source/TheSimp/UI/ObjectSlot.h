// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ObjectSlot.generated.h"

DECLARE_EVENT_OneParam(UObjectSlot, FOnClickedEvent, const int32);

UCLASS(Abstract)
class THESIMP_API UObjectSlot : public UUserWidget
{
	GENERATED_BODY()

public:
	FOnClickedEvent OnClicked;
	
	void Set(const FText Text, UTexture2D* Image, const int32 NewIndex);

protected:
	virtual void NativeOnInitialized() override;
	
private:
	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	class UButton* SlotButton;
	
	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	class UTextBlock* NameText;

	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	class UImage* ObjectImage;

	int32 Index = -1;
	
	UFUNCTION()
	void OnButtonClicked();
};
