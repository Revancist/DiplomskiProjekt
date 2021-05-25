// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "IncrementPathIndexCPP.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class DIPLOMSKIPROJECT_API UIncrementPathIndexCPP : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UIncrementPathIndexCPP(FObjectInitializer const& object_initializer);

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory) override;

private:
	enum class EDirectionType
	{
		Forward, Reverse
	};

	EDirectionType direction = EDirectionType::Forward;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Direction", meta = (AllowPrivateAccess = "true"))
		bool loop = true;
};
