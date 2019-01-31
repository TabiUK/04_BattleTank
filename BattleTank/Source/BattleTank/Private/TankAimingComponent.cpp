// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "GameFramework/Pawn.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/GameplayStaticsTypes.h"
#include "TankBarrel.h"
#include "Engine/World.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UTankAimingComponent::AimAt(FVector HitLocation, float LauchSpeed)
{
	if (Barrel == nullptr) return;

	FVector OutLauchVelocity = FVector(.0);
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));


	// Calculate the OutLaunchVelocity
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
	(
		this,
		OutLauchVelocity,
		StartLocation,
		HitLocation,
		LauchSpeed,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);


	if (bHaveAimSolution) {
		auto AimDirection = OutLauchVelocity.GetSafeNormal(); // unit vector
		auto TankName = GetOwner()->GetName();
		MoveBarrelTowards(AimDirection);
		auto Time = GetWorld()->GetTimeSeconds();
		UE_LOG(LogTemp, Warning, TEXT("%f: aim solve found"), Time);
	} else {
		auto Time = GetWorld()->GetTimeSeconds();
		UE_LOG(LogTemp, Warning, TEXT("%f: No aim solve found"), Time);

	}
}


void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{

	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;
	UE_LOG(LogTemp, Warning, TEXT("AimAsRotator %s"), *AimAsRotator.ToString());
	Barrel->Elevate(5);
	return;
}


void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	Barrel = BarrelToSet;
}
