// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "DiplomskiProjectHUD.generated.h"

UCLASS()
class ADiplomskiProjectHUD : public AHUD
{
	GENERATED_BODY()

public:
	ADiplomskiProjectHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

	// Draw Game Over when the game is lost
	void DrawGameOver();

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

};

