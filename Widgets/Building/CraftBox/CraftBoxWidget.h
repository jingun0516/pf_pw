// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/Building/BaseBuildingWidget.h"
#include <Components/Button.h>
#include <Components/VerticalBox.h>
#include "CraftBoxWidget.generated.h"

class ABaseBuilding;
class AHero;
class UExitButtonWidget;
class UCraftBoxItemWidget;
/**
 * 
 */
UCLASS()
class PF_PW_API UCraftBoxWidget : public UBaseBuildingWidget
{
	GENERATED_BODY()

public:
	virtual void NativeOnInitialized() override;

	UFUNCTION(BlueprintCallable)
	virtual void ExitWidgetFunc() override;

	UFUNCTION(BlueprintCallable)
	void InitCraftBoxSlots();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UExitButtonWidget* ExitWidget;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UVerticalBox* VerticalBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TMap<int, UCraftBoxItemWidget*> CraftBoxSlot;
	
	int temp_index = 0;
};
