// Copyright TABIUK Ltd.

#pragma once

#include "AIController.h"
#include "TankAIController.generated.h"

class UTankAimingComponent;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

protected:
	// How close can the AI tank get 
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float AcceptanceRadius = 80000.0; // in cm

private:
	virtual void SetPawn(APawn* InPawn) override;

	UTankAimingComponent* AiminComponent = nullptr;


	UFUNCTION(Category = "Callback")
	void OnPossedTankDeath();
};
