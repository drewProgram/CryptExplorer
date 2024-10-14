// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SecretWall.generated.h"

class UMover;
class UBoxComponent;
class AUnlockStand;

UCLASS()
class CRYPTRAIDER_API ASecretWall : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASecretWall();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Observer")
	AUnlockStand* UnlockStandClass;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(EditAnywhere)
	UBoxComponent* KeyAreaCollision;

	UPROPERTY(EditAnywhere)
	UMover* MoverComponent;

	UFUNCTION()
	void CloseDoor();

	UFUNCTION()
	void OpenDoor();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
