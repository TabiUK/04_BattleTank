// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Components/PrimitiveComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Engine/World.h"


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


void ATankPlayerController::AimTowardsCrosshair()
{
	auto ControlledTank = GetControlledTank();
	if (ControlledTank == nullptr) return;

	FVector HitLocation = FVector(.0f); // OUT Praramater;
	if (GetSightRayHitLocation(HitLocation)) {

		ControlledTank->AimAt(HitLocation);
	}
	return;
}


// Get world location of linetrace though the crosshair, true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector &OutHitLocation) const
{
	OutHitLocation = FVector(.0f);

	// Find the crosshair position in pixel coordinates
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);

	FVector LookDirection = FVector(.0f);
	if (GetLookDirection(ScreenLocation, LookDirection)) {
		// Line-trace along that LookDirection, and see what we hit (up to max range)
		return (GetLookVectorHitLocation(LookDirection, OutHitLocation));
	}


	return false;

}


// "De-project" the screen position of the crosshair to a world direction
bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector CameraWorldLocation = FVector(.0f); // ingnore camera's world location
	LookDirection = FVector(.0f);
	return (DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y,
		CameraWorldLocation, LookDirection));
}


bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
	/// Line-trace (AKA ray-cast) out to reach distance
	FHitResult HitResult = FHitResult();
	HitLocation = FVector(.0f);
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);

	if (GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Visibility)) {
		HitLocation = HitResult.Location;
		return true;
	}
	return false;
}


ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}