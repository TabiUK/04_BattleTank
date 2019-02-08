// Copyright TABIUK Ltd.

#include "TankBarrel.h"
#include "Engine/World.h"
#include "CoreMinimal.h"

void UTankBarrel::Elevate(float RelativeSpeed)
{
	if (RelativeSpeed == 0.0f) return;

	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1.0f, 1.0f);
	auto ElevationChange = RelativeSpeed * MaxDegreePerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;
	auto Elevation = FMath::Clamp<float>(RawNewElevation, MinElevationDegrees, MaxElevationDegrees);
	SetRelativeRotation(FRotator(Elevation, 0.0f, 0.0f));
}
