// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"

#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"

#include "KeyStatue.h"
#include "CRGameplayTags.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
	: MaxGrabDistance(400.f),
	GrabRadius(100.f),
	HoldDistance(200.f)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	PhysHandleComponent = CreateDefaultSubobject<UPhysicsHandleComponent>(TEXT("Physics Handle Component"));
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PhysHandleComponent == nullptr)
	{
		return;
	}

	if (PhysHandleComponent->GetGrabbedComponent() != nullptr)
	{
		FVector TargetLocation = GetComponentLocation() + GetForwardVector() * HoldDistance;
		PhysHandleComponent->SetTargetLocationAndRotation(TargetLocation, GetComponentRotation());
	}

}

bool UGrabber::TryToGrab()
{
	if (PhysHandleComponent == nullptr)
	{
		return false;
	}

	FVector Start = GetComponentLocation();
	FVector End = Start + GetForwardVector() * MaxGrabDistance;
	DrawDebugLine(GetWorld(), Start, End, FColor::Red);
	DrawDebugSphere(GetWorld(), End, 10, 10, FColor::Blue, false, 5);

	FCollisionShape Sphere = FCollisionShape::MakeSphere(GrabRadius);
	FHitResult HitResult;
	// Custom Trace Channels are defined in DefaultEngine.ini
	bool HasHit = GetWorld()->SweepSingleByChannel(
		HitResult, Start, End, FQuat::Identity, ECC_GameTraceChannel2, Sphere
	);

	if (HasHit)
	{
		FString HitActorName = HitResult.GetActor()->GetActorNameOrLabel();
		UE_LOG(LogTemp, Display, TEXT("Name of actor hit: %s"), *HitActorName);

		UPrimitiveComponent* HitComponent = HitResult.GetComponent();
		HitComponent->SetSimulatePhysics(true);
		HitComponent->WakeAllRigidBodies();

		DrawDebugSphere(GetWorld(), HitResult.Location, 10, 10, FColor::Green, false, 5);
		DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10, 10, FColor::Red, false, 5);

		PhysHandleComponent->GrabComponentAtLocationWithRotation(
			HitComponent,
			NAME_None,
			HitResult.ImpactPoint,
			GetComponentRotation()
		);

		AKeyStatue* KeyStatue = Cast<AKeyStatue>(HitResult.GetActor());
		if (KeyStatue)
		{
			KeyStatue->TagsContainer.AddTag(CRGameplayTags::Grabber_Grabbed);
			return true;
		}
	}

	return false;
}

void UGrabber::ReleaseItem()
{
	if (!PhysHandleComponent)
	{
		return;
	}

	if (PhysHandleComponent->GetGrabbedComponent() != nullptr)
	{
		AKeyStatue* KeyStatue = Cast<AKeyStatue>(PhysHandleComponent->GetGrabbedComponent()->GetOwner());
		if (KeyStatue)
		{
			PhysHandleComponent->GetGrabbedComponent()->WakeAllRigidBodies();
			KeyStatue->TagsContainer.RemoveTag(CRGameplayTags::Grabber_Grabbed);
			PhysHandleComponent->ReleaseComponent();

			return;
		}
		UE_LOG(LogTemp, Warning, TEXT("Could not release item!!!! Item is not of type KeyStatue"));
	}

	UE_LOG(LogTemp, Warning, TEXT("Could not release item!!!! nullptr"));
}
