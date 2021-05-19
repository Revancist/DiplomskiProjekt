// Fill out your copyright notice in the Description page of Project Settings.


#include "PatrolPathCpp.h"

// Sets default values
APatrolPathCpp::APatrolPathCpp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

FVector APatrolPathCpp::GetPatrolPoint(int const index) const
{
	return patrol_points[index];
}

int APatrolPathCpp::num() const
{
	return patrol_points.Num();
}
