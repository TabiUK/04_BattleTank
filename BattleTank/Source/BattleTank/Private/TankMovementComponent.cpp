// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "Engine/World.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	if (LeftTrackToSet == nullptr || RightTrackToSet == nullptr) return;
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
	return;
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (Throw == 0.0f) return;

	if (LeftTrack == nullptr || RightTrack == nullptr) return;
	//auto Time = GetWorld()->GetTimeSeconds();
	//auto Name = GetName();
	//UE_LOG(LogTemp, Warning, TEXT("%f: %s IntendMoveForward to: %f"), Time, *Name, Throw);
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);

}


void UTankMovementComponent::IntendTurnRight(float Throw)
{
	if (Throw == 0.0f) return;
	auto Time = GetWorld()->GetTimeSeconds();
	auto Name = GetName();
	UE_LOG(LogTemp, Warning, TEXT("%f: %s IntendMoveForward to: %f"), Time, *Name, Throw);


	if (LeftTrack == nullptr || RightTrack == nullptr) return;
	//auto Time = GetWorld()->GetTimeSeconds();
	//auto Name = GetName();
	//UE_LOG(LogTemp, Warning, TEXT("%f: %s IntendMoveForward to: %f"), Time, *Name, Throw);
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);

}