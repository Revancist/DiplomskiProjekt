// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PatrolPathCpp.h"
#include "Guard_NPC.generated.h"

UCLASS()
class DIPLOMSKIPROJECT_API AGuard_NPC : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AGuard_NPC();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	APatrolPathCpp* GetPatrolPath();

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "True"))
		APatrolPathCpp* patrol_path;
};
