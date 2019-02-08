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

private:

	// How close can the AI tank get 
	float AcceptanceRadius = 3000.0; // in cm

	UTankAimingComponent* AiminComponent = nullptr;
};
