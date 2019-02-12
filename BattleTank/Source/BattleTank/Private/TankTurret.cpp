// Copyright TABIUK Ltd.

#include "TankTurret.h"
#include "Engine/World.h"
#include "CoreMinimal.h"


void UTankTurret::Rotate(float RelativeSpeed)
{

	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1.0f, 1.0f);
	auto RotationChange = RelativeSpeed * MaxDegreePerSecond * GetWorld()->DeltaTimeSeconds;
	auto Rotation = RelativeRotation.Yaw + RotationChange;
	SetRelativeRotation(FRotator(0.0f, Rotation, 0.0f));
}

