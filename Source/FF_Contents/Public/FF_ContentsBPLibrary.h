// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"

// Custom Includes
#include "FF_Contents_Enums.h"
#include "Widgets/SliceWidget.h"

#include "FF_ContentsBPLibrary.generated.h"

UCLASS()
class UFF_ContentsBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Int32 To Graphics", ToolTip = "Unit Value gives scale as a float between 0 and 1.", Keywords = "int32, graphics, pie"), Category = "FF_Contents|Charts")
	static FF_CONTENTS_API void Int32ToGraphics(EChartType GraphicsType, int32 TargetInteger, int32 FullInteger, double& Scale, double& UnitValue);

};