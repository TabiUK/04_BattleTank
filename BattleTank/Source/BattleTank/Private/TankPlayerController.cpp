// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto ControlledTank = GetControlledTank();
	if (ControlledTank == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("No PlayerContoller controlling tank found"));
	} else {
		UE_LOG(LogTemp, Warning, TEXT("PlayerContoller Tank %s being controlled"), *ControlledTank->GetName());
	}

	//UE_LOG(LogTemp, Warning, TEXT("PlayerContoller Begin Play"));
}


// Called every frame
void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}


ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}


// Get world location of linetrace though the crosshair, true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector &OutHitLocation) const
{
	OutHitLocation = FVector(.0f);

	// Find the crosshair position in pixel coordinates
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);

	// "De-project" the screen position of the crosshair to a world direction
	FVector CameraWorldLocation = FVector(.0f); // ingnore camera's world location
	FVector WorldDirection = FVector(.0f);
	if (DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y,
		CameraWorldLocation, WorldDirection)) {
		UE_LOG(LogTemp, Warning, TEXT("Look Direction: %s"), *WorldDirection.ToString());
	}


	return false;

}


void ATankPlayerController::AimTowardsCrosshair()
{
	if (GetControlledTank() == nullptr) return;

	FVector HitLocation = FVector(.0f); // OUT Praramater;
	if (GetSightRayHitLocation(HitLocation)) {
		UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s"), *HitLocation.ToString());
		// TODO aim at point
	}
	return;
}