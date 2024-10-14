// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameplayTagContainer.h"

#include "DoorTrigger.generated.h"

class UMover;
class ASecretWall;
class AKeyStatue;

UDELEGATE(BlueprintCallable)
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDoorTriggeredDelegate);

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class CRYPTRAIDER_API UDoorTrigger : public UBoxComponent
{
	GENERATED_BODY()

public:
	UDoorTrigger();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintAssignable, Category = "Unlock")
	FOnDoorTriggeredDelegate OnDoorOpened;
	UPROPERTY(BlueprintAssignable, Category = "Unlock")
	FOnDoorTriggeredDelegate OnDoorClosed;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	AKeyStatue* AcceptedActor;

	UPROPERTY(EditAnywhere, Category = "Unlock")
	FGameplayTagContainer TagsToUnlock;


	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:
	bool HasSentOpenDelegate;
};
