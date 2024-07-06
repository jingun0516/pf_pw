#pragma once

#include "CoreMinimal.h"
#include "Widgets/Building/BaseBuildingWidget.h"
#include <Components/Image.h>
#include "WorkTimeWidget.generated.h"

class UTextBlock;
/**
 * 
 */
UCLASS()
class PF_PW_API UWorkTimeWidget : public UBaseBuildingWidget
{
	GENERATED_BODY()

public:
	void SetLeftWorkTime(float leftworktime);

protected:
	virtual void NativeOnInitialized() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UTextBlock* LeftWorkTime;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UImage* Image;
};
