// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"



void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	auto ControlledTank = GetControlledTank();
	FString TankName = "Tank";

	if (ControlledTank == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("No controlling tank found"));
	} else {
		TankName = ControlledTank->GetName();
	}

	//UE_LOG(LogTemp, Warning, TEXT("TankAIController Begin Play"));

	auto PlayerTank = GetPlayerTank();
	if (PlayerTank == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("No Player Controller tank found"));

	} else {
		UE_LOG(LogTemp, Warning, TEXT("TankAIController %s found Player Controller Pawn %s"), *TankName, *PlayerTank->GetName());
	}

}


// Called every frame
void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	auto CurrentTank = GetControlledTank();
	if (CurrentTank) {
		auto PlayerTank = GetPlayerTank();
		if (PlayerTank) {
			CurrentTank->AimAt(PlayerTank->GetActorLocation());
		}
	}
}


ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}


ATank * ATankAIController::GetPlayerTank() const
{
	return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}

