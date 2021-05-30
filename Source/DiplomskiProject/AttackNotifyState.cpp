// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackNotifyState.h"
#include "Runtime/Engine/Classes/Engine/Engine.h"
#include "Components/SkeletalMeshComponent.h"
#include "Guard_NPC.h"

void UAttackNotifyState::NotifyBegin(USkeletalMeshComponent* const mesh, UAnimSequenceBase* const animation, float const total_duration)
{
	if (mesh && mesh->GetOwner())
	{
		if (AGuard_NPC* const character = Cast<AGuard_NPC>(mesh->GetOwner()))
		{
			character->AttackStart();
		}
	}
}

void UAttackNotifyState::NotifyEnd(USkeletalMeshComponent* const mesh, UAnimSequenceBase* const animation)
{
	if (mesh && mesh->GetOwner())
	{
		if (AGuard_NPC* const character = Cast<AGuard_NPC>(mesh->GetOwner()))
		{
			character->AttackEnd();
		}
	}
}