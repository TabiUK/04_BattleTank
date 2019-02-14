// Copyright TABIUK Ltd.

#include "Tank.h"
#include "CoreMinimal.h"
#include "Engine/World.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}


void ATank::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = StartingHealth;
}


float ATank::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	int32 DamagePoints = FPlatformMath::RoundToInt(Damage);
	auto DamageToApply = FMath::Clamp<int32>(DamagePoints, 0, CurrentHealth);

	CurrentHealth -= DamageToApply;
	if (CurrentHealth <= 0) OnDeath.Broadcast();

	return DamageToApply;

}


float ATank::GetHealthPercent() const
{
	return (float)CurrentHealth / (float)StartingHealth;
}


ETankObjectType ATank::GetTankObjectType() const
{
	return TankObjectType;
}
