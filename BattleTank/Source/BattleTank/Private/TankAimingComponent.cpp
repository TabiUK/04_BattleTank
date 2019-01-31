// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "GameFramework/Pawn.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/GameplayStaticsTypes.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


void UTankAimingComponent::AimAt(FVector HitLocation, float LauchSpeed)
{
	if (Barrel == nullptr) return;

	FVector OutLauchVelocity = FVector(.0);
	FCollisionResponseParams ResponseParam = FCollisionResponseParams();
	TArray < AActor * > ActorsToIgnore = TArray < AActor * >();

	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));


	// Calculate the OutLaunchVelocity
	bool res = UGameplayStatics::SuggestProjectileVelocity
	(
		this,
		OutLauchVelocity,
		StartLocation,
		HitLocation,
		LauchSpeed,
		false,
		0.0f,
		0.0f,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);

	if (res) {
		auto AimDirection = OutLauchVelocity.GetSafeNormal(); // unit vector
		auto TankName = GetOwner()->GetName();
		UE_LOG(LogTemp, Warning, TEXT("Tank %s Aming at %s"), *TankName, *AimDirection.ToString());
	}
}


void UTankAimingComponent::SetBarrelReference(UStaticMeshComponent* BarrelToSet)
{
	Barrel = BarrelToSet;
}
