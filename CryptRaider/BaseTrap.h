// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayTagContainer.h"

#include "BaseTrap.generated.h"

UCLASS()
class CRYPTRAIDER_API ABaseTrap : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseTrap();
	
	UPROPERTY(EditAnywhere, Category = "Tags")
	FGameplayTagContainer TagsContainer;

	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	virtual void Activate();

	UFUNCTION(BlueprintCallable)
	virtual void Deactivate();

};
