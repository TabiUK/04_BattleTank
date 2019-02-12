// Copyright TABIUK Ltd.

#include "TankAIController.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"
#include "CoreMinimal.h"

// Depends on movement component via pathfinding system

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	auto ControlledTank = GetPawn();
	if (!ensure(ControlledTank)) return;

	AiminComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AiminComponent)) return;


}


// Called every frame
void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!ensure(AiminComponent)) return;

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!ensure(PlayerTank)) return;

  	auto ControlledTank = GetPawn();
	if (!ensure(ControlledTank)) return;

   // move towards the player
	MoveToActor(PlayerTank, AcceptanceRadius); // todo check radius is in cm

	// Aim towards the player
	AiminComponent->AimAt(PlayerTank->GetActorLocation());

	// fire if ready
	if (AiminComponent->GetFiringStatus() == EfiringStatus::Locked) AiminComponent->Fire();
}

