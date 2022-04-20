#include "BuildState.h"

#include "SnappingHelper.h"
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

void UBuildState::End()
{
	IPlayerStateHandler::End();
	CurrentObject->Destroy();
	CurrentObject = nullptr;
	Owner = nullptr;

	UAssetManager& AssetManager = UAssetManager::Get();
	TArray<FPrimaryAssetId> Ids;
	AssetManager.GetPrimaryAssetIdList(UConstructionAsset::AssetType, Ids);
	AssetManager.GetPrimaryAssetIdList(UMaterialAsset::AssetType, Ids);

	AssetManager.UnloadPrimaryAssets(Ids);
}

#pragma region Asset

void UBuildState::OnAssetLoaded()
{
	UE_LOG(LogTemp, Warning, TEXT("Asset Loaded"));
	bIsAssetLoaded = true;
	
	const UAssetManager& AssetManager = UAssetManager::Get();
	TArray<UObject*> Objs;
	TArray<FScrollSlotItem> Items;
	const bool bFound = AssetManager.GetPrimaryAssetObjectList(UConstructionAsset::AssetType, Objs);
	if (Objs.Num() >= 1 && bFound)
	{
		for (const auto Obj : Objs)
		{
			if (UConstructionAsset* Asset = Cast<UConstructionAsset>(Obj))
			{
				FScrollSlotItem Item;
				Item.Text = FText::FromString(Asset->Name);
				Item.Image = Asset->Preview.LoadSynchronous();
				Items.Add(Item);

				Constructions.Add(Asset);
			}
		}
	}

	if (const APawn* Pawn = Cast<APawn>(Owner))
	{
		if (const ATheSimpPlayerController* Controller = Cast<ATheSimpPlayerController>(Pawn->GetController()))
		{
			if (Controller->GetBuildModeScrollSlotWidget())
			{
				Controller->GetBuildModeScrollSlotWidget()->SetItems(Items);
				Controller->GetBuildModeScrollSlotWidget()->OnSlotClicked.AddUObject(this, &UBuildState::OnSlotClicked);
			}
		}
	}
}

ASimpObject* UBuildState::SpawnObjectIfNeeded(const IStateCommand* Command, int32 Idx, const FTransform Location) const
{
	if (CurrentObject != nullptr)
	{
		return nullptr;
	}
	if (Idx >= Constructions.Num())
	{
		return nullptr;
	}

	const auto Asset = Constructions[Idx];
	ASimpObject* Object = Cast<ASimpObject>(Command->SpawnActor(ASimpObject::StaticClass(), Location));
	Object->Init(Asset);
	return Object;
}

UMaterialAsset* UBuildState::GetBuildMaterial(const bool bIsValid) const
{
	const UAssetManager& AssetManager = UAssetManager::Get();
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

#pragma endregion 

void UBuildState::UpdateTransform()
{
	if (!CurrentObject)
	{
		return;
	}

	if (const APlayerControl* PlayerControl = Cast<APlayerControl>(Owner))
	{
		if (const ATheSimpPlayerController* Controller = Cast<ATheSimpPlayerController>(PlayerControl->GetController()))
		{
			FHitResult Result;
			Controller->GetHitResultUnderCursor(ECC_Visibility, false, Result);

			TArray<FHitResult> HitResults;
			UKismetSystemLibrary::SphereTraceMultiForObjects(Owner, Result.ImpactPoint, Result.ImpactPoint, 100.f,
			                                                 {UEngineTypes::ConvertToObjectType(ECC_WorldDynamic)},
			                                                 false, {CurrentObject}, EDrawDebugTrace::ForOneFrame,
			                                                 HitResults, true);

			FVector SlotLocation;
			const ESnapSlot Slot = FSnappingHelper::CheckSnap(HitResults, Result.ImpactPoint,
			                                                  CurrentObject->GetMesh()->Bounds.GetBox().GetSize(),
			                                                  SlotLocation);

			FTransform Transform;
			const UConstructionAsset* ConstructionAsset = CurrentObject->GetAsset<UConstructionAsset>();
			if (Slot != ESnapSlot::None && ConstructionAsset && ConstructionAsset->SnappableSlots.Contains(Slot))
			{
				Transform.SetLocation(SlotLocation);
			}
			else
			{
				Transform.SetLocation(Result.ImpactPoint + Result.ImpactNormal);
			}

			CurrentTransform = Transform;
		}
	}
}

void UBuildState::Tick(const float DeltaTime, const IStateCommand* Command)
{
	IPlayerStateHandler::Tick(DeltaTime, Command);
	UpdateTransform();

	if (!bIsAssetLoaded)
	{
		return;
	}
	if (!CurrentObject)
	{
		CurrentObject = SpawnObjectIfNeeded(Command, CurrentIndex, CurrentTransform);
		CurrentObject->GetMesh()->SetGenerateOverlapEvents(true);
		CurrentObject->GetMesh()->SetCollisionProfileName("OverlapAll");
		if (const UMaterialAsset* Mat = GetBuildMaterial(true))
		{
			CurrentObject->SetMaterial(Mat);
		}
	}

	const bool bTestInvalid = CurrentObject->GetMesh()->GetOverlapInfos().Num() > 0;
	if (bTestInvalid != bIsInvalid)
	{
		bIsInvalid = bTestInvalid;
		if (const UMaterialAsset* Mat = GetBuildMaterial(!bIsInvalid))
		{
			CurrentObject->SetMaterial(Mat);
		}
	}

	CurrentObject->SetActorTransform(CurrentTransform);
}

void UBuildState::Click(const FHitResult Result, const FPlayerContext Context, const IStateCommand* Command)
{
	if (bIsInvalid)
	{
		return;
	}

	if (CurrentObject)
	{
		CurrentObject->Destroy();
		CurrentObject = nullptr;
	}

	SpawnObjectIfNeeded(Command, CurrentIndex, CurrentTransform);
}

void UBuildState::InteractWorld(const FHitResult Result, const FPlayerContext Context, const IStateCommand* Command)
{
	if (ASimpObject* Object = Cast<ASimpObject>(Result.GetActor()))
	{
		Object->Destroy();
	}
}

#pragma region UI Interaction

void UBuildState::OnSlotClicked(const int32 Index)
{
	if (Index >= Constructions.Num())
	{
		UE_LOG(LogTemp, Warning, TEXT("Selected OOB index!! %d has only %d"), Index, Constructions.Num());
	}

	CurrentIndex = Index;
	CurrentObject->Destroy();
	CurrentObject = nullptr;
}

#pragma endregion 