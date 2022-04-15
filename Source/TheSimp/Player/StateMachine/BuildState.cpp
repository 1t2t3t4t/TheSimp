#include "BuildState.h"

#include "Engine/AssetManager.h"

UBuildState::UBuildState(): CurrentObject(nullptr)
{
	UAssetManager& AssetManager = UAssetManager::Get();
	TArray<FPrimaryAssetId> Ids;
	AssetManager.GetPrimaryAssetIdList(TEXT("Construction"), Ids);
	UE_LOG(LogTemp, Warning, TEXT("Assets %d"), Ids.Num());
}

void UBuildState::Click(const FHitResult Result, const FPlayerContext Context, const IStateCommand* Command)
{
	
}

void UBuildState::InteractWorld(const FHitResult Result, const FPlayerContext Context, const IStateCommand* Command)
{
	// No interaction in build mode.
}

void UBuildState::Tick(const float DeltaTime, const FPlayerContext, const IStateCommand* Command)
{
	
}
