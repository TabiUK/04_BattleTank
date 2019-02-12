// Copyright TABIUK Ltd.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * TankTrack is used to set maximum driving force, and to apply force to the tank.
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	// Sets a throttle between -1 and +1
	UFUNCTION(BlueprintCallable, Category = "Input")
	void SetThrottle(float Throttle);
	
	//  Force (F) is measured in newtons (N)
	//  mass(m) is measured in kilograms(kg)
	//  acceleration(a) is measured in metres per second squared(m / s²)
	// F = m a
	// F = 22 x 15
	// F = 330 N
	// Max force per track in Newtons
	UPROPERTY(EditDefaultsOnly)
	float TrackMaxDrivingForce = 4000000.0; //Assume 40 tonne tank, and 1g accelleration 

protected:
	virtual void BeginPlay() override;

private:
	UTankTrack();
	void ApplySidewaysForce();
	void DriveTrack();

	UFUNCTION(Category = "CallBack")
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	float CurrentThrottle = 0;
};
