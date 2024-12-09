#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EChartType : uint8
{
	ChartPie	UMETA(DisplayName = "Pie Chart"),
	ChartBar	UMETA(DisplayName = "Bar Chart"),
};
ENUM_CLASS_FLAGS(EChartType)