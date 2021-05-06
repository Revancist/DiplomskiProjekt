// Fill out your copyright notice in the Description page of Project Settings.


#include "Stalker_AI.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "DiplomskiProjectCharacter.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "GameFramework/Character.h"

AStalker_AI::AStalker_AI(FObjectInitializer const& object_initializer)
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> obj(TEXT("BehaviorTree'/Game/NPC/Neutral/Stalker/NPC_Neutral_Stalker_BT.NPC_Neutral_Stalker_BT'"));

	if (obj.Succeeded())
	{
		btree = obj.Object;
	}

	behavior_tree_component = object_initializer.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("BehaviorComp"));
	blackboard = object_initializer.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("BlackboardComp"));
}

void AStalker_AI::BeginPlay()
{
	Super::BeginPlay();
	// Run behavior tree. (Needs both lines)
	RunBehaviorTree(btree);
	behavior_tree_component->StartTree(*btree);
}

void AStalker_AI::OnPossess(APawn* const pawn)
{
	Super::OnPossess(pawn);
	if (blackboard)
	{
		blackboard->InitializeBlackboard(*btree->BlackboardAsset);
	}
}

UBlackboardComponent* AStalker_AI::get_blackboard() const
{
	return blackboard;
}

void AStalker_AI::on_updated(TArray<AActor*> const& updated_actors)
{
}
