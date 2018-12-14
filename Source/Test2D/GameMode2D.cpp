// Fill out your copyright notice in the Description page of Project Settings.

#include "GameMode2D.h"
#include "PlayerController2D.h"
#include "SpectatorPawn2D.h"
#include "PlayerState2D.h"
#include "GameState2D.h"
#include "HUD2D.h"

AGameMode2D::AGameMode2D()
{
	GameStateClass = AGameState2D::StaticClass();
	PlayerControllerClass = APlayerController2D::StaticClass();
	SpectatorClass = ASpectatorPawn2D::StaticClass();
	DefaultPawnClass = ASpectatorPawn2D::StaticClass();
	PlayerStateClass = APlayerState2D::StaticClass();
	HUDClass = AHUD2D::StaticClass();
}