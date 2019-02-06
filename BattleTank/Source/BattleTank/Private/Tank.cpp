// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "CoreMinimal.h"
#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "RProjectile.h"
#include "Engine/World.h"
#include "TankMovementComponent.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


void ATank::AimAt(FVector HitLocation)
{
	TankAimingComponent->AimAt(HitLocation, LauchSpeed);
}


void ATank::SetBarrelReference(UTankBarrel * BarrelToSet)
{
	if (BarrelToSet == nullptr) return;
	TankAimingComponent->SetBarrelReference(BarrelToSet);
	Barrel = BarrelToSet;
}


void ATank::SetTurretReference(UTankTurret * TurretToSet)
{
	if (TurretToSet == nullptr) return;
	TankAimingComponent->SetTurretReference(TurretToSet);
}


void ATank::Fire()
{
	bool isReloaded = (GetWorld()->GetTimeSeconds() - LastFireTime) > ReloadTimeInSceonds;
	if (!isReloaded) return;
	if (Barrel == nullptr) return;

	auto Projectile = GetWorld()->SpawnActor<ARProjectile>(
		ProjectileBlueprint,
		Barrel->GetSocketLocation(FName("Projectile")),
		Barrel->GetSocketRotation(FName("Projectile"))
		);

	if (Projectile == nullptr) return;

	Projectile->LaunchProjectile(LauchSpeed);
	LastFireTime = GetWorld()->GetTimeSeconds();
}
