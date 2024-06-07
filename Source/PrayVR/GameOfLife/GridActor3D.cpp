// Created by Cookie Core


#include "GridActor3D.h"

#include "CellActor.h"
#include "Kismet/GameplayStatics.h"
#include "PrayVR/Test/TestGameState.h"

AGridActor3D::AGridActor3D()
{
	PrimaryActorTick.bCanEverTick = true;

	AdvanceTime = 1.5f;
	maxTimer = 5.f;
	minTimer = 0.1f;
}


void AGridActor3D::BeginPlay()
{
	Super::BeginPlay();

	TArray<UStaticMeshComponent*> Components;
	CellActor.GetDefaultObject()->GetComponents<UStaticMeshComponent>(Components);
	const FVector BoxExtent = Components[0]->GetStaticMesh()->GetBounds().BoxExtent;
	const FVector Scale = Components[0]->GetRelativeTransform().GetScale3D();

	ensure(Components.Num() > 0);

	const float EffectiveBoxExtentX = BoxExtent.X * Scale.X + Offset;
	const float EffectiveBoxExtentY = BoxExtent.Y * Scale.Y + Offset;
	const float EffectiveBoxExtentZ = BoxExtent.Z * Scale.Z + Offset;
	const float XStep = EffectiveBoxExtentX * 2;
	const float YStep = EffectiveBoxExtentY * 2;
	const float ZStep = EffectiveBoxExtentZ * 2;
	const float BoardDeep = EffectiveBoxExtentX * 2 * Deep;
	const float BoardWidth = EffectiveBoxExtentY * 2 * Width;
	const float BoardHeight = EffectiveBoxExtentZ * 2 * Height;

	const FVector Origin = GetActorLocation();
	const FVector TopLeft(Origin.X - BoardDeep / 2 + EffectiveBoxExtentX, Origin.Y - BoardWidth / 2 + EffectiveBoxExtentY, Origin.Z + BoardHeight / 2 - EffectiveBoxExtentZ);

	for (int i = 0; i < Height; i++) {

		std::vector<std::vector<ACellActor*>> v2d;

		for (int j = 0; j < Width; j++) {

			std::vector<ACellActor*> v1d;

			for (int k = 0; k < Deep; k++) {

				const FVector Loc(Origin.X + k * XStep, TopLeft.Y + j * YStep, TopLeft.Z - i * ZStep);
				ACellActor* SpawnedActorRef = GetWorld()->SpawnActor<ACellActor>(CellActor, Loc, GetActorRotation()); //const pointer to non-const CellActor
				SpawnedActorRef->SetXYZ(i, j, k);
				v1d.push_back(SpawnedActorRef);
			}
			v2d.push_back(v1d);
		}
		CellActors3D.push_back(v2d);
	}

}

int32 AGridActor3D::CountAliveNeighbors(const int32 i, const int32 j, const int32 k) {
	int32 NumAliveNeighbors = 0;
	for (int x = -1; x <= 1; x++) {
		for (int y = -1; y <= 1; y++) {
			for (int z = -1; z <= 1; z++) {
				if (!(x == 0 && y == 0 && z == 0)) {
					const int32 effective_i = i + x;
					const int32 effective_j = j + y;
					const int32 effective_k = k + z;
					if ((effective_i >= 0 && effective_i < Height) && (effective_j >= 0 && effective_j < Width) && (effective_k >= 0 && effective_k < Deep)) {
						if (CellActors3D[effective_i][effective_j][effective_k]->GetAlive()) {
							NumAliveNeighbors++;
						}
					}
				}
			}
		}
	}
	return NumAliveNeighbors;
}

//TODO wszystko to do vr i dodaj tam player controler do test�w
//TODO change rules http://cs.brown.edu/courses/cs195v/projects/life/edwallac/index.html
//TODO change visibility
void AGridActor3D::UpdateAliveNext(const int32 i, const int32 j, const int32 k, const int32 NumAliveNeighbors) {
	const bool IsAlive = CellActors3D[i][j][k]->GetAlive();
	if (IsAlive && (NumAliveNeighbors < 2))
	{
		CellActors3D[i][j][k]->SetAliveNext(false);
	}
	else if (IsAlive && ((NumAliveNeighbors == 2) || (NumAliveNeighbors == 3)))
	{
		CellActors3D[i][j][k]->SetAliveNext(true);
	}
	else if (IsAlive && (NumAliveNeighbors > 3))
	{
		CellActors3D[i][j][k]->SetAliveNext(false);
	}
	else if (!IsAlive && (NumAliveNeighbors == 3))
	{
		CellActors3D[i][j][k]->SetAliveNext(true);
	}
	else {
		CellActors3D[i][j][k]->SetAliveNext(CellActors3D[i][j][k]->GetAlive());
	}
}

void AGridActor3D::GenerateNext() {
	for (int i = 0; i < Height; i++) {
		for (int j = 0; j < Width; j++) {
			for (int k = 0; k < Deep; k++) {
				const int NumAliveNeighbors = CountAliveNeighbors(i, j, k);
				UpdateAliveNext(i, j, k, NumAliveNeighbors);
			}
		}
	}
}

void AGridActor3D::UpdateNext() {
	for (int i = 0; i < Height; i++) {
		for (int j = 0; j < Width; j++) {
			for (int k = 0; k < Deep; k++) {
				CellActors3D[i][j][k]->Update();
			}
		}
	}
}

void AGridActor3D::ToEditMode() {
	for (int i = 0; i < Height; i++) {
		for (int j = 0; j < Width; j++) {
			for (int k = 0; k < Deep; k++) {
				CellActors3D[i][j][k]->SetActorHiddenInGame(false);
			}
		}
	}
}

void AGridActor3D::ToPlayMode() {
	for (int i = 0; i < Height; i++) {
		for (int j = 0; j < Width; j++) {
			for (int k = 0; k < Deep; k++) {
				//const bool IsAlive = CellActors3D[i][j][k]->GetAlive();
				//if (IsAlive) {
				//	CellActors3D[i][j][k]->SetActorHiddenInGame(false);
				//}
				//else {
				//	CellActors3D[i][j][k]->SetActorHiddenInGame(true);
				//}
			}
		}
	}
}


void AGridActor3D::Reset() {
	for (int i = 0; i < Height; i++) {
		for (int j = 0; j < Width; j++) {
			for (int k = 0; k < Deep; k++) {
				CellActors3D[i][j][k]->Reset();
				ClearTimer();
			}
		}
	}
}

void AGridActor3D::RandomGrid()
{
	Reset();

	for (int i = 0; i < Height; i++) {
		for (int j = 0; j < Width; j++) {
			for (int k = 0; k < Deep; k++) {
				if (FMath::RandRange(0.0f, 1.0f) < 0.2f)
				{
					CellActors3D[i][j][k]->SetAlive(true);
					CellActors3D[i][j][k]->Random();
				}
			}
		}
	}
}


