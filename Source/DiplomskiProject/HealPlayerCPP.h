// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "HealPlayerCPP.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class DIPLOMSKIPROJECT_API UHealPlayerCPP : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	UHealPlayerCPP(FObjectInitializer const& object_initializer);

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory) override;
};
