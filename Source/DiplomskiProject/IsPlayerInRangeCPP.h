// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "IsPlayerInRangeCPP.generated.h"

/**
 * 
 */
UCLASS()
class DIPLOMSKIPROJECT_API UIsPlayerInRangeCPP : public UBTService_BlackboardBase
{
	GENERATED_BODY()
public:
	UIsPlayerInRangeCPP();
	void OnBecomeRelevant(UBehaviorTreeComponent& owner_comp, uint8* node_memory) override;
protected:
	FString GetStaticServiceDescription() const override;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Range", meta = (AllowPrivateAccess = "true"))
		float range = 500.0f;

};
