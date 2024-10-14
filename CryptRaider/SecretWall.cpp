#include "SecretWall.h"

#include "Components/BoxComponent.h"
#include "Mover.h"
#include "UnlockStand.h"
#include "DoorTrigger.h"

// Sets default values
ASecretWall::ASecretWall()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	RootComponent = BaseMesh;

	MoverComponent = CreateDefaultSubobject<UMover>(TEXT("Mover Component"));
}

// Called when the game starts or when spawned
void ASecretWall::BeginPlay()
{
	Super::BeginPlay();

	if (UnlockStandClass != nullptr)
	{
		UnlockStandClass->GetDoorTrigger()->OnDoorOpened.AddDynamic(this, &ASecretWall::OpenDoor);
		UnlockStandClass->GetDoorTrigger()->OnDoorClosed.AddDynamic(this, &ASecretWall::CloseDoor);
	}

}

// Called every frame
void ASecretWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASecretWall::OpenDoor()
{
	MoverComponent->SetShouldMoveDown(true);
	MoverComponent->SetShouldMoveUp(false);
}

void ASecretWall::CloseDoor()
{
	MoverComponent->SetShouldMoveDown(false);
	MoverComponent->SetShouldMoveUp(true);
}
