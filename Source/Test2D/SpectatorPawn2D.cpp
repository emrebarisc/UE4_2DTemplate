// Fill out your copyright notice in the Description page of Project Settings.

#include "SpectatorPawn2D.h"

#include "CameraComponent2D.h"
#include "Components/SphereComponent.h"
#include "Engine/CollisionProfile.h"

ASpectatorPawn2D::ASpectatorPawn2D(const FObjectInitializer & objectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;

	GetCollisionComponent()->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);
	bAddDefaultMovementBindings = false;

	cameraComponent_ = CreateDefaultSubobject<UCameraComponent2D>(TEXT("Camera Component"));
}

void ASpectatorPawn2D::BeginPlay()
{
	Super::BeginPlay();

	SetActorLocation(FVector::ZeroVector);
}

void ASpectatorPawn2D::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
}

//void ASpectatorPawn2D::MoveForward(float value)
//{
//	if (value != 0.f)
//	{
//		cameraComponent_->MoveForward(value);
//	}
//}

void ASpectatorPawn2D::MoveUp(float value)
{
	if (value != 0.f)
	{
		cameraComponent_->MoveUp(value);
	}
}

void ASpectatorPawn2D::MoveRight(float value)
{
	if (value != 0.f)
	{
		cameraComponent_->MoveRight(value);
	}
}

void ASpectatorPawn2D::OnMouseScrollUp()
{
	cameraComponent_->OnZoomIn();
}

void ASpectatorPawn2D::OnMouseScrollDown()
{
	cameraComponent_->OnZoomOut();
}
