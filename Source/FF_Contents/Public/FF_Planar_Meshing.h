// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

// Custom Includes.
#include "FF_Contents_Includes.h"

#include "FF_Planar_Meshing.generated.h"

USTRUCT(BlueprintType)
struct FF_CONTENTS_API FGridParameters
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly)
	TArray<int32> Points;

	UPROPERTY(BlueprintReadOnly)
	TArray<FVector> Vertices;

	UPROPERTY(BlueprintReadOnly)
	int32 Grid_X = 0;
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_OneParam(FDelegateGrid, FGridParameters, Out_Params);

UCLASS()
class FF_CONTENTS_API APlanar_Meshing : public AActor
{
	GENERATED_BODY()
	
protected:
	
	// Called when the game starts or when spawned.
	virtual void BeginPlay() override;

	// Called when the game ends or when destroyed.
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	template <typename T> 
	static void SetArrayElement(TArray<T>& Array, T Item, int32 Index);

public:	
	
	// Sets default values for this actor's properties.
	APlanar_Meshing();

	// Called every frame.
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	virtual FGridParameters MakePointGrid(USplineComponent* In_Spline, double Triangle_Size = 100);

};
