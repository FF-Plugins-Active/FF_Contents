// Copyright Epic Games, Inc. All Rights Reserved.

#include "FF_ContentsBPLibrary.h"
#include "FF_Contents.h"

#include "Kismet/KismetMathLibrary.h"

UFF_ContentsBPLibrary::UFF_ContentsBPLibrary(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}

void UFF_ContentsBPLibrary::Int32ToGraphics(EChartType GraphicsType, int32 TargetInteger, int32 FullInteger, double& Scale, double& UnitValue)
{
    int32 FullScale = 0;

    switch (GraphicsType)
    {
        case EChartType::ChartPie:
            FullScale = 360;
            break;
        
        case EChartType::ChartBar:
            FullScale = 100;
            break;
    }

    Scale = (static_cast<double>(TargetInteger) * FullScale) / FullInteger;

    UnitValue = Scale / FullScale;
}