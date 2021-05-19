// Fill out your copyright notice in the Description page of Project Settings.


#include "Medic_AI.h"
#include "Medic_NPC.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "DiplomskiProjectCharacter.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "GameFramework/Character.h"
#include "Medic_blackboard_keys.h"

AMedic_AI::AMedic_AI(FObjectInitializer const& object_initializer)
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> obj(TEXT("BehaviorTree'/Game/NPC/Friendly/Medic/NPC_Friendly_Medic_BT.NPC_Friendly_Medic_BT'"));
	
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (obj.Succeeded())
	{
		btree = obj.Object;
	}

	behavior_tree_component = object_initializer.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("BehaviorComp"));
	blackboard = object_initializer.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("BlackboardComp"));
}

void AMedic_AI::BeginPlay()
{
	Super::BeginPlay();
	// Run behavior tree. (Needs both lines)
	RunBehaviorTree(btree);
	behavior_tree_component->StartTree(*btree);
}

void AMedic_AI::OnPossess(APawn* const pawn)
{
	Super::OnPossess(pawn);
	if (blackboard)
	{
		blackboard->InitializeBlackboard(*btree->BlackboardAsset);
	}
}

void AMedic_AI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	/* Check if the Player is hurt (Player's Current Health < Player's Max Health) */

	// Get Player character
	ADiplomskiProjectCharacter* player = Cast<ADiplomskiProjectCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	
	// Check if cast was successful and Player is hurt
	if (player && player->GetPlayerHealth() < player->GetMaxHealth())
	{
		this->GetBlackboard()->SetValueAsBool(bb_keys::player_needs_healing, true);
	}
	else
	{
		this->GetBlackboard()->SetValueAsBool(bb_keys::player_needs_healing, false);
	}

	/* Check if Medic's stored Health is below recharge point */

	// Get NPC
	AMedic_NPC* npc = Cast<AMedic_NPC>(this->GetPawn());

	// Check if cast was successful and medic needs to recharge
	if (npc && npc->GetStoredHealth() <= npc->GetRechargePoint())
	{
		this->GetBlackboard()->SetValueAsBool(bb_keys::low_charge, true);
		
		// If medic is full
		if (npc->GetStoredHealth() == npc->GetMaxStoredHealth())
		{
			this->GetBlackboard()->SetValueAsBool(bb_keys::low_charge, false);
		}
	}
}

UBlackboardComponent* AMedic_AI::GetBlackboard() const
{
	return blackboard;
}
