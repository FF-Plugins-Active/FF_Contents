// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/UMG.h"

#include "Components/TextBlock.h"

#include "UMG_Sample.generated.h"

UCLASS()
class FF_CONTENTS_API USampleWidgetCpp : public UUserWidget
{
	GENERATED_BODY()
	
public:	

	virtual void NativeConstruct() override;

	// You need to open "Show Inherited Variables" to show it in "Variables" section.
	
	// "BindWidgetOptional" means, you don't have to add this widget in UMG blueprints.
	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetOptional))
	UTextBlock* Text_Optional = nullptr;

	// "BindWidget" means, you have to add this widget in UMG blueprints.
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* Text_Must = nullptr;
};
