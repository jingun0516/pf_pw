// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "YesNoWidget.generated.h"

class UButton;
class UUserWidget;
/**
 * 
 */

UENUM(BlueprintType)
enum class ENextDo
{
	E_None,
	E_Craft
};

UCLASS()
class PF_PW_API UYesNoWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeOnInitialized() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UButton* YesButton;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UButton* NoButton;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UUserWidget* NextWidget;

	ENextDo next;

public:
	UFUNCTION()
	void NoButtonClicked();

	UFUNCTION()
	void YesButtonClicked();

	void SetNextWidget(UUserWidget* InNextWidget);

	FORCEINLINE void SetNextDo(ENextDo nextFunc) { next = nextFunc; }
	FORCEINLINE ENextDo GetNextDo() { return next; }

	void DoCraft();
};
