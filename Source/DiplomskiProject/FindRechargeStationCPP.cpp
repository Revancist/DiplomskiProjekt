// Fill out your copyright notice in the Description page of Project Settings.


#include "FindRechargeStationCPP.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Runtime/NavigationSystem/Public/NavigationSystem.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Medic_AI.h"
#include "MedicStation.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "GameFramework/Character.h"
#include "Medic_blackboard_keys.h"
#include "EngineUtils.h"
#include "Math/Vector.h"

// Set name of node in Behavior Tree
UFindRechargeStationCPP::UFindRechargeStationCPP(FObjectInitializer const& object_initializer)
{
	NodeName = TEXT("Find Recharge Station");
}

// Find the location of nearest Recharge Station
EBTNodeResult::Type UFindRechargeStationCPP::ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
	// Get NPC controller
	auto const npc_controller = Cast<AMedic_AI>(owner_comp.GetAIOwner());
	// Check if cast was successful
	if (npc_controller)
	{
		// Get NPC
		auto const npc = npc_controller->GetPawn();

		// Get all Recharge Stations and put them in an array
		TArray<AActor*> AllStations;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMedicStation::StaticClass(), AllStations);
		
		// Initialize Station and NearestStation
		AMedicStation* NearestStation = Cast<AMedicStation>(AllStations[0]);
		AMedicStation* Station = Cast<AMedicStation>(AllStations[0]);

		// If the casts were successful
		if (Station && NearestStation)
		{
			// If Array has more than one element
			if (AllStations.Num() > 1)
			{
				// Distance between Medic and first Station
				float distance = FVector::Dist(npc->GetActorLocation(), Station->GetActorLocation());

				// For each station in array
				for (int32 iStation = 1; iStation < AllStations.Num(); ++iStation)
				{
					// Cast Actor to MedicStation
					Station = Cast<AMedicStation>(AllStations[iStation]);

					// If cast was successful and new distance is less than stored distance
					if (Station && (distance > FVector::Dist(npc->GetActorLocation(), Station->GetActorLocation())))
					{
						// Store new closest distance
						distance = FVector::Dist(npc->GetActorLocation(), Station->GetActorLocation());
						// Store new nearest Station
						NearestStation = Station;
					}
				}
			}
			// Set blackboard value for target location
			npc_controller->GetBlackboard()->SetValueAsVector(bb_keys::target_location, NearestStation->GetActorLocation());

			// Finish task with success
			FinishLatentTask(owner_comp, EBTNodeResult::Succeeded);
			return EBTNodeResult::Succeeded;
		}
	}
	// Finish task with fail
	FinishLatentTask(owner_comp, EBTNodeResult::Failed);
	return EBTNodeResult::Failed;
}
