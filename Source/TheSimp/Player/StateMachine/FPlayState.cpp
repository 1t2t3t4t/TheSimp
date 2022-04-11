#include "FPlayState.h"

#include "AIController.h"
#include "TheSimp/Character/Simp.h"

void FPlayState::Click(const FHitResult Result, const FPlayerContext Context)
{
	if (Context.ControlSimp)
	{
		if (AAIController* Controller = Context.ControlSimp->GetController<AAIController>())
		{
			Controller->MoveTo(Result.ImpactPoint);
		}
	}
}

void FPlayState::InteractWorld(const FHitResult Result, const FPlayerContext Context)
{
}
