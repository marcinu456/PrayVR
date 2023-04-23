// Created by Cookie Core

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ButterflySpawner.generated.h"

USTRUCT(BlueprintType)
struct FButterflySetup
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", Category = "ButterflySetup"))
	float sigma = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", Category = "ButterflySetup"))
	float rho = 28;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", Category = "ButterflySetup"))
	float beta = 8 / 3;
};


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


	//UPROPERTY(EditAnywhere)
	//	TArray<AButterflyActor*> ButterflyActors;


	/** Class for cell. */
	//UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true", Category = "ButterflySetup"))
	//	TSubclassOf<AButterflyActor> ButterflyActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", Category = "ButterflySetup"))
		int32 numberOfButterfly = 4;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", Category = "ButterflySetup"))
		float ButterflyDeltaTime = 0.002;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", Category = "ButterflySetup"))
		TArray<FButterflySetup> ButterflySetupArray;
	
	UFUNCTION(BlueprintCallable)
		FVector UpdatePosition(FButterflySetup ButterflySetup, FVector Position);
};


