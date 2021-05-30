// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "StopInvestigatingCPP.generated.h"

/**
 * 
 */
UCLASS()
class DIPLOMSKIPROJECT_API UStopInvestigatingCPP : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UStopInvestigatingCPP(FObjectInitializer const& object_initializer);

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory) override;
};