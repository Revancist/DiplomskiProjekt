// Fill out your copyright notice in the Description page of Project Settings.


#include "ChangeGuardSpeedCPP.h"
#include "Guard_NPC.h"
#include "Guard_AI.h"
#include "GameFramework/CharacterMovementComponent.h"

UChangeGuardSpeedCPP::UChangeGuardSpeedCPP()
{
	bNotifyBecomeRelevant = true;
	NodeName = TEXT("Change Guard Speed");
}

void UChangeGuardSpeedCPP::OnBecomeRelevant(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
	Super::OnBecomeRelevant(owner_comp, node_memory);

	// Get AI
	auto const controller = owner_comp.GetAIOwner();
	if (controller)
	{
		// Get NPC
		AGuard_NPC* const npc = Cast<AGuard_NPC>(controller->GetPawn());
		if (npc)
		{
			npc->GetCharacterMovement()->MaxWalkSpeed = speed;
		}
	}
}

FString UChangeGuardSpeedCPP::GetStaticServiceDescription() const
{
	return FString("Change Guard's speed.");
}
