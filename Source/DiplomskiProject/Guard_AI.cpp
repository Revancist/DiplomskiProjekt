// Fill out your copyright notice in the Description page of Project Settings.


#include "Guard_AI.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "DiplomskiProjectCharacter.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "guard_blackboard.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "GameFramework/Character.h"

AGuard_AI::AGuard_AI(FObjectInitializer const& object_initializer)
{
	// Initialize Behavior Tree
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> obj(TEXT("BehaviorTree'/Game/NPC/Hostile/Guard/NPC_Hostile_Guard_BT.NPC_Hostile_Guard_BT'"));
	// Check if initialization is a success
	if (obj.Succeeded())
	{
		btree = obj.Object;
	}

	// Get behavior tree component and blackboard
	behavior_tree_component = object_initializer.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("BehaviorTreeComponent"));
	blackboard = object_initializer.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("BlackboardComponent"));

	SetupPerceptionSystem();
}

void AGuard_AI::BeginPlay()
{
	Super::BeginPlay();

	// Runs behavior tree (needs both lines)
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

// Called when Guard Perception System is updated
void AGuard_AI::OnUpdated(TArray<AActor*> const& updated_actors)
{
	for (size_t x = 0; x < updated_actors.Num(); ++x)
	{
		// Get all updated perception components
		FActorPerceptionBlueprintInfo info;
		GetPerceptionComponent()->GetActorsPerception(updated_actors[x], info);
		for (size_t k = 0; k < info.LastSensedStimuli.Num(); ++k)
		{
			// Check component type
			FAIStimulus const stim = info.LastSensedStimuli[k];
			if (stim.Tag == "Noise")
			{
				// Set blackboard Investigate value and target location
				GetBlackboard()->SetValueAsBool(bb_keys::is_investigating, stim.WasSuccessfullySensed());
				GetBlackboard()->SetValueAsVector(bb_keys::target_location, stim.StimulusLocation);
			}
			else if (stim.Type.Name == "Default__AISense_Sight")
			{
				// Set blackboard Can see Player value and Has been Chasing value
				GetBlackboard()->SetValueAsBool(bb_keys::can_see_player, stim.WasSuccessfullySensed());
				GetBlackboard()->SetValueAsBool(bb_keys::has_been_chasing, true);
			}
		}
	}
}

void AGuard_AI::SetupPerceptionSystem()
{
	// Create and initialise sight configuration object
	sight_config = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	if (sight_config)
	{
		SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Component")));
		sight_config->SightRadius = 1500.0f;
		sight_config->LoseSightRadius = sight_config->SightRadius + 50.0f;
		sight_config->PeripheralVisionAngleDegrees = 90.0f;
		sight_config->SetMaxAge(5.0f);
		sight_config->AutoSuccessRangeFromLastSeenLocation = 100.0f;
		sight_config->DetectionByAffiliation.bDetectEnemies = true;
		sight_config->DetectionByAffiliation.bDetectFriendlies = true;
		sight_config->DetectionByAffiliation.bDetectNeutrals = true;

		// Add sight configuration component to perception component
		GetPerceptionComponent()->SetDominantSense(*sight_config->GetSenseImplementation());
		GetPerceptionComponent()->OnPerceptionUpdated.AddDynamic(this, &AGuard_AI::OnUpdated);
		GetPerceptionComponent()->ConfigureSense(*sight_config);
	}

	// Create and initialise hearinf config object
	hearing_config = CreateDefaultSubobject<UAISenseConfig_Hearing>(TEXT("Hearing config"));
	if (hearing_config)
	{
		hearing_config->HearingRange = 3000.0f;
		hearing_config->DetectionByAffiliation.bDetectEnemies = true;
		hearing_config->DetectionByAffiliation.bDetectFriendlies = true;
		hearing_config->DetectionByAffiliation.bDetectNeutrals = true;

		GetPerceptionComponent()->OnPerceptionUpdated.AddDynamic(this, &AGuard_AI::OnUpdated);
		GetPerceptionComponent()->ConfigureSense(*hearing_config);
	}
}
