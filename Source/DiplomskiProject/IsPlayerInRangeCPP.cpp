// Fill out your copyright notice in the Description page of Project Settings.


#include "IsPlayerInRangeCPP.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

UIsPlayerInRangeCPP::UIsPlayerInRangeCPP()
{
	// Set flag when service is called
	bNotifyBecomeRelevant = true;
	NodeName = TEXT("Is Player in Range");
}

void UIsPlayerInRangeCPP::OnBecomeRelevant(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
	Super::OnBecomeRelevant(owner_comp, node_memory);

	// Get Player
	ACharacter* const player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
}

FString UIsPlayerInRangeCPP::GetStaticServiceDescription() const
{
	return FString("Check if Player is in determined range.");
}
