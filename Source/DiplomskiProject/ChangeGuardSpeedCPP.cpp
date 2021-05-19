// Fill out your copyright notice in the Description page of Project Settings.


#include "ChangeGuardSpeedCPP.h"
#include "Guard_NPC.h"
#include "Guard_AI.h"
#include "GameFramework/CharacterMovementComponent.h"

UChangeGuardSpeedCPP::UChangeGuardSpeedCPP()
{
	// Set flag when service is called
	bNotifyBecomeRelevant = true;
	NodeName = TEXT("Change Guard Speed");
}

void UChangeGuardSpeedCPP::OnBecomeRelevant(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
	Super::OnBecomeRelevant(owner_comp, node_memory);

	// Get NPC controller
	auto const controller = owner_comp.GetAIOwner();
	
	// Check cast
	if (controller)
	{
		// Get NPC
		AGuard_NPC* npc = Cast<AGuard_NPC>(controller->GetPawn());

		// Check cast
		if (npc)
		{
			// Set NPC max walk speed
			npc->GetCharacterMovement()->MaxWalkSpeed = speed;
		}
	}
}

FString UChangeGuardSpeedCPP::GetStaticServiceDescription() const
{
	return FString("Changes Guard's walking speed.");
}
