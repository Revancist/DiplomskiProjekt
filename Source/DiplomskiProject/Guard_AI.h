// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Guard_AI.generated.h"

/**
 * 
 */
UCLASS()
class DIPLOMSKIPROJECT_API AGuard_AI : public AAIController
{
	GENERATED_BODY()
public:
	AGuard_AI(FObjectInitializer const& object_initializer = FObjectInitializer::Get());
	void BeginPlay() override;
	void OnPossess(APawn* const pawn) override;
	class UBlackboardComponent* GetBlackboard() const;

private:
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
		class UBehaviorTreeComponent* behavior_tree_component;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
		class UBehaviorTree* btree;

	class UBlackboardComponent* blackboard;
};
