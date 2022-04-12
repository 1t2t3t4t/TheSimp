#pragma once
#include "TheSimpGameModeBase.h"

namespace EnumHelper
{
	inline FString ToString(const EPlayerMode& Mode)
	{
		switch (Mode)
		{
		case EPlayerMode::Unknown:
			return TEXT("Unknown");
		case EPlayerMode::Play:
			return TEXT("Play");
		case EPlayerMode::Build:
			return TEXT("Build");
		}

		return TEXT("Invalid");
	}
}
