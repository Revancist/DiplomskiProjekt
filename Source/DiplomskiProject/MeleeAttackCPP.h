// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "Guard_NPC.h"
#include "MeleeAttackCPP.generated.h"

/**
 * 
 */
UCLASS()
class DIPLOMSKIPROJECT_API UMeleeAttackCPP : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UMeleeAttackCPP(FObjectInitializer const& object_initializer);

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory) override;

private:
	bool MontageHasFinished(AGuard_NPC* const npc);
};
