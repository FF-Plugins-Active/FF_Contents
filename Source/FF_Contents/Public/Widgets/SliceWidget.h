// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

// UE Includes.
#include "Components/Widget.h"
#include "Widgets/SCompoundWidget.h"

#include "SliceWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FDelegateSlice, const FGeometry&, MyGeometry, const FPointerEvent&, MouseEvent);

class FF_CONTENTS_API SSlateSlice : public SCompoundWidget
{

protected:

	FSlateBrush* Brush;
	double Angle = 0;
	double ArcSize = 0;
	double Smoothness = 0.5;
	void* ParentBuffer = nullptr;

	virtual FReply CallbackCursorHit(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent, FDelegateSlice Delegate);

public:

	SLATE_BEGIN_ARGS(SSlateSlice)
		{}
		SLATE_ARGUMENT(FSlateBrush*, Brush)
		SLATE_ARGUMENT(double, Angle)
		SLATE_ARGUMENT(double, ArcSize)
		SLATE_ARGUMENT(double, Smoothness)
	SLATE_END_ARGS()

	TSharedPtr<FHittestGrid> HittestGrid;

	void Construct(const FArguments& InArgs);
	virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;
	virtual FReply OnMouseMove(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
	virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;

	void SetBrush(FSlateBrush* InBrush);
	void SetAngle(double InAngle);
	void SetArcSize(double InArcSize);
	void SetSmoothness(double InSmoothness);
	void SetParent(void* InBuffer);
};

UCLASS()
class FF_CONTENTS_API USliceWidget : public UWidget
{
	GENERATED_BODY()

protected:

	virtual TSharedRef<SWidget> RebuildWidget() override;
	TSharedPtr<SSlateSlice> MySlice;

public:

	virtual void SynchronizeProperties() override;
	virtual void ReleaseSlateResources(bool bReleaseChildren) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance")
	FSlateBrush Brush;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Appearance", meta = (ClampMin = "0", ClampMax = "360"))
	double Angle = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Appearance", meta = (ClampMin = "0", ClampMax = "360"))
	double ArcSize = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Appearance", meta = (ClampMin = "0.5", ClampMax = "10"))
	double Smoothness = 0.5;

	UPROPERTY(BlueprintAssignable)
	FDelegateSlice Delegate_Mouse_Move;

	UPROPERTY(BlueprintAssignable)
	FDelegateSlice Delegate_Mouse_Down;

	UFUNCTION(BlueprintCallable, Category = "Appearance")
	void SetAngle(double InAngle);

	UFUNCTION(BlueprintCallable, Category = "Appearance")
	void SetArcSize(double InArcSize);

	UFUNCTION(BlueprintCallable, Category = "Appearance")
	void SetSmoothness(double InSmoothness);

	UFUNCTION(BlueprintCallable, Category = "Appearance")
	void SetParent();

	UFUNCTION(BlueprintCallable, Category = "FF_Contents|Slice Widget")
	virtual bool IsMouseOnPie(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent);

#if WITH_EDITOR
	virtual const FText GetPaletteCategory() override;
#endif
	
};