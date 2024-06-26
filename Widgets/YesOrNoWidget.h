#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Components/Button.h>

#include "YesOrNoWidget.generated.h"

class UBUtton;
class UUserWidget;
/**
 * 
 */
UCLASS()
class PF_PW_API UYesOrNoWidget : public UUserWidget
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

public:
	UFUNCTION()
	void NoButtonClicked();

	UFUNCTION()
	void YesButtonClicked();

	void SetNextWidget(UUserWidget* InNextWidget);
};
