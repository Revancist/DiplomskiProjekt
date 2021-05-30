// Fill out your copyright notice in the Description page of Project Settings.


#include "StopInvestigatingCPP.h"
#include "Guard_AI.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "guard_blackboard.h"

UStopInvestigatingCPP::UStopInvestigatingCPP(FObjectInitializer const& object_initializer)
{
	NodeName = TEXT("Stop Investigating");
}

EBTNodeResult::Type UStopInvestigatingCPP::ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
	// Get blackboard key and set it to false
	AGuard_AI* const controller = Cast<AGuard_AI>(owner_comp.GetAIOwner());

	if (controller)
	{
		controller->GetBlackboard()->SetValueAsBool(bb_keys::is_investigating, false);

		// Finish with success
		FinishLatentTask(owner_comp, EBTNodeResult::Succeeded);
		return EBTNodeResult::Succeeded;
	}

	// Finish with Fail
	FinishLatentTask(owner_comp, EBTNodeResult::Failed);
	return EBTNodeResult::Failed;
}