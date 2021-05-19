// Fill out your copyright notice in the Description page of Project Settings.


#include "HealPlayerCPP.h"
#include "DiplomskiProjectCharacter.h"
#include "Medic_NPC.h"
#include "Medic_AI.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Medic_blackboard_keys.h"

UHealPlayerCPP::UHealPlayerCPP(FObjectInitializer const& object_initializer)
{
	NodeName = TEXT("Heal Player");
}

EBTNodeResult::Type UHealPlayerCPP::ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
	// Get NPC and it's controller
	AMedic_AI* npc_controller = Cast<AMedic_AI>(owner_comp.GetAIOwner());
	AMedic_NPC* npc = Cast<AMedic_NPC>(npc_controller->GetPawn());

	// Get player character
	ADiplomskiProjectCharacter* player = Cast<ADiplomskiProjectCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	// Check casts
	if (npc_controller && npc && player)
	{
		// Heal player
		player->UpdatePlayerHealth(npc->GetHealAmount());
		// Lower medic's Stored Health
		npc->UpdateStoredHealth((-1) * npc->GetHealAmount());

		// If Player is at full health
		if (player->GetPlayerHealth() == player->GetMaxHealth())
		{
			// Stop healing Player
			npc_controller->GetBlackboard()->SetValueAsBool(bb_keys::player_needs_healing, false);
		}
		
		// If Medic has no charge left
		if (npc->GetStoredHealth() == 0)
		{
			npc_controller->GetBlackboard()->SetValueAsBool(bb_keys::no_charge, true);
		}

		// Finish task with success
		FinishLatentTask(owner_comp, EBTNodeResult::Succeeded);
		return EBTNodeResult::Succeeded;
	}

	// Finish task with fail
	FinishLatentTask(owner_comp, EBTNodeResult::Failed);
	return EBTNodeResult::Failed;
}
