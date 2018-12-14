// Fill out your copyright notice in the Description page of Project Settings.

#include "CameraComponent2D.h"

#include "Engine/LocalPlayer.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/SpectatorPawn.h"

#include "PlayerController2D.h"

UCameraComponent2D::UCameraComponent2D()
{
	SetProjectionMode(ECameraProjectionMode::Orthographic);

	bShouldClampCamera_ = true;

	zoomAlpha_ = 1.f;
	cameraScrollSpeed_ = 3000.f;
	cameraActiveBorder_ = 100.f;
	minZoomLevel_ = 0.4f;
	maxZoomLevel_ = 1.f;
	minCameraOffset_ = 0.f;
	maxCameraOffset_ = 20000.f;
	movementSpeed_ = 100.f;

	fixedCameraAngle_ = FRotator(0.f, 0.f, 0.f);
}

void UCameraComponent2D::GetCameraView(float deltaTime, FMinimalViewInfo& desiredView)
{
	APlayerController* playerController = GetPlayerController();

	if (playerController)
	{
		desiredView.FOV = 30.f;
		const float currentOffset = minCameraOffset_ + zoomAlpha_ * (maxCameraOffset_ - minCameraOffset_);
		const FVector focalPos = playerController->GetFocalLocation();
		desiredView.Location = focalPos - fixedCameraAngle_.Vector() * currentOffset;
		desiredView.Rotation = fixedCameraAngle_;
	}
}

void UCameraComponent2D::OnZoomIn()
{
	SetZoomLevel(zoomAlpha_ - 0.1f);
}

void UCameraComponent2D::OnZoomOut()
{
	SetZoomLevel(zoomAlpha_ + 0.1f);
}

void UCameraComponent2D::UpdateCameraMovement(const APlayerController* playerController) const
{
	ULocalPlayer* const localPlayer = Cast<ULocalPlayer>(playerController->Player);

	if (localPlayer && localPlayer->ViewportClient && localPlayer->ViewportClient->Viewport)
	{
		FVector2D mousePosition;
		if (!localPlayer->ViewportClient->GetMousePosition(mousePosition))
		{
			return;
		}

		FViewport* viewport = localPlayer->ViewportClient->Viewport;
		const float scrollSpeed = 60.f;
		const FIntPoint viewportSize = viewport->GetSizeXY();

		const uint32 viewLeft = FMath::TruncToInt(localPlayer->Origin.X * viewportSize.X);
		const uint32 viewRight = viewLeft + FMath::TruncToInt(localPlayer->Size.X * viewportSize.X);
		const uint32 viewTop = FMath::TruncToInt(localPlayer->Origin.Y * viewportSize.Y);
		const uint32 viewBottom = viewTop + FMath::TruncToInt(localPlayer->Size.Y * viewportSize.Y);

		const float maxSpeed = cameraScrollSpeed_ * FMath::Clamp(zoomAlpha_, minZoomLevel_, maxZoomLevel_);

		const uint32 mouseX = mousePosition.X;
		const uint32 mouseY = mousePosition.Y;
		float spectatorCameraSpeed = maxSpeed;

		if (true) //!bNoScrollZone_
		{
			if (mouseX >= viewLeft && mouseX <= (viewLeft + cameraActiveBorder_))
			{
				const float delta = 1.0f - float(mouseX - viewLeft) / cameraActiveBorder_;
				spectatorCameraSpeed = delta * maxSpeed;
				MoveRight(-scrollSpeed * delta);
			}
			else if (mouseX >= (viewRight - cameraActiveBorder_) && mouseX <= viewRight)
			{
				const float delta = float(mouseX - viewRight + cameraActiveBorder_) / cameraActiveBorder_;
				spectatorCameraSpeed = delta * maxSpeed;
				MoveRight(scrollSpeed * delta);
			}

			if (mouseY >= viewTop && mouseY <= (viewTop + cameraActiveBorder_))
			{
				const float delta = 1.0f - float(mouseY - viewTop) / cameraActiveBorder_;
				spectatorCameraSpeed = delta * maxSpeed;
				MoveUp(scrollSpeed * delta);
			}
			else if (mouseY >= (viewBottom - cameraActiveBorder_) && mouseY <= viewBottom)
			{
				const float delta = float(mouseY - (viewBottom - cameraActiveBorder_)) / cameraActiveBorder_;
				spectatorCameraSpeed = delta * maxSpeed;
				MoveUp(-scrollSpeed * delta);
			}
		}
	}
}

//void UCameraComponent2D::MoveForward(const float value) const
//{
//	APawn* ownerPawn = GetOwnerPawn();
//
//	if (ownerPawn)
//	{
//		APlayerController* controller = GetPlayerController();
//		if (value != 0.f && controller)
//		{
//			// If our camera is not rotated or we want to use camera's local coordinates, we can use rotationMatrix
//			//const FRotationMatrix rotationMatrix(controller->PlayerCameraManager->GetCameraRotation());
//			const FVector worldSpaceAcc = /*rotationMatrix.GetScaledAxis(EAxis::Y)*/ FVector(1.f, 0.f, 0.f) * movementSpeed_;
//
//			ownerPawn->AddMovementInput(worldSpaceAcc, value);
//		}
//	}
//}

void UCameraComponent2D::MoveUp(const float value) const
{
	APawn* ownerPawn = GetOwnerPawn();

	if (ownerPawn)
	{
		APlayerController* controller = GetPlayerController();
		if (value != 0.f && controller)
		{
			// If our camera is not rotated or we want to use camera's local coordinates, we can use rotationMatrix
			//const FRotationMatrix rotationMatrix(controller->PlayerCameraManager->GetCameraRotation());
			const FVector worldSpaceAcc = /*rotationMatrix.GetScaledAxis(EAxis::X)*/ FVector(0.f, 0.f, 1.f) * movementSpeed_;

			ownerPawn->AddMovementInput(worldSpaceAcc, value);
		}
	}
}

void UCameraComponent2D::MoveRight(const float value) const
{
	APawn* ownerPawn = GetOwnerPawn();

	if (ownerPawn)
	{
		APlayerController* controller = GetPlayerController();
		if (value != 0.f && controller)
		{
			// If our camera is not rotated or we want to use camera's local coordinates, we can use rotationMatrix
			//const FRotationMatrix rotationMatrix(controller->PlayerCameraManager->GetCameraRotation());
			const FVector worldSpaceAcc = /*rotationMatrix.GetScaledAxis(EAxis::Y)*/ FVector(0.f, 1.f, 0.f) * movementSpeed_;

			ownerPawn->AddMovementInput(worldSpaceAcc, value);
		}
	}
}

void UCameraComponent2D::SetZoomLevel(float level)
{
	zoomAlpha_ = FMath::Clamp(level, minZoomLevel_, maxZoomLevel_);
}

APawn* UCameraComponent2D::GetOwnerPawn() const
{
	return Cast<APawn>(GetOwner());
}

APlayerController2D* UCameraComponent2D::GetPlayerController() const
{
	APlayerController2D* controller = nullptr;
	APawn* owner = GetOwnerPawn();
	if (owner)
	{
		controller = Cast<APlayerController2D>(owner->GetController());
	}

	return controller;
}