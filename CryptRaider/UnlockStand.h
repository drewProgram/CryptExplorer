// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UnlockStand.generated.h"

class UDoorTrigger;

UCLASS()
class CRYPTRAIDER_API AUnlockStand : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AUnlockStand();

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	UDoorTrigger* GetDoorTrigger();

	UFUNCTION(BlueprintCallable)
	void FixKeyOnStand(AActor* Key);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(EditDefaultsOnly)
	UDoorTrigger* DoorTrigger;

	UPROPERTY(VisibleAnywhere, Category = "Unlock")
	USceneComponent* KeyLocation;

};
