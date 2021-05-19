// Fill out your copyright notice in the Description page of Project Settings.


#include "FindLocationNearPlayerCPP.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Runtime/NavigationSystem/Public/NavigationSystem.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Stalker_AI.h"
#include "Stalker_NPC.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "GameFramework/Character.h"
#include "DiplomskiProjectCharacter.h"
#include "Stalker_blackboard_keys.h"

UFindLocationNearPlayerCPP::UFindLocationNearPlayerCPP(FObjectInitializer const& object_initializer)
{
	NodeName = TEXT("Find Location near Player");
}

// Find a location near Player
EBTNodeResult::Type UFindLocationNearPlayerCPP::ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
	// Get NPC, NPC's location and the AI controller
	auto const npc_controller = Cast<AStalker_AI>(owner_comp.GetAIOwner());
	if (npc_controller)
	{
		auto const npc = npc_controller->GetPawn();
		auto const npc_location = npc->GetActorLocation();

		// Cast npc to stalker
		AStalker_NPC* stalker = Cast<AStalker_NPC>(npc);
		// Get Player character
		ADiplomskiProjectCharacter* player = Cast<ADiplomskiProjectCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

		// Check if casts were successful
		if (player && stalker)
		{
			// Find Player location
			FVector const player_location = player->GetActorLocation();

			// Find location near Player
			FVector delta = npc_location - player_location;
			delta = delta.GetSafeNormal();
			FVector target_location = stalker->GetFollowDistance() * delta + player_location;

			// Set target location and finish task
			npc_controller->GetBlackboard()->SetValueAsVector(bb_keys::target_location, target_location);
			return EBTNodeResult::Succeeded;
		}
		return EBTNodeResult::Failed;
	}
	return EBTNodeResult::Failed;
}
