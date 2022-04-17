#include "BuildState.h"

#include "Engine/AssetManager.h"
#include "Kismet/GameplayStatics.h"
#include "TheSimp/MaterialAsset.h"
#include "TheSimp/Building/ConstructionAsset.h"
#include "TheSimp/Building/SimpObject.h"
#include "TheSimp/Player/PlayerControl.h"

void UBuildState::Begin()
{
	UAssetManager& AssetManager = UAssetManager::Get();
	TArray<FPrimaryAssetId> Ids;
	AssetManager.GetPrimaryAssetIdList(UConstructionAsset::AssetType, Ids);
	AssetManager.GetPrimaryAssetIdList(UMaterialAsset::AssetType, Ids);

	UE_LOG(LogTemp, Warning, TEXT("Assets %d"), Ids.Num());
	
	const FStreamableDelegate Delegate = FStreamableDelegate::CreateUObject(this, &UBuildState::OnAssetLoaded);
	AssetManager.LoadPrimaryAssets(Ids, {}, Delegate);
}

void UBuildState::OnAssetLoaded()
{
	UE_LOG(LogTemp, Warning, TEXT("Asset Loaded"));
	bIsAssetLoaded = true;
}

ASimpObject* UBuildState::SpawnObjectIfNeeded(const IStateCommand* Command, int32 Idx, const FTransform Location) const
{
	if (CurrentObject != nullptr)
	{
		return nullptr;
	}
	UAssetManager& AssetManager = UAssetManager::Get();
	TArray<UObject*> Objs;
	const bool bFound = AssetManager.GetPrimaryAssetObjectList(UConstructionAsset::AssetType, Objs);
	if (Objs.Num() >= 1 && bFound)
	{
		if (const UConstructionAsset* Asset = Cast<UConstructionAsset>(Objs[0]))
		{;
			ASimpObject* Object = Cast<ASimpObject>(Command->SpawnActor(ASimpObject::StaticClass(), Location));
			Object->Init(Asset);
			
			TArray<UObject*> Mats;
			AssetManager.GetPrimaryAssetObjectList(UMaterialAsset::AssetType, Mats);
			
			if (const UMaterialAsset* Mat = Cast<UMaterialAsset>(Mats[0]))
			{
				Object->SetMaterial(Mat);
			}
			return Object;
		}
	}

	return nullptr;
}

UMaterialAsset* UBuildState::GetBuildMaterial(const bool bIsValid) const
{
	UAssetManager& AssetManager = UAssetManager::Get();
	TArray<UObject*> Mats;
	const bool bLoaded = AssetManager.GetPrimaryAssetObjectList(UMaterialAsset::AssetType, Mats);
	if (!bLoaded)
	{
		return nullptr;
	}

	const FString Name = bIsValid ? TEXT("Valid") : TEXT("Invalid");
	const auto Mat = Mats.FindByPredicate([Name](const UObject* Obj)
	{
		if (const UMaterialAsset* MaterialAsset = Cast<UMaterialAsset>(Obj))
		{
			return MaterialAsset->Name == Name;
		}

		return false;
	});

	if (Mat == nullptr)
	{
		return nullptr;
	}
	
	if (UMaterialAsset* MaterialAsset = Cast<UMaterialAsset>(*Mat))
	{
		return MaterialAsset;
	}

	return nullptr;
}

void UBuildState::Tick(const float DeltaTime, const IStateCommand* Command)
{
	IPlayerStateHandler::Tick(DeltaTime, Command);
	if (const APlayerControl* PlayerControl = Cast<APlayerControl>(Owner))
	{
		if (ATheSimpPlayerController* Controller = Cast<ATheSimpPlayerController>(PlayerControl->GetController()))
		{
			FHitResult Result;
			Controller->GetHitResultUnderCursor(ECC_Visibility, false, Result);
			FTransform Transform;
			Transform.SetLocation(Result.ImpactPoint + Result.ImpactNormal);
			if (!CurrentObject)
			{
				CurrentObject = SpawnObjectIfNeeded(Command, 0, Transform);
			}
			CurrentObject->SetActorTransform(Transform);
			if (const UMaterialAsset* Mat = GetBuildMaterial(true))
			{
				CurrentObject->SetMaterial(Mat);
			}
		}
	}
}

void UBuildState::Click(const FHitResult Result, const FPlayerContext Context, const IStateCommand* Command)
{
	
}

void UBuildState::InteractWorld(const FHitResult Result, const FPlayerContext Context, const IStateCommand* Command)
{
	// No interaction in build mode.
}

