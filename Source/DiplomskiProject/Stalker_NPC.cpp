// Fill out your copyright notice in the Description page of Project Settings.


#include "Stalker_NPC.h"

// Sets default values
AStalker_NPC::AStalker_NPC()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	FollowDistance = 250.0f;
}

// Called when the game starts or when spawned
void AStalker_NPC::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AStalker_NPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AStalker_NPC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float AStalker_NPC::GetFollowDistance()
{
	return FollowDistance;
}

