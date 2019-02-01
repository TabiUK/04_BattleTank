// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankBarrel;
class UTankTurret;
class UTankAimingComponent;
class ARProjectile;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrelReference(UTankBarrel* BarrelToSet);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetTurretReference(UTankTurret * TurretToSet);

	UFUNCTION(BlueprintCallable, Category = Firing)
	void Fire();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UTankAimingComponent* TankAimingComponent = nullptr;

private:

   UPROPERTY(EditAnywhere, Category = Firing)
   float LauchSpeed = 4000.0f; // 4000 m/s

   UPROPERTY(EditAnywhere, Category = Setup)
   TSubclassOf<ARProjectile> ProjectileBlueprint; // see https://docs.unrealengine.com/latest/INT/Programming/UnrealArchitecture/TSubclassOf

   // Local barrel refence for spawning projectile
   UTankBarrel* Barrel = nullptr;
	
};
