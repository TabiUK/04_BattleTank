// Copyright TABIUK Ltd.

#include "TankAimingComponent.h"
#include "GameFramework/Pawn.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/GameplayStaticsTypes.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Engine/World.h"
#include "CoreMinimal.h"


// Sets default values for this component's properties

UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}



void UTankAimingComponent::AimAt(FVector HitLocation, float LauchSpeed)
{
	if (!ensure(Barrel) || !ensure(Turret)) return;

	FVector OutLauchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));


	// Calculate the OutLaunchVelocity
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
	(
		this,
		OutLauchVelocity,
		StartLocation,
		HitLocation,
		LauchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);


	if (bHaveAimSolution) {
		auto AimDirection = OutLauchVelocity.GetSafeNormal(); // unit vector
		MoveBarrelTowards(AimDirection);
	}
}


void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	if (!ensure(Barrel) || !ensure(Turret)) return;

	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;
	Barrel->Elevate(DeltaRotator.Pitch);
	Turret->Rotate(DeltaRotator.Yaw);

	return;
}


void UTankAimingComponent::Initialise(UTankBarrel * BarrelToSet, UTankTurret * TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}
