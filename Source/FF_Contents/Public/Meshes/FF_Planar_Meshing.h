// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

// Custom Includes.
#include "FF_Contents_Includes.h"

#include "FF_Planar_Meshing.generated.h"

UCLASS()
class FF_CONTENTS_API APlanar_Meshing : public AActor
{
	GENERATED_BODY()
	
private:

	bool IsPointInsideSpline(USplineComponent* BoundarySpline, const FVector& Point) const;

protected:
	
	// Called when the game starts or when spawned.
	virtual void BeginPlay() override;

	// Called when the game ends or when destroyed.
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	
	// Sets default values for this actor's properties.
	APlanar_Meshing();

	// Called every frame.
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Frozen Forest|FF Contents|Planar Grid")
	bool Grid_Generate(TArray<FTransform>& Out_Vertices, USplineComponent* BoundarySpline, FVector Size = FVector(0.1), double GridSize = 100, int32 Layer = 1, double Height = 10);

	UFUNCTION(BlueprintCallable, Category = "Frozen Forest|FF Contents|Planar Grid")
	void Grid_Debug(FVector Point, bool bInside, bool bIsPersistant, double Time = 10);

};
