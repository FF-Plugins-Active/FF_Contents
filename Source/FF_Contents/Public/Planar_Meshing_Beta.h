// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

// Custom Includes.
#include "FF_Contents_Includes.h"

#include "Planar_Meshing_Beta.generated.h"

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

UCLASS()
class FF_CONTENTS_API APlanar_Meshing_Beta : public AActor
{
	GENERATED_BODY()
	
private:	

	template <typename T>
	static void SetArrayElement(TArray<T>& Array, T Item, int32 Index);

protected:

	// Called when the game starts or when spawned.
	virtual void BeginPlay() override;

	// Called when the game ends or when destroyed.
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:

	// Sets default values for this actor's properties.
	APlanar_Meshing_Beta();

	// Called every frame.
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Frozen Forest|FF Contents|Planar Grid", meta = (ToolTip = "Exprimental"))
	virtual FGridParameters Grid_Generate(USplineComponent* In_Spline, double Triangle_Size = 100);

	UFUNCTION(BlueprintCallable)
	virtual bool Generate_ISM(UInstancedStaticMeshComponent* In_ISMC, FGridParameters In_Params, FVector ObjectSize);

};
