// Fill out your copyright notice in the Description page of Project Settings.


#include "Medic_NPC.h"
#include "DiplomskiProjectCharacter.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

// Sets default values
AMedic_NPC::AMedic_NPC()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set default Max and Current Stored Health Points
	MaxStoredHealth = 100.f;
	StoredHealth = 0.f;

	// Set default Healing Amount
	HealAmount = 10.f;

	// Set default recharge point
	RechargePoint = 30.f;
}

// Called when the game starts or when spawned
void AMedic_NPC::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMedic_NPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AMedic_NPC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

// Accessor for Max Stored Health
float AMedic_NPC::GetMaxStoredHealth()
{
	return MaxStoredHealth;
}

// Accessor for Current Stored Health
float AMedic_NPC::GetStoredHealth()
{
	return StoredHealth;
}

// Accessor for Recharge Point
float AMedic_NPC::GetRechargePoint()
{
	return RechargePoint;
}

// Accessor for Heal Amount
float AMedic_NPC::GetHealAmount()
{
	return HealAmount;
}

// Called when Stored Health is updated
void AMedic_NPC::UpdateStoredHealth(float Amount)
{
	// Update Stored Health
	StoredHealth += Amount;

	// Check if stored health is above Max
	if (StoredHealth > MaxStoredHealth)
	{
		// Keep Stored Health at Max
		StoredHealth = MaxStoredHealth;
	}
	// Check if stored health is below 0
	else if (StoredHealth < 0)
	{
		// Keep Stored Health at 0
		StoredHealth = 0;
	}
}

