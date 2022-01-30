// Created by Cookie Core

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AgentBase.generated.h"

UCLASS()
class PRAYVR_API AAgentBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAgentBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
protected:

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* StaticMeshComponent;

	/** sphere component */
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
		class USphereComponent* Sphere1;

public:
	/** called when something enters the sphere component */
	UFUNCTION()
		virtual void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	/** called when something leaves the sphere component */
	UFUNCTION()
		virtual void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


	bool currentStatus = true;
	int32 hp;

	virtual void OnDestroy();

	void SetOverlap(bool bOverlap);

	void SetBasicMaterial();

	void SetBeginMaterial();

	void SetClickedMaterial();

	void SetUpAgent(bool bSetup);

protected:
	virtual void Move() {};

	class AAgentSpawner* AgentSpawner;

	/** Material for when the cell is alive. */
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true", Category = "Materials"))
		UMaterialInterface* BasicMaterial;
	/** Material for when player hovers over the cell in edit mode. */
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true", Category = "Materials"))
		UMaterialInterface* BeginOverMaterial;
	/** Material for when the cell is alive. */
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true", Category = "Materials"))
		UMaterialInterface* ClickedMaterial;

};
