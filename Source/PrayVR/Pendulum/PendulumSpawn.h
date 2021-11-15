// Created by Cookie Core

#pragma once

#include "CoreMinimal.h"
#include "Pendulum.h"
#include "GameFramework/Actor.h"
#include "PendulumSpawn.generated.h"

UCLASS()
class PRAYVR_API APendulumSpawn : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APendulumSpawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	UPROPERTY()
	TArray<APendulum*> PendulumActors; //row-major

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<APendulum> PendulumClass;

};
