// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Medic_NPC.generated.h"

UCLASS()
class DIPLOMSKIPROJECT_API AMedic_NPC : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMedic_NPC();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// Set Max Stored Health Points and Starting Stored Health Points;
	UPROPERTY(EditAnywhere, Category = "Storage", META = (BlueprintProtected = "true"))
		float MaxStoredHealth;
	UPROPERTY(EditAnywhere, Category = "Storage", META = (BlueprintProtected = "true"))
		float StoredHealth;

	// Set Healing Amount
	UPROPERTY(EditAnywhere, Category = "Healing", META = (BlueprintProtected = "true"))
		float HealAmount;

	// Set recharge treshold
	UPROPERTY(EditAnywhere, Category = "Storage", META = (BlueprintProtected = "true"))
		float RechargePoint;

public:
	// Public way to access Medic's Stored Health
	float GetMaxStoredHealth();
	float GetStoredHealth();

	// Public way to access Medic's Heal Amount
	float GetHealAmount();

	// Public way to access Recharge Point
	float GetRechargePoint();

	// Update Medic's Stored Health
	void UpdateStoredHealth(float Amount);
};
