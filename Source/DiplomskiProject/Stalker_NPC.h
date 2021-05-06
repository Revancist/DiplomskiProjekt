// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Stalker_NPC.generated.h"

UCLASS()
class DIPLOMSKIPROJECT_API AStalker_NPC : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AStalker_NPC();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Accessor for FollowDistance
	float GetFollowDistance();

protected:
	// Distance from Player
	UPROPERTY(EditAnywhere, Category = "Distance", META = (BlueprintProtected = "true"))
		float FollowDistance;
};
