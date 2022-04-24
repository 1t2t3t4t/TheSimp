// Fill out your copyright notice in the Description page of Project Settings.


#include "UserHudWidget.h"

void UUserHudWidget::Report(const USimpNeed* Needs) const
{
	if (Needs)
	{
		HungerBar->SetPercent(Needs->Hunger / 100.f);
	}
}
