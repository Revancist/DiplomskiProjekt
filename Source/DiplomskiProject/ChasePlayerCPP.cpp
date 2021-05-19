// Fill out your copyright notice in the Description page of Project Settings.


#include "ChasePlayerCPP.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

UChasePlayerCPP::UChasePlayerCPP(FObjectInitializer const& object_initializer)
{
	NodeName = TEXT("Chase Player");
}

EBTNodeResult::Type UChasePlayerCPP::ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
	return EBTNodeResult::Type();
}
