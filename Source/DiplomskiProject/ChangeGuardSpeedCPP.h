// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "ChangeGuardSpeedCPP.generated.h"

/**
 * 
 */
UCLASS()
class DIPLOMSKIPROJECT_API UChangeGuardSpeedCPP : public UBTService_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UChangeGuardSpeedCPP();
	void OnBecomeRelevant(UBehaviorTreeComponent& owner_comp, uint8* node_memory) override;
protected:
	FString GetStaticServiceDescription() const override;
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
		float speed = 400.0f;
};
