// Created by Cookie Core

#pragma once

#include <vector>

#include "CoreMinimal.h"
#include "GridActor.h"
#include "GridActor3D.generated.h"

class ACellActor;

//USTRUCT()
//struct FCellArrayZ
//{
//	GENERATED_USTRUCT_BODY()
//
//		UPROPERTY()
//		TArray<ACellActor*> CellY;
//
//};
//
//USTRUCT()
//struct FCellArrayY
//{
//	GENERATED_USTRUCT_BODY()
//
//		UPROPERTY()
//		TArray<FCellArrayZ> CellZ;
//
//};



UCLASS()
class PRAYVR_API AGridActor3D : public AGridActor
{
	GENERATED_BODY()

public:
	AGridActor3D();
	/**
	 * Updates the visibility of the cells for edit mode.
	 * All cells are set to be visible.
	 */
	virtual void ToEditMode() override;

	/**
	 * Updates the visibility of the cells for play mode.
	 * Dead cells are set to be invisible and alive cells are set to be visible.
	 */
	virtual void ToPlayMode() override;

	virtual void Reset() override;

	virtual void RandomGrid() override;

protected:
	virtual void BeginPlay() override;



	/**
	* Counts the number of alive neighbors for the cell at index j + i * width.
	*/
	int32 CountAliveNeighbors(const int32 i, const int32 j, const int32 k);

	/**
	* Updates the cells' AliveNext field based on the rules of the game.
	*/
	void UpdateAliveNext(const int32 i, const int32 j, const int32 k, const int32 NumAliveNeighbors);

	/**
	* Populates the AliveNext field of all the cells in the grid to be able to advance to the next generation.
	*/
	virtual void GenerateNext();

	/**
	* Updates the visibility and Alive field of the cells in the grid.
	*/
	virtual void UpdateNext();


	std::vector<std::vector<std::vector<ACellActor*>>> CellActors3D; //row-major

	/** Deep of grid in number of cells. */
	UPROPERTY(EditAnywhere, meta = (ClampMin = "1", AllowPrivateAccess = "true", Category = "Grid Setup"))
	int Deep = 10;

};
