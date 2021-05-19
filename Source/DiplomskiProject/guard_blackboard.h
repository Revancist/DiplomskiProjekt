#pragma once

#include "Runtime/Core/Public/UObject/NameTypes.h"
#include "Runtime/Core/Public/Containers/UnrealString.h"

namespace bb_keys
{
	TCHAR const* const patrol_path_vector = TEXT("PatrolPathVector");
	TCHAR const* const patrol_path_index = TEXT("PatrolPathIndex");
	TCHAR const* const path_looping = TEXT("PathLooping");
	TCHAR const* const direction = TEXT("Direction");
	TCHAR const* const wait_time = TEXT("WaitTime");
	TCHAR const* const can_see_player = TEXT("CanSeePlayer");
	TCHAR const* const target_location = TEXT("TargetLocation");
	TCHAR const* const chase_status = TEXT("ChaseStatus");
	TCHAR const* const player_in_melee = TEXT("PlayerIsInMeleeRange");
	TCHAR const* const is_investigating = TEXT("IsInvestigating");
}