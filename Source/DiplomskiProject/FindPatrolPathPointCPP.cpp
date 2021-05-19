// Fill out your copyright notice in the Description page of Project Settings.


#include "FindPatrolPathPointCPP.h"
#include "Guard_NPC.h"
#include "Guard_AI.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "guard_blackboard.h"

UFindPatrolPathPointCPP::UFindPatrolPathPointCPP(FObjectInitializer const& object_initializer)
{
	NodeName = TEXT("Find Patrol Path point");
}

// Find Patrol point location
EBTNodeResult::Type UFindPatrolPathPointCPP::ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
	// Get AI controller
	AGuard_AI* const controller = Cast<AGuard_AI>(owner_comp.GetAIOwner());
	// Get NPC
	AGuard_NPC* const npc = Cast<AGuard_NPC>(controller->GetPawn());

	// Check cast
	if (controller && npc)
	{
		/* Get current patrol path point, transform it to a global position and write to blackboard */
		
		// Get current patrol path index
		int const index = controller->GetBlackboard()->GetValueAsInt(bb_keys::patrol_path_index);
		// Get current patrol path from the NPC's reference to the patrol path
		FVector const point = npc->GetPatrolPath()->GetPatrolPoint(index);
		
		// Transform current patrol path point to a global position using it's parent
		FVector const global_point = npc->GetPatrolPath()->GetActorTransform().TransformPosition(point);

		// Write to blackboard
		controller->GetBlackboard()->SetValueAsVector(bb_keys::patrol_path_vector, global_point);

		// Finish with success
		FinishLatentTask(owner_comp, EBTNodeResult::Succeeded);
		return EBTNodeResult::Succeeded;
	}

	// Finish with fail
	FinishLatentTask(owner_comp, EBTNodeResult::Failed);
	return EBTNodeResult::Failed;
}
