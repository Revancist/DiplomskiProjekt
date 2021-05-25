// Fill out your copyright notice in the Description page of Project Settings.


#include "IncrementPathIndexCPP.h"
#include "Guard_AI.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Guard_NPC.h"
#include "guard_blackboard.h"
#include <cmath>

UIncrementPathIndexCPP::UIncrementPathIndexCPP(FObjectInitializer const& object_initializer)
{
	NodeName = TEXT("Increment Path Index");
}

EBTNodeResult::Type UIncrementPathIndexCPP::ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
	// Get AI controller
	AGuard_AI* const controller = Cast<AGuard_AI>(owner_comp.GetAIOwner());
	if (controller)
	{
		// Get NPC
		AGuard_NPC* const npc = Cast<AGuard_NPC>(controller->GetPawn());
		if (npc)
		{
			int const points_num = npc->GetPatrolPath()->num();
			int const max_index = points_num - 1;

			// Get current index
			int index = controller->GetBlackboard()->GetValueAsInt(bb_keys::patrol_path_index);
			
			// Check if looping is on and current index is last point
			if (loop && index >= max_index)
			{
				// Set next index to starting point
				controller->GetBlackboard()->SetValueAsInt(bb_keys::patrol_path_index, 0);
				
				//Finish with success
				FinishLatentTask(owner_comp, EBTNodeResult::Succeeded);
				return EBTNodeResult::Succeeded;
			}
			// Set Direction to Reverse if at last index (at the end of patrol path)
			else if (index >= max_index && direction == EDirectionType::Forward)
			{
				direction = EDirectionType::Reverse;
			}
			// Set Direction to Forward if at first index (at the start of patrol path)
			else if (index == 0 && direction == EDirectionType::Reverse)
			{
				direction = EDirectionType::Forward;
			}

			// Increment or decrement index based on direction and set blackboard value
			controller->GetBlackboard()->SetValueAsInt(bb_keys::patrol_path_index, (direction == EDirectionType::Forward ? std::abs(++index) : std::abs(--index)));

			// Finish with success
			FinishLatentTask(owner_comp, EBTNodeResult::Succeeded);
			return EBTNodeResult::Succeeded;
		}
	}

	// Finish with fail
	FinishLatentTask(owner_comp, EBTNodeResult::Failed);
	return EBTNodeResult::Failed;
}
