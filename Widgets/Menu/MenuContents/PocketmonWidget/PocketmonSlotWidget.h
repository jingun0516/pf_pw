#pragma once

#include "CoreMinimal.h"
#include "Widgets/Menu/BasePartsMenuWidget.h"
#include <Components/Button.h>
#include <Components/EditableTextBox.h>
#include <Components/ProgressBar.h>
#include <Components/Image.h>
#include <Components/TextBlock.h>
#include "PocketmonSlotWidget.generated.h"

/**
 * 
 */
UCLASS()
class PF_PW_API UPocketmonSlotWidget : public UBasePartsMenuWidget
{
	GENERATED_BODY()
	
public:
	void SetMonsterLV(int LV);
	void SetMonsterName(FText name);
	void SetHPProgressBar(float percent);
	void SetHPText(float HP, float MaxHP);
	void SetHungerProgressBar(float percent);
	void SetMonsterImage(UTexture2D* image);

private:
	virtual void NativeOnInitialized() override;

	UPROPERTY(meta = (BindWidget))
	UButton* PocketmonSlotButton;

	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* MonsterLV;

	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* MonsterName;

	UPROPERTY(meta = (BindWidget))
	UProgressBar* HPProgressBar;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* HPText;

	UPROPERTY(meta = (BindWidget))
	UProgressBar* HungerProgressBar;

	UPROPERTY(meta = (BindWidget))
	UImage* MonsterImage;
};
