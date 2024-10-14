#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayTagContainer.h"

#include "KeyStatue.generated.h"


UCLASS()
class CRYPTRAIDER_API AKeyStatue : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AKeyStatue();

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Tags")
	FGameplayTagContainer TagsContainer;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Visuals")
	UStaticMeshComponent* StatueMesh;
};
