// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PatrolPath.h"
#include "Animation/ANimMontage.h"
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

private:
	// Way to add patrol path through Unreal Editor
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Patrol Route", meta = (AllowPrivateAccess = "true"))
		APatrolPath* patrol_path;

	// Way to set montage animation through Unreal Editor
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation", meta = (AllowPrivateAccess = "true"))
		UAnimMontage* montage;

	// Amount of damage dealt by NPC
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack", meta = (AllowPrivateAccess = "true"))
		float damage = 10.0f;

	// Collision box for right fist
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collision, meta = (AllowPrivateaccess = "true"))
		class UBoxComponent* right_fist_collision_box;

	// Checks if attack animation overlaped Player and deals damage if true
	UFUNCTION()
		void OnAttackOverlapBegin(
			UPrimitiveComponent* const overlapped_component,
			AActor* const other_actor,
			UPrimitiveComponent* other_component,
			int const other_body_index,
			bool const from_sweep,
			FHitResult const& sweep_result);

	UFUNCTION()
		void OnAttackOverlapEnd(
			UPrimitiveComponent* const overlapped_component,
			AActor* const other_actor,
			UPrimitiveComponent* other_component,
			int const other_body_index);

public:
	// Getter for Patrol Path
	APatrolPath* GetPatrolPath();

	// Getter for Montage
	UAnimMontage* GetMontage() const;

	// Getter for Damage
	float GetDamage();

	// Called when Guard is attacking Player
	void MeleeAttack();

	virtual void AttackStart();
	virtual void AttackEnd();
};
