// Fill out your copyright notice in the Description page of Project Settings.


#include "SimpNeed.h"

FString USimpNeed::ToString() const
{
	return FString::Printf(TEXT("Hunger: %f\n"), Hunger);
}
