// Copyright TABIUK Ltd.

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
	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = "Firing")
	void Fire();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly)
	UTankAimingComponent* TankAimingComponent = nullptr;

private:

   UPROPERTY(EditDefaultsOnly, Category = "Setup")
   TSubclassOf<ARProjectile> ProjectileBlueprint; // see https://docs.unrealengine.com/latest/INT/Programming/UnrealArchitecture/TSubclassOf

   //TODO remove once firing is moved to aiming component
   UPROPERTY(EditDefaultsOnly, Category = "Firing")
   float LauchSpeed = 4000.0f; // 4000 m/s

   UPROPERTY(EditDefaultsOnly, Category = "Firing")
   float ReloadTimeInSceonds = 3.0f;

   UTankBarrel* Barrel = nullptr;

   double LastFireTime = 0;

};
