#pragma once

#include "CoreMinimal.h"
#include "Building/BaseBuilding.h"
#include "Building_CraftBox.generated.h"

class UCraftBoxClickedWidget;
class ABaseTool;

UCLASS()
class PF_PW_API ABuilding_CraftBox : public ABaseBuilding
{
	GENERATED_BODY()

public:
	ABuilding_CraftBox();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

public:
	FORCEINLINE void SetToolClass(TSubclassOf<ABaseTool> InToolClass) { ToolClass = InToolClass; }
	FORCEINLINE void SetToolImage(UTexture2D* image) { ToolImage = image; }
	FORCEINLINE TSubclassOf<ABaseTool> GetToolClass(){ return ToolClass; }
	virtual void JobsDone() override;

	virtual void StartWork() override;

	virtual void InterAction() override;

private:
	TSubclassOf<ABaseTool> ToolClass;
	UTexture2D* ToolImage;
	
};
