// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ObjectSlot.h"
#include "Blueprint/UserWidget.h"
#include "ScrollSlotWidget.generated.h"

USTRUCT(BlueprintType)
struct FScrollSlotItem
{
	GENERATED_BODY()
	FScrollSlotItem() = default;
	
	FText Text;

	UPROPERTY(Transient)
	UTexture2D* Image;
};

UCLASS(Abstract)
class THESIMP_API UScrollSlotWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetItems(const TArray<FScrollSlotItem> Items) const;
	
private:
	TArray<FScrollSlotItem> CurrentItems;
	
    UPROPERTY(EditDefaultsOnly, meta= (BindWidget))
    class UGridPanel* SlotPanel;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UObjectSlot> ObjectSlotClass;
};
