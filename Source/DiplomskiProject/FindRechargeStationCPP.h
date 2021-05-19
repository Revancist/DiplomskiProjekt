// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "FindRechargeStationCPP.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class DIPLOMSKIPROJECT_API UFindRechargeStationCPP : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	// Constructor
	UFindRechargeStationCPP(FObjectInitializer const& object_initializer);

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory) override;
};
