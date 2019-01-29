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



ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}