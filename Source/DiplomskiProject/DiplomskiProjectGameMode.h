// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DiplomskiProjectGameMode.generated.h"

UCLASS(minimalapi)
class ADiplomskiProjectGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ADiplomskiProjectGameMode();

protected:
	// Widget class to use for the HUD screen
	UPROPERTY(EditDefaultsOnly, Category = "Health", Meta = (BlueprintProtected = "true"))
		TSubclassOf<class UUserWidget> HUDWidgetClass;

	// The instance of the HUD
	UPROPERTY()
		class UUserWidget* CurrentWidget;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void BeginPlay() override;

	// Called when the Game is over
	UFUNCTION(BlueprintCallable, Category = "Game")
	void GameOver();
};