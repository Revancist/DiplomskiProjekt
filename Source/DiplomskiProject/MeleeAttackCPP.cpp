// Fill out your copyright notice in the Description page of Project Settings.


#include "MeleeAttackCPP.h"
#include "Guard_AI.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Engine/LatentActionManager.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimMontage.h"
#include "Animation/AnimInstance.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "DiplomskiProjectCharacter.h"

UMeleeAttackCPP::UMeleeAttackCPP(FObjectInitializer const& object_initializer)
{
    NodeName = TEXT("Melee Attack");
}

EBTNodeResult::Type UMeleeAttackCPP::ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
    // Get AI controller and NPC
    AAIController* const controller = owner_comp.GetAIOwner();
    AGuard_NPC* const npc = Cast<AGuard_NPC>(controller->GetPawn());
    
    // Check cast
    if (controller && npc)
    {
        // If the montage has finished playing, play it again (stops "jittering")
        if (MontageHasFinished(npc))
        {
            npc->MeleeAttack();

            /*// Get player character
            ADiplomskiProjectCharacter* player = Cast<ADiplomskiProjectCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
            if (player)
            {
                // Hurt player
                player->UpdatePlayerHealth(-1 * npc->GetDamage());
            }*/
        }
    }

    // Finish with success
    FinishLatentTask(owner_comp, EBTNodeResult::Succeeded);
    return EBTNodeResult::Succeeded;
}

// Check if montage has finished playing
bool UMeleeAttackCPP::MontageHasFinished(AGuard_NPC* const npc)
{
    return npc->GetMesh()->GetAnimInstance()->Montage_GetIsStopped(npc->GetMontage());
}
