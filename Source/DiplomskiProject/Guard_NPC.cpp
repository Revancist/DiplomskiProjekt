// Fill out your copyright notice in the Description page of Project Settings.


#include "Guard_NPC.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Components/SkeletalMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Runtime/Engine/Classes/Components/BoxComponent.h"
#include "DiplomskiProjectCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AGuard_NPC::AGuard_NPC() :
	right_fist_collision_box(CreateDefaultSubobject<UBoxComponent>(TEXT("RightFistCollisionBox")))
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Smoothes NPC rotation
	bUseControllerRotationYaw = false;
	// GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	
	// Setup collision box for right fist
	if (right_fist_collision_box)
	{
		FVector const extent(5.0f);
		right_fist_collision_box->SetBoxExtent(extent, false);
		right_fist_collision_box->SetCollisionProfileName("NoCollision");
	}
}

// Called when the game starts or when spawned
void AGuard_NPC::BeginPlay()
{
	Super::BeginPlay();
	
	if (right_fist_collision_box)
	{
		FAttachmentTransformRules const rules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, false);
		right_fist_collision_box->SetRelativeLocation(FVector(-7.0f, 0.0f, 0.0f));
		right_fist_collision_box->SetupAttachment(GetMesh(), "hand_rSocket");

		right_fist_collision_box->OnComponentBeginOverlap.AddDynamic(this, &AGuard_NPC::OnAttackOverlapBegin);
		right_fist_collision_box->OnComponentEndOverlap.AddDynamic(this, &AGuard_NPC::OnAttackOverlapEnd);
	}
}

// Called every frame
void AGuard_NPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Plays Melee Attack animation
void AGuard_NPC::MeleeAttack()
{
	// Check if montage is set
	if (montage)
	{
		// Play animation
		PlayAnimMontage(montage);
	}
}

void AGuard_NPC::AttackStart()
{
	right_fist_collision_box->SetCollisionProfileName("Fist");
	right_fist_collision_box->SetNotifyRigidBodyCollision(true);
}

void AGuard_NPC::AttackEnd()
{
	right_fist_collision_box->SetCollisionProfileName("NoCollision");
	right_fist_collision_box->SetNotifyRigidBodyCollision(false);
}

// Called to bind functionality to input
void AGuard_NPC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AGuard_NPC::OnAttackOverlapBegin(UPrimitiveComponent* const overlapped_component, AActor* const other_actor, UPrimitiveComponent* other_component, int const other_body_index, bool const from_sweep, FHitResult const& sweep_result)
{
	if (ADiplomskiProjectCharacter* const player = Cast<ADiplomskiProjectCharacter>(other_actor))
	{
		player->UpdatePlayerHealth(-1 * damage);
	}
}

void AGuard_NPC::OnAttackOverlapEnd(UPrimitiveComponent* const overlapped_component, AActor* const other_actor, UPrimitiveComponent* other_component, int const other_body_index)
{
}

// Getter for Patrol Path
APatrolPath* AGuard_NPC::GetPatrolPath()
{
	return patrol_path;
}

// Getter for Montage
UAnimMontage* AGuard_NPC::GetMontage() const
{
	return montage;
}

float AGuard_NPC::GetDamage()
{
	return damage;
}
