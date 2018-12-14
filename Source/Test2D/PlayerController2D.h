// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerController2D.generated.h"

class ASpectatorPawn2D;

/**
 * 
 */
UCLASS()
class TEST2D_API APlayerController2D : public APlayerController
{
	GENERATED_BODY()
	
public:
	APlayerController2D();

	ASpectatorPawn2D *GetMainSpectatorPawn() const;

protected:
	virtual void SetupInputComponent() override;
	virtual void ProcessPlayerInput(const float deltaTime, const bool bGamePaused) override;

	//void MovePawnForward(float value);
	void MovePawnUp(float value);
	void MovePawnRight(float value);
	void ZoomIn();
	void ZoomOut();

private:
	
};
