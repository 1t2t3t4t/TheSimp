#include "UPlayState.h"

#include "AIController.h"
#include "TheSimp/Character/Simp.h"

void UPlayState::Begin()
{
}

void UPlayState::Click(const FHitResult Result, const FPlayerContext Context, const IStateCommand* Command)
{
	if (Context.ControlSimp)
	{
		if (AAIController* Controller = Context.ControlSimp->GetController<AAIController>())
		{
			Controller->MoveTo(Result.ImpactPoint);
		}
	}
}

void UPlayState::InteractWorld(const FHitResult Result, const FPlayerContext Context, const IStateCommand* Command)
{
	
}
