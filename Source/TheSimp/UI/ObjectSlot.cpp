// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectSlot.h"

#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void UObjectSlot::Set(const FText Text, UTexture2D* Image, const int32 NewIndex)
{
	if (NameText)
	{
		NameText->SetText(Text);
	}

	if (Image)
	{
		ObjectImage->SetBrushFromTexture(Image);
	}

	Index = NewIndex;
}

void UObjectSlot::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	SlotButton->OnClicked.AddDynamic(this, &UObjectSlot::OnButtonClicked);
}

void UObjectSlot::OnButtonClicked()
{
	if (OnClicked.IsBound())
	{
		OnClicked.Broadcast(Index);
	}
}
