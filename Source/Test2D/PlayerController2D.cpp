// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerController2D.h"

#include "Engine/LocalPlayer.h"

#include "CameraComponent2D.h"
#include "PlayerCameraManager2D.h"
#include "SpectatorPawn2D.h"

APlayerController2D::APlayerController2D()
{
	PrimaryActorTick.bCanEverTick = true;
	bHidden = false;
	bShowMouseCursor = true;

	PlayerCameraManagerClass = APlayerCameraManager2D::StaticClass();
}

ASpectatorPawn2D* APlayerController2D::GetMainSpectatorPawn() const
{
	return Cast<ASpectatorPawn2D>(GetPawn());
}

void APlayerController2D::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("ZoomIn", IE_Pressed, this, &APlayerController2D::ZoomIn);
	InputComponent->BindAction("ZoomOut", IE_Pressed, this, &APlayerController2D::ZoomOut);

	//InputComponent->BindAxis("MoveForward", this, &APlayerController2D::MovePawnForward);
	InputComponent->BindAxis("MoveUp", this, &APlayerController2D::MovePawnUp);
	InputComponent->BindAxis("MoveRight", this, &APlayerController2D::MovePawnRight);

}

void APlayerController2D::ProcessPlayerInput(const float deltaTime, const bool bGamePaused)
{
	Super::ProcessPlayerInput(deltaTime, bGamePaused);

	{
		const ULocalPlayer* localPlayer = Cast<ULocalPlayer>(Player);
		const ASpectatorPawn2D* spectatorPawn = GetMainSpectatorPawn();

		if (spectatorPawn && localPlayer)
		{
			if (localPlayer->ViewportClient)
			{
				spectatorPawn->GetCameraComponent()->UpdateCameraMovement(this);
			}
		}
	}
}

void APlayerController2D::MovePawnUp(float value)
{
	ASpectatorPawn2D *spectatorPawn;
	if (value != 0.f && (spectatorPawn = Cast<ASpectatorPawn2D>(GetPawn())) != nullptr)
	{
		spectatorPawn->MoveUp(value);
	}
}

void APlayerController2D::MovePawnRight(float value)
{
	ASpectatorPawn2D *spectatorPawn;
	if (value != 0.f && (spectatorPawn = Cast<ASpectatorPawn2D>(GetPawn())) != nullptr)
	{
		spectatorPawn->MoveRight(value);
	}
}

void APlayerController2D::ZoomIn()
{
	ASpectatorPawn2D *spectatorPawn;
	if ((spectatorPawn = Cast<ASpectatorPawn2D>(GetPawn())) != nullptr)
	{
		spectatorPawn->OnMouseScrollUp();
	}
}

void APlayerController2D::ZoomOut()
{
	ASpectatorPawn2D *spectatorPawn;
	if ((spectatorPawn = Cast<ASpectatorPawn2D>(GetPawn())) != nullptr)
	{
		spectatorPawn->OnMouseScrollDown();
	}
}
