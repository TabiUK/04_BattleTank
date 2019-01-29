// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	auto ControlledTank = GetControlledTank();
	if (ControlledTank == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("No controlling tank found"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Tank %s being controlled"), *ControlledTank->GetName());
	}

	UE_LOG(LogTemp, Warning, TEXT("TankAIController Begin Play"));
}



ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

