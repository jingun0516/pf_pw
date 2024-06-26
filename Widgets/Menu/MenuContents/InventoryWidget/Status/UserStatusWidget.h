// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/Menu/BasePartsMenuWidget.h"
#include <Components/TextBlock.h>
#include <Components/Button.h>
#include "Components/ProgressBar.h"
#include <Components/EditableTextBox.h>
#include "UserStatusWidget.generated.h"

/**
 * 
 */
UCLASS()
class PF_PW_API UUserStatusWidget : public UBasePartsMenuWidget
{
	GENERATED_BODY()
	
public:
	void SetPlayerLevelText(int lv);
	void SetExpToNextLevelText(int exp);

	void SetEXPProgressBar(float percent);

	void SetStatusPointText(int point);

	void SetHPPointText(int point);
	void SetStaminaPointText(int point);
	void SetAttackPointText(int point);
	void SetDefPointText(int point);
	void SetWorkTimePointText(int point);
	void SetWeightPointText(int point);

	UFUNCTION()
	void OnStatusButtonClicked();

	UFUNCTION()
	void OnHPButtonClicked();
	UFUNCTION()
	void OnStaminaButtonClicked();
	UFUNCTION()
	void OnAttackButtonClicked();
	UFUNCTION()
	void OnDefButtonClicked();
	UFUNCTION()
	void OnWorkTimeButtonClicked();
	UFUNCTION()
	void OnWeightButtonClicked();

	void SubStatusPoint();

private:
	virtual void NativeOnInitialized() override;

	bool bButtonsVisible = false;

	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* PlayerLevelText;

	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* ExpToNextLevelText;

	UPROPERTY(meta = (BindWidget))
	UProgressBar* EXPProgressBar;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* StatusPointText;
	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* HPText;
	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* StaminaText;
	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* AttackText;
	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* DefText;
	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* WorkTimeText;
	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* WeightText;

	UPROPERTY(meta = (BindWidget))
	UButton* HPButton;
	UPROPERTY(meta = (BindWidget))
	UButton* StaminaButton;
	UPROPERTY(meta = (BindWidget))
	UButton* AttackButton;
	UPROPERTY(meta = (BindWidget))
	UButton* DefButton;
	UPROPERTY(meta = (BindWidget))
	UButton* WorkTimeButton;
	UPROPERTY(meta = (BindWidget))
	UButton* WeightButton;

	TArray<UButton*> ButtonArray;

	UPROPERTY(meta = (BindWidget))
	UButton* StatusButton;
};
