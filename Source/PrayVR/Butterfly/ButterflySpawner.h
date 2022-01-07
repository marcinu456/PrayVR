// Created by Cookie Core

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ButterflySpawner.generated.h"

class AButterflyActor;
UCLASS()
class PRAYVR_API AButterflySpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AButterflySpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
private:

	TArray<AButterflyActor*> ButterflyActors;

	/** Class for cell. */
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true", Category = "Grid Setup"))
		TSubclassOf<AButterflyActor> ButterflyActor;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true", Category = "Setup"))
		int32 numberOfButterfly = 4;
};
