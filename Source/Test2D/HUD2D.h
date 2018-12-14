// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "HUD2D.generated.h"

class APlayerController2D;
class ASpectatorPawn2D;

/**
 * 
 */
UCLASS()
class TEST2D_API AHUD2D : public AHUD
{
	GENERATED_BODY()
		AHUD2D();

	void BeginPlay() override;
	void Tick(float deltaSeconds) override;

private:
	// Main drawing function
	virtual void DrawHUD() override;
	APlayerController2D* GetPlayerController() const;
	ASpectatorPawn2D* GetSpectatorPawn() const;

	void DrawHealthBars() const;
	void DrawSelectionGrid(FVector2D gridStartPos);

	float uiScale_;
	
	
	
};
