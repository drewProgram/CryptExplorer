#include "FloorTrap.h"

#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

#include "CRGameplayTags.h"
#include "CryptRaiderCharacter.h"
#include "CryptRaiderGameMode.h"

AFloorTrap::AFloorTrap()
	: CanDamagePlayerAgain(true)
{
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	RootComponent = BaseMesh;

	TrapActivatorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Trap Activator Mesh"));
	TrapActivatorMesh->SetupAttachment(BaseMesh);

	TrapActivatorCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Trap Activator Collider"));
	TrapActivatorCollider->SetupAttachment(TrapActivatorMesh);

	SpearsLocation = CreateDefaultSubobject<USceneComponent>(TEXT("Spears"));
	SpearsLocation->SetupAttachment(BaseMesh);

	DamageCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Damage Collider"));
	DamageCollider->SetupAttachment(SpearsLocation);

	MoveOffset = FVector(0.f, 0.f, 240.f);
}

void AFloorTrap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (SpearsLocation->GetComponentLocation() == OriginalLocation + MoveOffset)
	{
		Deactivate();
	}

	Move(DeltaTime);
}

void AFloorTrap::SetCanDamagePlayerAgain()
{
	CanDamagePlayerAgain = true;
}

void AFloorTrap::BeginPlay()
{
	Super::BeginPlay();

	OriginalLocation = SpearsLocation->GetComponentLocation();

	TrapActivatorCollider->OnComponentBeginOverlap.AddDynamic(this, &AFloorTrap::BeginOverlap);
	DamageCollider->OnComponentBeginOverlap.AddDynamic(this, &AFloorTrap::BeginDamageOverlap);
}



void AFloorTrap::Activate()
{
	Super::Activate();

	UE_LOG(LogTemp, Display, TEXT("Activate called"));
	TagsContainer.AddTag(CRGameplayTags::Trap_Activating);
	TagsContainer.RemoveTag(CRGameplayTags::Trap_Deactivating);
}

void AFloorTrap::Deactivate()
{
	Super::Deactivate();

	TagsContainer.AddTag(CRGameplayTags::Trap_Deactivating);
	TagsContainer.RemoveTag(CRGameplayTags::Trap_Activating);
}

void AFloorTrap::Move(float DeltaTime)
{
	if (TagsContainer.HasTagExact(CRGameplayTags::Trap_Activating))
	{
		FVector CurrentLocation = SpearsLocation->GetComponentLocation();
		FVector TargetLocation = OriginalLocation + MoveOffset;
		float Speed = FVector::Distance(OriginalLocation, TargetLocation) / MoveTime;

		FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, TargetLocation, DeltaTime, Speed);
		UE_LOG(LogTemp, Display, TEXT("New Location: %s"), *NewLocation.ToString());
		UE_LOG(LogTemp, Display, TEXT("Target: %s"), *TargetLocation.ToString());
		SpearsLocation->SetWorldLocation(NewLocation);
	}
	else if (TagsContainer.HasTagExact(CRGameplayTags::Trap_Deactivating))
	{
		FVector CurrentLocation = SpearsLocation->GetComponentLocation();
		float Speed = FVector::Distance(OriginalLocation, CurrentLocation);

		FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, OriginalLocation, DeltaTime, Speed);
		SpearsLocation->SetWorldLocation(NewLocation);
	}
}

void AFloorTrap::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACryptRaiderCharacter* Player = Cast<ACryptRaiderCharacter>(OtherActor);
	if (Player)
	{
		Activate();
	}
}

void AFloorTrap::BeginDamageOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (CanDamagePlayerAgain)
	{
		ACryptRaiderCharacter* Player = Cast<ACryptRaiderCharacter>(OtherActor);
		if (Player)
		{
			ACryptRaiderGameMode* GameMode = Cast<ACryptRaiderGameMode>(UGameplayStatics::GetGameMode(this));
			if (GameMode)
			{
				CanDamagePlayerAgain = false;
				FTimerHandle TimerHandle;
				GetWorldTimerManager().SetTimer(
					TimerHandle,
					this,
					&AFloorTrap::SetCanDamagePlayerAgain,
					1.f,
					false,
					0
				);
				UE_LOG(LogTemp, Warning, TEXT("Damaged"));
				GameMode->RespawnPlayer();
			}
		}
	}
}

