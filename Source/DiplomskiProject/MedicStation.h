// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MedicStation.generated.h"

UCLASS()
class DIPLOMSKIPROJECT_API AMedicStation : public AActor
{
	GENERATED_BODY()
public:	
	// Sets default values for this actor's properties
	AMedicStation();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	// Collision Sphere
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collision, meta = (AllowPrivateAccess = "true"))
		class USphereComponent* CollisionSphere;

	// Particle System
	UPROPERTY(VisibleAnywhere)
		class UParticleSystemComponent* Sparks;

private:
	// Static mesh to represent the station
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Station", meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* StationMesh;
};
