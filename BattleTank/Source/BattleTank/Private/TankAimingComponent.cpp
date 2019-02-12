// Copyright TABIUK Ltd.

#include "TankAimingComponent.h"
#include "GameFramework/Pawn.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/GameplayStaticsTypes.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "RProjectile.h"
#include "Engine/World.h"
#include "CoreMinimal.h"


// Sets default values for this component's properties

UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// so that first fire is after initial reload
	LastFireTime = GetWorld()->GetTimeSeconds();
}


void UTankAimingComponent::Initialise(UTankBarrel * BarrelToSet, UTankTurret * TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}


void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	if (RoundsLeft <= 0) {
		FiringStatus = EfiringStatus::OutOfAmmo;
	} else if ((GetWorld()->GetTimeSeconds() - LastFireTime) < ReloadTimeInSceonds)
	{
		FiringStatus = EfiringStatus::Reloading;
	} else if (IsBarrelMoving()) {
		FiringStatus = EfiringStatus::Aiming;
	}
	else {
		FiringStatus = EfiringStatus::Locked;

	}

}


bool UTankAimingComponent::IsBarrelMoving() const
{
	if (!ensure(Barrel)) return false;
	auto BarrelForward = Barrel->GetForwardVector();
	return (!BarrelForward.Equals(AimDirection, 0.1));
}


void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (!ensure(Barrel)) return;

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
		AimDirection = OutLauchVelocity.GetSafeNormal(); // unit vector
		MoveBarrelTowards(AimDirection);
	}
}


EfiringStatus UTankAimingComponent::GetFiringStatus() const
{
	return FiringStatus;
}


int UTankAimingComponent::GetRoundsLeft() const
{
	return RoundsLeft;
}


void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	if (!ensure(Barrel) || !ensure(Turret)) return;

	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;

	// Always yaw the shprtest way
	Barrel->Elevate(DeltaRotator.Pitch);
	if (FMath::Abs<float>(DeltaRotator.Yaw) < 180.0f)
	{
		Turret->Rotate(DeltaRotator.Yaw);
	} else {  // Avoid going the long-way round
		Turret->Rotate(-DeltaRotator.Yaw);
	}

	return;
}


void UTankAimingComponent::Fire()
{

	if (FiringStatus == EfiringStatus::Reloading || FiringStatus == EfiringStatus::OutOfAmmo) return;

	if (!ensure(Barrel) || !ensure(ProjectileBlueprint)) return;

	auto Projectile = GetWorld()->SpawnActor<ARProjectile>(
		ProjectileBlueprint,
		Barrel->GetSocketLocation(FName("Projectile")),
		Barrel->GetSocketRotation(FName("Projectile"))
		);

	if (!ensure(Projectile)) return;

	Projectile->LaunchProjectile(LauchSpeed);
	LastFireTime = GetWorld()->GetTimeSeconds();
	if (RoundsLeft > 0) RoundsLeft--;
}