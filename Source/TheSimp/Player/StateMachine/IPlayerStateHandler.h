#pragma once

#include "IPlayerStateHandler.generated.h"

class ASimp;

struct FPlayerContext
{
	ASimp* ControlSimp;

	explicit FPlayerContext(ASimp* ControlSimp)
		: ControlSimp(ControlSimp)
	{
	}
};

class IStateCommand
{
public:
	virtual ~IStateCommand() = default;
	
	virtual AActor* SpawnActor(UClass* Class, FTransform const& Transform, const FActorSpawnParameters& SpawnParameters = FActorSpawnParameters()) const = 0;
};

UINTERFACE(MinimalAPI)
class UPlayerStateHandler : public UInterface
{
	GENERATED_BODY()
};

class IPlayerStateHandler
{
	GENERATED_BODY()
	
public:
	virtual void Begin() = 0;

	virtual void Tick(const float DeltaTime, const IStateCommand* Command) {};
	virtual void Click(const FHitResult Result, const FPlayerContext, const IStateCommand* Command) = 0;
	virtual void InteractWorld(const FHitResult Result, const FPlayerContext Context, const IStateCommand* Command) = 0;
};
