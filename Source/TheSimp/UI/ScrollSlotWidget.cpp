// Fill out your copyright notice in the Description page of Project Settings.


#include "ScrollSlotWidget.h"

#include "Components/GridPanel.h"

void UScrollSlotWidget::SetItems(const TArray<FScrollSlotItem> Items) const
{
	int32 Row = 0;
	int32 Column = 0;

	for (const auto Item : Items)
	{
		const auto Widget = CreateWidget<UObjectSlot>(GetOwningPlayer(), ObjectSlotClass);
		Widget->Set(Item.Text, Item.Image, Column);
		SlotPanel->AddChildToGrid(Widget, Row, Column);
		Widget->OnClicked.AddUObject(this, &UScrollSlotWidget::OnClicked);
		Column++;
	}
}

void UScrollSlotWidget::OnClicked(const int32 Index) const
{
	if (OnSlotClicked.IsBound())
	{
		OnSlotClicked.Broadcast(Index);
	}
}
