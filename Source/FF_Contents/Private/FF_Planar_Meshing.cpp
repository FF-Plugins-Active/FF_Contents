// Fill out your copyright notice in the Description page of Project Settings.

#include "FF_Planar_Meshing.h"

// Sets default values.
APlanar_Meshing::APlanar_Meshing()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned.
void APlanar_Meshing::BeginPlay()
{
	Super::BeginPlay();
}

// Called when the game ends or when destroyed.
void APlanar_Meshing::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

// Called every frame.
void APlanar_Meshing::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool APlanar_Meshing::IsPointInsideSpline(USplineComponent* BoundarySpline, const FVector& Point) const
{
	// Find the closest point on the spline to the current grid point.
	FVector ClosestSplinePoint = BoundarySpline->FindLocationClosestToWorldLocation(Point, ESplineCoordinateSpace::World);

	// Calculate the distance from the point to the closest spline point.
	float Distance = FVector::Dist(Point, ClosestSplinePoint);

	// Use the cross product and distance to determine if the point is inside or outside the spline.
	FVector DirectionToSpline = (ClosestSplinePoint - Point).GetSafeNormal();
	FVector SplineTangent = BoundarySpline->FindDirectionClosestToWorldLocation(Point, ESplineCoordinateSpace::World);
	FVector CrossProduct = FVector::CrossProduct(FVector(0, 0, 1), SplineTangent);

	// Use the dot product to determine whether the point is inside or outside.
	float DotProduct = FVector::DotProduct(DirectionToSpline, CrossProduct);

	// If the dot product is negative, the point is inside the spline.
	return DotProduct < 0;
}

bool APlanar_Meshing::Grid_Generate(TArray<FTransform>& Out_Vertices, USplineComponent* BoundarySpline, FVector Size, double GridSize, int32 Layer, double Height)
{
	if (!IsValid(BoundarySpline))
	{
		UE_LOG(LogTemp, Warning, TEXT("APlanar_Meshing::Grid_Generate -> Boundry spline is not valid."));
		return false;
	}

	if (GridSize <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("APlanar_Meshing::Grid_Generate -> Grid size have to be bigger than 0."));
		return false;
	}

	if (Layer <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("APlanar_Meshing::Grid_Generate -> Layer size have to be bigger than 0."));
		return false;
	}

	if (Height <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("APlanar_Meshing::Grid_Generate -> Height have to be bigger than 0."));
		return false;
	}

	// Get the bounding box of the spline.
	FBox SplineBounds = BoundarySpline->Bounds.GetBox();
	FVector Origin = SplineBounds.GetCenter();
	FVector Extent = SplineBounds.GetExtent();

	// Calculate the number of points to generate along each axis.
	const int32 NumPointsX = FMath::CeilToInt(Extent.X * 2 / GridSize);
	const int32 NumPointsY = FMath::CeilToInt(Extent.Y * 2 / GridSize);

	TArray<FTransform> Temp_Vertices;

	for (int32 i = -NumPointsX / 2; i <= NumPointsX / 2; i++)
	{
		for (int32 j = -NumPointsY / 2; j <= NumPointsY / 2; j++)
		{
			// Calculate the position of the current grid point.
			FVector FloorLocation = Origin + FVector(i * GridSize, j * GridSize, 0);

			if (IsPointInsideSpline(BoundarySpline, FloorLocation))
			{
				for (int32 Index_Layer = 0; Index_Layer < Layer; Index_Layer++)
				{
					FVector EachLocation = FloorLocation;
					EachLocation.Z = Index_Layer * Height + FloorLocation.Z;

					FTransform EachTransform;
					EachTransform.SetLocation(EachLocation);
					EachTransform.SetScale3D(Size);

					Temp_Vertices.Add(EachTransform);
				}
			}
		}
	}

	Out_Vertices = Temp_Vertices;
	return true;
}

void APlanar_Meshing::Grid_Debug(FVector Point, bool bInside, bool bIsPersistant, double Time)
{
	FColor Color = bInside ? FColor::Green : FColor::Red;
	float PointSize = 10.0f;

	DrawDebugPoint(GetWorld(), Point, PointSize, Color, bIsPersistant, Time);
}