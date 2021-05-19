// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PatrolPathCpp.generated.h"

UCLASS()
class DIPLOMSKIPROJECT_API APatrolPathCpp : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APatrolPathCpp();

	FVector GetPatrolPoint(int const index) const;
	int num() const;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (MakeEditWidget = "true", AllowPrivateAccess = "true"))
		TArray<FVector> patrol_points;
};