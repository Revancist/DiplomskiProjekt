// Copyright Epic Games, Inc. All Rights Reserved.

#include "DiplomskiProjectGameMode.h"
#include "DiplomskiProjectHUD.h"
#include "DiplomskiProjectCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "TimerManager.h"
#include "GameFramework/HUD.h"

ADiplomskiProjectGameMode::ADiplomskiProjectGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ADiplomskiProjectHUD::StaticClass();

	// Enable tick
	PrimaryActorTick.bCanEverTick = true;
}

void ADiplomskiProjectGameMode::BeginPlay()
{
	Super::BeginPlay();

	// Setup HUD
	if (HUDWidgetClass != nullptr)
	{
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), HUDWidgetClass);
		if (CurrentWidget != nullptr)
		{
			CurrentWidget->AddToViewport();
		}
	}
}

void ADiplomskiProjectGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// Check that we are using the DiplomskiProject character
	ADiplomskiProjectCharacter* MyCharacter = Cast<ADiplomskiProjectCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
	if (MyCharacter)
	{
		// If Player's Health Points are <= 0, end the game
		if (MyCharacter->GetPlayerHealth() <= 0)
		{
			GameOver();
		}
	}
}
// Called when Player's Health is <= 0
void ADiplomskiProjectGameMode::GameOver()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	if (PlayerController)
	{
		// Block Player input
		PlayerController->SetCinematicMode(true, true, true);
		// Reset level
		UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
	}
}
