// Fill out your copyright notice in the Description page of Project Settings.


#include "FindPatrolPointCPP.h"
#include "Guard_AI.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Guard_NPC.h"
#include "guard_blackboard.h"

UFindPatrolPointCPP::UFindPatrolPointCPP(FObjectInitializer const& object_initializer)
{
	NodeName = TEXT("Find Patrol Path Point");
}

EBTNodeResult::Type UFindPatrolPointCPP::ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
	// Get AI controller and check cast
	AGuard_AI* const controller = Cast<AGuard_AI>(owner_comp.GetAIOwner());
	if (controller)
	{
		// Get current Patrol Path index from blackboard
		int const index = controller->GetBlackboard()->GetValueAsInt(bb_keys::patrol_path_index);

		// Use index to get current Patrol Path from NPC's reference to Patrol Path
		AGuard_NPC* const npc = Cast<AGuard_NPC>(controller->GetPawn());
		if (npc)
		{
			FVector const point = npc->GetPatrolPath()->GetPatrolPoint(index);

			// Transform point to global position using it's parent
			FVector const global_point = npc->GetPatrolPath()->GetActorTransform().TransformPosition(point);

			// Write global path point to blackboard
			controller->GetBlackboard()->SetValueAsVector(bb_keys::patrol_path_vector, global_point);

			// Finish with success
			FinishLatentTask(owner_comp, EBTNodeResult::Succeeded);
			return EBTNodeResult::Succeeded;
		}
	}

	// Finish with fail
	FinishLatentTask(owner_comp, EBTNodeResult::Failed);
	return EBTNodeResult::Failed;
}
