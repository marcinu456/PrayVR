// Created by Cookie Core

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CellActor.generated.h"

UCLASS()
class PRAYVR_API ACellActor : public AActor
{
	GENERATED_BODY()
	
public:
	ACellActor();

	bool GetAlive() const {
		return Alive;
	}
	void SetAlive(const bool IsAlive) {
		this->Alive = IsAlive;
	}

	bool GetAliveNext() const {
		return AliveNext;
	}
	void SetAliveNext(const bool IsAliveNext) //const changes the function itself - this function cannot change internal fields
	{
		this->AliveNext = IsAliveNext;
	}

	/**
	 * Called after we've calculated whether this cell should be alive in the next generation.
	 * @warning Only call this after AliveNext has been set correctly.
	 */
	void Update();

	void Reset();

	void Random();

	void SetXYZ(int32 _X, int32 _Y, int32 _Z)
	{
		X = _X;
		Y = _Y;
		Z = _Z;
	}

	void GetXYZ(int32& _X, int32& _Y, int32& _Z)
	{
		_X = X;
		_Y = Y;
		_Z = Z;
	}

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable)
		void Clicked();
	UFUNCTION(BlueprintCallable)
		void BeginCursorOver();
	UFUNCTION(BlueprintCallable)
		void EndCursorOver();

private:
	mutable bool Alive;
	bool AliveNext;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* StaticMeshComponent;

	/** Material for when the cell is alive. */
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true", Category = "Materials"))
		UMaterialInterface* ClickedMaterial;
	/** Material for when player hovers over the cell in edit mode. */
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true", Category = "Materials"))
		UMaterialInterface* BeginCursorOverMaterial;
	/** Material for when the cell is not alive in edit mode. */
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true", Category = "Materials"))
		UMaterialInterface* EndCursorOverMaterial;

	UPROPERTY(EditAnywhere, Category = "Settings")
		int32 X;
	UPROPERTY(EditAnywhere, Category = "Settings")
		int32 Y;
	UPROPERTY(EditAnywhere, Category = "Settings")
		int32 Z;
};
