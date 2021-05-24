// Fill out your copyright notice in the Description page of Project Settings.


#include "Guard_NPC.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AGuard_NPC::AGuard_NPC()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Smoothes NPC rotation
	bUseControllerRotationYaw = false;
	// GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->bOrientRotationToMovement = true;
}

// Called when the game starts or when spawned
void AGuard_NPC::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGuard_NPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AGuard_NPC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

APatrolPath* AGuard_NPC::GetPatrolPath()
{
	return patrol_path;
}

