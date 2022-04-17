#include "BuildState.h"

#include "Engine/AssetManager.h"
#include "Kismet/GameplayStatics.h"
#include "TheSimp/MaterialAsset.h"
#include "TheSimp/Building/ConstructionAsset.h"
#include "TheSimp/Building/SimpObject.h"

void UBuildState::Begin()
{
	UAssetManager& AssetManager = UAssetManager::Get();
	TArray<FPrimaryAssetId> Ids;
	AssetManager.GetPrimaryAssetIdList(TEXT("Construction"), Ids);
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

void UBuildState::Click(const FHitResult Result, const FPlayerContext Context, const IStateCommand* Command)
{
	UAssetManager& AssetManager = UAssetManager::Get();
	TArray<UObject*> Objs;
	bool bFound = AssetManager.GetPrimaryAssetObjectList(TEXT("Construction"), Objs);
	if (Objs.Num() >= 1 && bFound)
	{
		if (const UConstructionAsset* Asset = Cast<UConstructionAsset>(Objs[0]))
		{
			FTransform Trans;
			Trans.SetLocation(Result.ImpactPoint + Result.ImpactNormal);
			const ASimpObject* Object = Cast<ASimpObject>(Command->SpawnActor(ASimpObject::StaticClass(), Trans));
			Object->Init(Asset);
			
			TArray<UObject*> Mats;
			AssetManager.GetPrimaryAssetObjectList(UMaterialAsset::AssetType, Mats);
			
			if (const UMaterialAsset* Mat = Cast<UMaterialAsset>(Mats[0]))
			{
				Object->SetMaterial(Mat);
			}
		}
	}
}

void UBuildState::InteractWorld(const FHitResult Result, const FPlayerContext Context, const IStateCommand* Command)
{
	// No interaction in build mode.
}

