// Created by Cookie Core

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Pendulum.generated.h"

UCLASS()
class PRAYVR_API APendulum : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APendulum();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	void computeAnglesEuler(float dt);
	void computeAnglesRunge(float dt);
	void computePosition();

	void air();


	float px = 0;
	float py = 0;

	float x0 = 0;
	float y0 = 0;
	float theta0prim = 0;
	float theta0bis = 0;
	float theta0 = 0;
	float length0 = 0;
	float mass0 = 0;

	float x1 = 0;
	float y1 = 0;
	float theta1prim = 0.0;
	float theta1bis = 0;
	float theta1 = 0;
	float length1 = 0;
	float mass1 = 0;


	float g = 9.81;

	UPROPERTY()
		TArray<class USplineMeshComponent*> ColumnsPathMeshPool;

	UPROPERTY(VisibleAnywhere)
		class USplineComponent* FirstColumn;

	UPROPERTY()
		TArray<class USplineMeshComponent*> FirstSplineColumn;

	UPROPERTY(EditDefaultsOnly)
		class UStaticMesh* FirstColumnArchMesh;

	UPROPERTY(EditDefaultsOnly)
		class UMaterialInterface* FirstColumnArchMaterial;

	UPROPERTY(EditDefaultsOnly)
		class UStaticMesh* SecondColumnArchMesh;

	UPROPERTY(EditDefaultsOnly)
		class UMaterialInterface* SecondColumnArchMaterial;

};
