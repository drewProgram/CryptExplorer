#include "DoorTrigger.h"

#include "SecretWall.h"
#include "Mover.h"
#include "UnlockStand.h"
#include "CRGameplayTags.h"
#include "KeyStatue.h"

UDoorTrigger::UDoorTrigger()
	: AcceptedActor(nullptr), HasSentOpenDelegate(false)
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UDoorTrigger::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (AcceptedActor && !AcceptedActor->TagsContainer.HasTagExact(CRGameplayTags::Grabber_Grabbed) && !HasSentOpenDelegate)
	{
		UE_LOG(LogTemp, Warning, TEXT("Entrou"));
		OnDoorOpened.Broadcast();
		HasSentOpenDelegate = true;
		
		AUnlockStand* UnlockStand = Cast<AUnlockStand>(GetOwner());
		if (UnlockStand)
		{
			UnlockStand->FixKeyOnStand(AcceptedActor);
		}
	}
}

void UDoorTrigger::BeginPlay()
{
	Super::BeginPlay();
	OnComponentBeginOverlap.AddDynamic(this, &UDoorTrigger::BeginOverlap);
	OnComponentEndOverlap.AddDynamic(this, &UDoorTrigger::EndOverlap);
}

void UDoorTrigger::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AKeyStatue* KeyStatue = Cast<AKeyStatue>(OtherActor);
	if (KeyStatue)
	{
		UE_LOG(LogTemp, Warning, TEXT("Overlap"));
		if (KeyStatue->TagsContainer.HasAnyExact(TagsToUnlock))
		{
			AcceptedActor = KeyStatue;
		}
	}
}

void UDoorTrigger::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AKeyStatue* KeyStatue = Cast<AKeyStatue>(OtherActor);
	if (KeyStatue)
	{
		if (KeyStatue == AcceptedActor)
		{
			AcceptedActor = nullptr;
			OnDoorClosed.Broadcast();
			HasSentOpenDelegate = false;
		}
	}
}
