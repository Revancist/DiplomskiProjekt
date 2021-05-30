// Fill out your copyright notice in the Description page of Project Settings.


#include "UpdateHasBeenChasingCPP.h"
#include "Guard_AI.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "guard_blackboard.h"

UUpdateHasBeenChasingCPP::UUpdateHasBeenChasingCPP(FObjectInitializer const& object_initializer)
{
	NodeName = TEXT("Update Has Been Chasing");
}

EBTNodeResult::Type UUpdateHasBeenChasingCPP::ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
	// Get AI controller
	AGuard_AI* const controller = Cast<AGuard_AI>(owner_comp.GetAIOwner());

	if (controller)
	{
		controller->GetBlackboard()->SetValueAsBool(bb_keys::has_been_chasing, false);

		// Finish with success
		FinishLatentTask(owner_comp, EBTNodeResult::Succeeded);
		return EBTNodeResult::Succeeded;
	}

	// Finish with fail
	FinishLatentTask(owner_comp, EBTNodeResult::Failed);
	return EBTNodeResult::Failed;
}