// Fill out your copyright notice in the Description page of Project Settings.


#include "UnlockStand.h"
#include "DoorTrigger.h"

// Sets default values
AUnlockStand::AUnlockStand()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(RootComponent);

	DoorTrigger = CreateDefaultSubobject<UDoorTrigger>(TEXT("Door Trigger"));
	DoorTrigger->SetupAttachment(BaseMesh);

	KeyLocation = CreateDefaultSubobject<USceneComponent>(TEXT("Unlock Object Location"));
	KeyLocation->SetupAttachment(BaseMesh);

}

// Called when the game starts or when spawned
void AUnlockStand::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AUnlockStand::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

UDoorTrigger* AUnlockStand::GetDoorTrigger()
{
	return DoorTrigger;
}

void AUnlockStand::FixKeyOnStand(AActor* Key)
{
	UE_LOG(LogTemp, Warning, TEXT("Yo"));
	if (Key)
	{
		UE_LOG(LogTemp, Warning, TEXT("Location: %s"), *KeyLocation->GetComponentLocation().ToString());
		
		Key->DisableComponentsSimulatePhysics();
		
		Key->SetActorLocationAndRotation(KeyLocation->GetComponentLocation(), GetActorRotation());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Key is nullptr"));
	}
}
