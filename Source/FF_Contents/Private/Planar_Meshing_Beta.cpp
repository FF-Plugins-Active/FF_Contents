// Fill out your copyright notice in the Description page of Project Settings.


#include "Planar_Meshing_Beta.h"

// Sets default values
APlanar_Meshing_Beta::APlanar_Meshing_Beta()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void APlanar_Meshing_Beta::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called when the game ends or when destroyed.
void APlanar_Meshing_Beta::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

// Called every frame
void APlanar_Meshing_Beta::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

template<typename T>
void APlanar_Meshing_Beta::SetArrayElement(TArray<T>& Array, T Item, int32 Index)
{
	if (Array.Num() - 1 < Index)
	{
		Array.SetNum(Index + 1);
	}

	Array.Insert(Item, Index);
}

FGridParameters APlanar_Meshing_Beta::Grid_Generate(USplineComponent* In_Spline, double Triangle_Size)
{
	if (!IsValid(In_Spline))
	{
		return FGridParameters();
	}

	TArray<FVector> Vertices;
	TArray<int32> Point_Indexes;

	const double Degree_60 = 60;
	bool bIsEdge = false;
	bool bIsInside = false;
	int32 CurrentPoint = 0;

	const FVector Origin = In_Spline->Bounds.Origin;
	const FVector Extent = In_Spline->Bounds.BoxExtent;
	const double Clampled_Size = UKismetMathLibrary::FClamp(Triangle_Size, (double)2, double(30));
	const double Divison = Clampled_Size / 2;
	const double Tangent = Divison * UKismetMathLibrary::Tan(Degree_60);

	const int32 Number_X = UKismetMathLibrary::FCeil((Extent.X / Clampled_Size) + 1);
	const int32 Number_Y = UKismetMathLibrary::FCeil((Extent.Y / Tangent) + 1);

	for (int32 Index_Y = -Number_Y; Index_Y < Number_Y; Index_Y++)
	{
		for (int32 Index_X = -Number_X; Index_X < Number_X; Index_X++)
		{
			const double Percent = UKismetMathLibrary::GenericPercent_FloatFloat(UKismetMathLibrary::Abs(Index_Y + Number_Y), 2);

			const double X_Axis = Origin.X + (Index_X * Clampled_Size) + (Percent * Divison);
			const double Y_Axis = Origin.Y + (Index_Y * Tangent);
			const double Z_Axis = Origin.Z;

			const FVector CurrentLocation = FVector(X_Axis, Y_Axis, Z_Axis);

			FVector Direction = In_Spline->FindDirectionClosestToWorldLocation(CurrentLocation, ESplineCoordinateSpace::World);
			FVector CrossProduct = UKismetMathLibrary::Cross_VectorVector(FVector(0, 0, 1), Direction);

			FVector CurrentEdgeLocation = In_Spline->FindLocationClosestToWorldLocation(CurrentLocation, ESplineCoordinateSpace::World);
			FVector LocationDifference = CurrentEdgeLocation - CurrentLocation;

			const double DotProduct = UKismetMathLibrary::Dot_VectorVector(LocationDifference, CrossProduct);
			bIsInside = DotProduct < 0 ? true : false;

			const double VectorLenght = UKismetMathLibrary::VSize(LocationDifference);
			bIsEdge = VectorLenght < Triangle_Size ? true : false;

			CurrentPoint++;

			if (bIsInside)
			{
				APlanar_Meshing_Beta::SetArrayElement<FVector>(Vertices, CurrentLocation, CurrentPoint);
				APlanar_Meshing_Beta::SetArrayElement<int32>(Point_Indexes, CurrentPoint, 0);
			}

			else if (bIsEdge)
			{
				APlanar_Meshing_Beta::SetArrayElement<FVector>(Vertices, CurrentEdgeLocation, CurrentPoint);
				APlanar_Meshing_Beta::SetArrayElement<int32>(Point_Indexes, CurrentPoint, 1);
			}

			else
			{
				APlanar_Meshing_Beta::SetArrayElement<FVector>(Vertices, CurrentLocation, CurrentPoint);
				APlanar_Meshing_Beta::SetArrayElement<int32>(Point_Indexes, CurrentPoint, -1);
			}
		}
	}

	FGridParameters Out_Params;
	Out_Params.Grid_X = Number_X * 2;
	Out_Params.Points = Point_Indexes;
	Out_Params.Vertices = Vertices;

	return Out_Params;
}

bool APlanar_Meshing_Beta::Generate_ISM(UInstancedStaticMeshComponent* In_ISMC, FGridParameters In_Params, FVector ObjectSize)
{
	if (!IsValid(In_ISMC))
	{
		return false;
	}

	if (In_Params.Points.IsEmpty() || In_Params.Vertices.IsEmpty())
	{
		return false;
	}

	TArray<FTransform> Array_Transforms;
	for (int32 Index_Object = 1; Index_Object < In_Params.Points.Num(); Index_Object++)
	{
		if (In_Params.Points[Index_Object] >= 0)
		{
			FTransform Transform;
			Transform.SetScale3D(ObjectSize);
			Transform.SetLocation(In_Params.Vertices[Index_Object]);
			Array_Transforms.Add(Transform);
			
			//In_ISMC->AddInstance(Transform, true);
		}
	}

	In_ISMC->AddInstances(Array_Transforms, false, true);

	return true;
}