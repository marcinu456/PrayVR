// Created by Cookie Core

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "TestGameState.generated.h"

class AGridActor3D;
/**
 * 
 */
UCLASS()
class PRAYVR_API ATestGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	bool GetEditMode() {
		return EditMode;
	}
	void SetEditMode(const bool Editing);

	float GetAdvanceTime() {
		return AdvanceTime;
	}

	void StartTimers();
	void ClearTimers();
	void Reset();

	void SpeedUp();
	void SlowDown();

protected:
	virtual void BeginPlay() override;

private:
	bool EditMode;
	TArray<AGridActor3D*> GridActors; //row-major

	/** Time before the grid advances to the next generation. */
	UPROPERTY(EditAnywhere, meta = (ClampMin = "0.1", ClampMax = "10.0", AllowPrivateAccess = "true", Category = "Level Setup"))
		float AdvanceTime = 0.5f;
	/** Transforms for the grids to spawn. */
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true", Category = "Level Setup"))
		TArray<FTransform> Transforms;
	/** Class for grid. */
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true", Category = "Level Setup"))
		TSubclassOf<AGridActor3D> GridActor;

};
