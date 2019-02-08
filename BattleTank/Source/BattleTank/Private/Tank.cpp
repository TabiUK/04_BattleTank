// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "CoreMinimal.h"
#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "RProjectile.h"
#include "Engine/World.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();

	TankAimingComponent = FindComponentByClass<UTankAimingComponent>();
}


void ATank::AimAt(FVector HitLocation)
{

	if (!ensure(TankAimingComponent)) return;

	TankAimingComponent->AimAt(HitLocation, LauchSpeed);
}


void ATank::Fire()
{

	if (!ensure(Barrel)) return;

	bool isReloaded = (GetWorld()->GetTimeSeconds() - LastFireTime) > ReloadTimeInSceonds;
	if (!isReloaded) return;

	auto Projectile = GetWorld()->SpawnActor<ARProjectile>(
		ProjectileBlueprint,
		Barrel->GetSocketLocation(FName("Projectile")),
		Barrel->GetSocketRotation(FName("Projectile"))
		);

	if (!ensure(Projectile)) return;

	Projectile->LaunchProjectile(LauchSpeed);
	LastFireTime = GetWorld()->GetTimeSeconds();
}
