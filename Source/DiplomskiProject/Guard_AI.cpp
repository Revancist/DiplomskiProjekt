// Fill out your copyright notice in the Description page of Project Settings.


#include "Guard_AI.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "DiplomskiProjectCharacter.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "GameFramework/Character.h"

// Initialize behavior tree and blackboard.
AGuard_AI::AGuard_AI(FObjectInitializer const& object_initializer)
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> obj(TEXT("BehaviorTree'/Game/NPC/Hostile/Guard/NPC_Hostile_Guard_BT.NPC_Hostile_Guard_BT'"));

	if (obj.Succeeded())
	{
		btree = obj.Object;
	}

	behavior_tree_component = object_initializer.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("BehaviorComp"));
	blackboard = object_initializer.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("BlackboardComp"));
	//setup_perception_system();
}

void AGuard_AI::BeginPlay()
{
	Super::BeginPlay();
	// Run behavior tree. (Apperently needs both)
	RunBehaviorTree(btree);
	behavior_tree_component->StartTree(*btree);
}

void AGuard_AI::OnPossess(APawn* const pawn)
{
	Super::OnPossess(pawn);
	if (blackboard)
	{
		blackboard->InitializeBlackboard(*btree->BlackboardAsset);
	}
}

UBlackboardComponent* AGuard_AI::GetBlackboard() const
{
	return blackboard;
}