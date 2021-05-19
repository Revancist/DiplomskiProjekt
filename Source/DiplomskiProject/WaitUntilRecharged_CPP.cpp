// Fill out your copyright notice in the Description page of Project Settings.


#include "WaitUntilRecharged_CPP.h"
#include "Medic_NPC.h"
#include "Medic_AI.h"
#include "MedicStation.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "Medic_blackboard_keys.h"

// Set name of node in Behavior Tree
UWaitUntilRecharged_CPP::UWaitUntilRecharged_CPP(FObjectInitializer const& object_initializer)
{
	NodeName = TEXT("Wait until Recharged");
}

EBTNodeResult::Type UWaitUntilRecharged_CPP::ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
	// Get NPC controller
	AMedic_AI* npc_controller = Cast<AMedic_AI>(owner_comp.GetAIOwner());
	if (npc_controller)
	{
		// Get NPC
		AMedic_NPC* npc = Cast<AMedic_NPC>(npc_controller->GetPawn());
		// Update NPC Stored Health
		npc->UpdateStoredHealth(1);
		
		// Update blackboard no charge value
		npc_controller->GetBlackboard()->SetValueAsBool(bb_keys::no_charge, false);

		// If NPC is at full Stored Health
		if (npc->GetStoredHealth() == npc->GetMaxStoredHealth())
		{
			// Set blackboard value for full charge
			npc_controller->GetBlackboard()->SetValueAsBool(bb_keys::low_charge, false);
		}

		// Finish task with success
		FinishLatentTask(owner_comp, EBTNodeResult::Succeeded);
		return EBTNodeResult::Succeeded;
	}
	// Finish task with fail
	FinishLatentTask(owner_comp, EBTNodeResult::Failed);
	return EBTNodeResult::Failed;
}