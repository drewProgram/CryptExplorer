#include "BaseTrap.h"

// Sets default values
ABaseTrap::ABaseTrap()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseTrap::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABaseTrap::Activate()
{
	// TODO: visual effects or sounds
}

void ABaseTrap::Deactivate()
{
	// TODO: visual effects or sounds
}

// Called every frame
void ABaseTrap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

