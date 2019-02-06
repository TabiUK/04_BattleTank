// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"
#include "CoreMinimal.h"
#include "Tank.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

}


// Called every frame
void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (PlayerTank) {
    	auto ControlledTank = Cast<ATank>(GetPawn());
	    if (ControlledTank) {

			// move towards the player
			MoveToActor(PlayerTank, AcceptanceRadius); // todo check radius is in cm

			// Aim towards the player
			ControlledTank->AimAt(PlayerTank->GetActorLocation());

			// fire if ready
			ControlledTank->Fire();
		}
	}
}

