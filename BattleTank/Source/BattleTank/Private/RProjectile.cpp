// Copyright TABIUK Ltd.

#include "RProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Engine/World.h"


// Sets default values
ARProjectile::ARProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile Movement"));
	ProjectileMovementComponent->bAutoActivate = false;
}

// Called when the game starts or when spawned
void ARProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



void ARProjectile::LaunchProjectile(float speed)
{
	ProjectileMovementComponent->SetVelocityInLocalSpace(FVector::ForwardVector * speed);
	ProjectileMovementComponent->Activate();
}