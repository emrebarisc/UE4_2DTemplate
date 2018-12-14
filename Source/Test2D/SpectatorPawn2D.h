// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SpectatorPawn.h"
#include "SpectatorPawn2D.generated.h"

class UCameraComponent2D;

/**
 * 
 */
UCLASS()
class TEST2D_API ASpectatorPawn2D : public ASpectatorPawn
{
	GENERATED_BODY()

	friend class APlayerController2D;

public:
	ASpectatorPawn2D(const FObjectInitializer& ObjectInitializer);
	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;

	UCameraComponent2D* GetCameraComponent() const
	{
		return cameraComponent_;
	}

private:
	void MoveUp(float value);
	//void MoveForward(float value);
	void MoveRight(float value);
	void OnMouseScrollUp();
	void OnMouseScrollDown();

	UCameraComponent2D* cameraComponent_;
};
