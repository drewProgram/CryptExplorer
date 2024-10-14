#include "KeyStatue.h"

// Sets default values
AKeyStatue::AKeyStatue()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StatueMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = StatueMesh;
}

// Called when the game starts or when spawned
void AKeyStatue::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AKeyStatue::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
