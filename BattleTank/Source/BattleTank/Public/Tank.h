// Copyright TABIUK Ltd.

#pragma once
#include "GameFramework/Pawn.h"
#include "Runtime/Core/Public/Delegates/DelegateCombinations.h"
#include "Tank.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);

// Enum for aiming state
UENUM()
enum class ETankObjectType : uint8
{
	Tank,
	Mortar
};

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	// Called by the engine when actor damage is dealt
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	//Return current health as a percentage of starting health, between 0 and 1
	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHealthPercent() const;

	ETankObjectType GetTankObjectType() const;


	FTankDelegate OnDeath;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
    int32 StartingHealth = 100.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	ETankObjectType TankObjectType = ETankObjectType::Tank;

	UPROPERTY(VisibleAnywhere, Category = "Health")
	int32 CurrentHealth = StartingHealth;

};
