// Fill out your copyright notice in the Description page of Project Settings.


#include "FindPlayerLocationCPP.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Runtime/NavigationSystem/Public/NavigationSystem.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "GameFramework/Character.h"
#include "DiplomskiProjectCharacter.h"
#include "guard_blackboard.h"

UFindPlayerLocationCPP::UFindPlayerLocationCPP(FObjectInitializer const& object_initializer)
{
	NodeName = TEXT("Find Player Location");
}

// Find Player location
EBTNodeResult::Type UFindPlayerLocationCPP::ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
	// Get Player character and NPC
	ADiplomskiProjectCharacter* player = Cast<ADiplomskiProjectCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	// Check cast
	if (player)
	{
		// Set blackboard Target Location value 
		owner_comp.GetBlackboardComponent()->SetValueAsVector(bb_keys::target_location, player->GetActorLocation());

		// Finish with success
		FinishLatentTask(owner_comp, EBTNodeResult::Succeeded);
		return EBTNodeResult::Succeeded;
	}

	// Finish with fail
	FinishLatentTask(owner_comp, EBTNodeResult::Failed);
	return EBTNodeResult::Failed;
}
