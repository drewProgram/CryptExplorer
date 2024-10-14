// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseTrap.h"
#include "FloorTrap.generated.h"

class UBoxComponent;

/**
 * 
 */
UCLASS()
class CRYPTRAIDER_API AFloorTrap : public ABaseTrap
{
	GENERATED_BODY()

public:
	AFloorTrap();

	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void SetCanDamagePlayerAgain();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Visuals")
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(VisibleAnywhere, Category = "Activation")
	UStaticMeshComponent* TrapActivatorMesh;

	UPROPERTY(VisibleAnywhere, Category = "Activation")
	UBoxComponent* TrapActivatorCollider;

	UPROPERTY(EditAnywhere, Category = "Activation")
	USceneComponent* SpearsLocation;

	UPROPERTY(VisibleAnywhere, Category = "Damage")
	UBoxComponent* DamageCollider;

	FVector OriginalLocation;

	UPROPERTY(EditAnywhere, Category = "Movement")
	FVector MoveOffset;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float MoveTime;

	virtual void Activate() override;
	virtual void Deactivate() override;

	void Move(float DeltaTime);

	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
		
	UFUNCTION()
	void BeginDamageOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	bool CanDamagePlayerAgain;
};
