// Fill out your copyright notice in the Description page of Project Settings.

#include "HUD2D.h"

#include "Components/CapsuleComponent.h"
#include "Engine/Canvas.h"
#include "Engine/Engine.h"
#include "Engine/GameViewportClient.h"

#include "PlayerController2D.h"

AHUD2D::AHUD2D()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AHUD2D::BeginPlay()
{
	Super::BeginPlay();
}

void AHUD2D::Tick(float deltaSeconds)
{
	Super::Tick(deltaSeconds);
}

void AHUD2D::DrawHUD()
{
	Super::DrawHUD();

	if (GEngine && GEngine->GameViewport)
	{
		FVector2D viewportSize;
		GEngine->GameViewport->GetViewportSize(viewportSize);
		uiScale_ = viewportSize.X / 2048.f;
	}
}

APlayerController2D * AHUD2D::GetPlayerController() const
{
	return Cast<APlayerController2D>(PlayerOwner);
}

ASpectatorPawn2D *AHUD2D::GetSpectatorPawn() const
{
	APlayerController2D *pc = GetPlayerController();
	if (pc)
	{
		return pc->GetMainSpectatorPawn();
	}

	return nullptr;
}