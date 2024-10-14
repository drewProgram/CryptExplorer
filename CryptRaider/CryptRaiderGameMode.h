// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CryptRaiderGameMode.generated.h"

UCLASS(minimalapi)
class ACryptRaiderGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ACryptRaiderGameMode();

	UFUNCTION(BlueprintCallable)
	void FinishGame();

	UFUNCTION(BlueprintImplementableEvent)
	void WriteEndMessage();

	UFUNCTION(BlueprintImplementableEvent)
	void WriteDeathMessage();

	UFUNCTION(BlueprintImplementableEvent)
	void RenderDamageScreen();

	UFUNCTION(BlueprintCallable)
	void RespawnPlayer();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Game Rule")
	FVector RespawnLocation;

private:
	
	UPROPERTY(BlueprintReadWrite, Category = "Game Rule", meta = (AllowPrivateAccess = "true"))
	bool bFinalStandActivated;


};
