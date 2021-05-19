// Fill out your copyright notice in the Description page of Project Settings.


#include "MedicStation.h"
#include "Components/SphereComponent.h"
#include "Medic_NPC.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AMedicStation::AMedicStation()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create static mesh component
	StationMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StationMesh"));
	RootComponent = StationMesh;

	// Create collision sphere
	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	CollisionSphere->SetupAttachment(RootComponent);
	CollisionSphere->SetSphereRadius(100.f);

	// Create particle system
	static ConstructorHelpers::FObjectFinder<UParticleSystem> Effect(TEXT("ParticleSystem'/Game/StarterContent/Particles/P_Sparks.P_Sparks'"));
	Sparks = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystem"));
	Sparks->SetTemplate(Effect.Object);
	Sparks->SetupAttachment(RootComponent);
	Sparks->SetVisibility(false);
}

// Called when the game starts or when spawned
void AMedicStation::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMedicStation::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Get all overlapping Actors and store them in an array
	TArray<AActor*> CollectedActors;
	CollisionSphere->GetOverlappingActors(CollectedActors);

	//For each collected actor
	for (int32 iCollected = 0; iCollected < CollectedActors.Num(); ++iCollected)
	{
		// Cast collected actor to AMedic_NPC
		AMedic_NPC* const CollectedMedic = Cast<AMedic_NPC>(CollectedActors[iCollected]);
		// Check if the cast was successful and Medic is not at Max stored health
		if (CollectedMedic && (CollectedMedic->GetStoredHealth() < CollectedMedic->GetMaxStoredHealth()))
		{
			// Show sparks
			Sparks->SetVisibility(true);
		}
		else 
		{
			// Don't show sparks
			Sparks->SetVisibility(false);
		}
	}
}
