#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"

#include "BaseBuilding.h"

#include "DA_ToBuildDataAsset.generated.h"

class ABaseBuilding;
class ABaseItem;
/**
 * 
 */
UCLASS(BlueprintType)
class PF_PW_API UDA_ToBuildDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Required)
	TSubclassOf<ABaseBuilding> BuildingClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Required)
	FName BuildingName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Property)
	float MaxDurability = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Property)
	float GoalWorkTime = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Property)
	UTexture2D* texture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Property)
	TArray<TSubclassOf<ABaseItem>> RequiredItems;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Property)
	TArray <int> RequiredCounts;

};
