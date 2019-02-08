// Copyright TABIUK Ltd.

#include "TankAIController.h"
#include "Engine/World.h"
#include "CoreMinimal.h"
#include "Tank.h"
// Depends on movement component via pathfinding system

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

}


// Called every frame
void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (!ensure(PlayerTank)) return;

  	auto ControlledTank = Cast<ATank>(GetPawn());
	if (!ensure(ControlledTank)) return;

   // move towards the player
	MoveToActor(PlayerTank, AcceptanceRadius); // todo check radius is in cm

	// Aim towards the player
	ControlledTank->AimAt(PlayerTank->GetActorLocation());

	// fire if ready
	ControlledTank->Fire();
}

