// Copyright TABIUK Ltd.

#include "TankTrack.h"
#include "Engine/World.h"
#include "Components/PrimitiveComponent.h"


void UTankTrack::SetThrottle(float Throttle)
{
	if (Throttle == 0.0f) return;

	auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}

