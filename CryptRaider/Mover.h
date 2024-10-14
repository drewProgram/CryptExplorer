// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Mover.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CRYPTRAIDER_API UMover : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMover();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void SetShouldMoveDown(bool value);

	UFUNCTION(BlueprintCallable)
	void SetShouldMoveUp(bool value);

	UFUNCTION(BlueprintCallable)
	bool GetShouldMoveDown();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	FVector MoveOffset;

	UPROPERTY(EditAnywhere)
	float MoveTime;

	UPROPERTY(EditAnywhere)
	bool ShouldMoveDown;

	UPROPERTY(EditAnywhere)
	bool ShouldMoveUp;

	FVector OriginalLocation;
};
