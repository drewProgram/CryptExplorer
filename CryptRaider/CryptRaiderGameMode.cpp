// Copyright Epic Games, Inc. All Rights Reserved.

#include "CryptRaiderGameMode.h"
#include "CryptRaiderCharacter.h"
#include "Grabber.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"

ACryptRaiderGameMode::ACryptRaiderGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;
}

void ACryptRaiderGameMode::FinishGame()
{
	// Spawn Widget with text congratulating player
	UE_LOG(LogTemp, Warning, TEXT("You won the game!"));

	WriteEndMessage();

	// Spawn win sound

	// Return to menu

}

void ACryptRaiderGameMode::RespawnPlayer()
{
	// Fade screen to black and respawn
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	if (PlayerController)
	{
		APawn* PlayerPawn = PlayerController->GetPawn();
		if (PlayerPawn)
		{
			RenderDamageScreen();
			WriteDeathMessage();
			ACryptRaiderCharacter* PlayerCharacter = Cast<ACryptRaiderCharacter>(PlayerPawn);
			if (PlayerCharacter)
			{
				// If we dont release the item, it will bug and disappear
				PlayerCharacter->GetGrabberComponent()->ReleaseItem();
			}
			PlayerPawn->SetActorLocation(RespawnLocation);
		}
	}
}

void ACryptRaiderGameMode::BeginPlay()
{
	Super::BeginPlay();

}
