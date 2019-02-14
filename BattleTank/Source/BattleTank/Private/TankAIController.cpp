// Copyright TABIUK Ltd.

#include "TankAIController.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.h" // so we can impliment ondeath

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

  	auto ControlledTank = Cast<ATank>(GetPawn());
	if (!ensure(ControlledTank)) return;

	if (ControlledTank->GetTankObjectType() == ETankObjectType::Tank) {
		// move towards the player
		auto a = MoveToActor(PlayerTank, 8000.0f);  // todo check radius is in cm
		if (a == EPathFollowingRequestResult::Failed) 	UE_LOG(LogTemp, Warning, TEXT("Failed"));
		if (a == EPathFollowingRequestResult::AlreadyAtGoal) 	UE_LOG(LogTemp, Warning, TEXT("AlreadyAtGoal"));
	}


	// Aim towards the player
	AiminComponent->AimAt(PlayerTank->GetActorLocation());

	// fire if ready
	if (AiminComponent->GetFiringStatus() == EfiringStatus::Locked) AiminComponent->Fire();
}

void ATankAIController::SetPawn(APawn * InPawn)
{
	Super::SetPawn(InPawn);

	if (InPawn == nullptr) return;

	auto PossessedTank = Cast<ATank>(InPawn);
	if (!ensure(PossessedTank)) return;

	PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPossedTankDeath);
}


void ATankAIController::OnPossedTankDeath()
{
	auto Pawn = GetPawn();
	if (Pawn) Pawn->DetachFromControllerPendingDestroy();
}

