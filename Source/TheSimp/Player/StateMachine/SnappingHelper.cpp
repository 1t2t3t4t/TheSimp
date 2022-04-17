// Fill out your copyright notice in the Description page of Project Settings.


#include "SnappingHelper.h"

#include "Kismet/KismetMathLibrary.h"
#include "TheSimp/Building/SimpObject.h"

static constexpr float SnapOffset = 0.1;

FHitResult FindMinDist(const TArray<FHitResult>& Results, const FVector Location)
{
	FHitResult Result = Results[0];
	float MinDist = 9999;
	for (auto& HitRes : Results)
	{
		const float Dist = UKismetMathLibrary::Vector_Distance(Location, HitRes.ImpactPoint);
		if (Dist < MinDist)
		{
			Result = HitRes;
			MinDist = Dist;
		}
	}

	return Result;
}

ESnapSlot FSnappingHelper::CheckSnap(const TArray<FHitResult> OverlapInfos, const FVector Location,
                                     const FVector MeshSize, FVector& Out)
{
	const TArray<FHitResult> Results = OverlapInfos.FilterByPredicate([](const FHitResult& Info) -> bool
	{
		return Cast<ASimpObject>(Info.GetActor()) != nullptr;
	});
	if (Results.Num() == 0)
	{
		return ESnapSlot::None;
	}

	const FHitResult Result = FindMinDist(Results, Location);
	const ASimpObject* Object = Cast<ASimpObject>(Result.GetActor());
	const FVector LocalToObjectLocation = UKismetMathLibrary::InverseTransformLocation(
		Object->GetActorTransform(), Location);
	const FVector ObjectSize = Object->GetMesh()->Bounds.GetBox().GetSize();

	Out = Object->GetActorLocation();

	if (LocalToObjectLocation.X <= 0)
	{
		Out.X -= ObjectSize.X + SnapOffset;
		return ESnapSlot::Below;
	}
	if (LocalToObjectLocation.X >= ObjectSize.X)
	{
		Out.X += MeshSize.X + SnapOffset;
		return ESnapSlot::Above;
	}
	if (LocalToObjectLocation.Y >= 0)
	{
		Out.Y += MeshSize.Y + SnapOffset;
		return ESnapSlot::Right;
	}
	if (LocalToObjectLocation.Y <= -ObjectSize.Y)
	{
		Out.Y -= ObjectSize.Y + SnapOffset;
		return ESnapSlot::Left;
	}

	return ESnapSlot::None;
}
