// Copyright TABIUK Ltd.

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"


// Enum for aiming state
UENUM()
enum class EfiringStatus : uint8
{
	Reloading,
	Aiming,
	Locked
};

// Forward Declarationg
class UTankBarrel;
class UTankTurret;
class ARProjectile;

// Holds barrels properites and elevate methods
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

	UFUNCTION(BlueprintCallable, Category = "Firing")
	void Fire();


protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EfiringStatus FiringStatus = EfiringStatus::Reloading;

private:	
	void MoveBarrelTowards(FVector AimDirection);

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<ARProjectile> ProjectileBlueprint; // see https://docs.unrealengine.com/latest/INT/Programming/UnrealArchitecture/TSubclassOf

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LauchSpeed = 4000.0f; // 4000 m/s

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float ReloadTimeInSceonds = 3.0f;

	double LastFireTime = 0;

	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;

	
};