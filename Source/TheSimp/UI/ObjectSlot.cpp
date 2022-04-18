// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectSlot.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"

void UObjectSlot::Set(const FText Text, UTexture2D* Image) const
{
	if (NameText)
	{
		NameText->SetText(Text);
	}

	if (Image)
	{
		ObjectImage->SetBrushFromTexture(Image);
	}
}
