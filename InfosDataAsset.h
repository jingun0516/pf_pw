#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "InfosDataAsset.generated.h"

class UDA_ToBuildDataAsset;
class UToolsDataAsset;
class UMonsterStatusDataAsset;
class ABaseResource;
/**
 * 
 */
UCLASS(BlueprintType)
class PF_PW_API UInfosDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	TArray<UDA_ToBuildDataAsset*> GetBuildingArray() { return BuildingArray; }
	TArray<UToolsDataAsset*> GetToolArray() { return ToolArray; }
	TArray<UMonsterStatusDataAsset*> GetMonsterArray() { return MonsterArray; }
	TArray<TSubclassOf<ABaseResource>> GetResourceArray() { return ResourceArray; }

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Building")
	TArray<UDA_ToBuildDataAsset*> BuildingArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tool")
	TArray<UToolsDataAsset*> ToolArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Monster")
	TArray<UMonsterStatusDataAsset*> MonsterArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resource")
	TArray<TSubclassOf<ABaseResource>> ResourceArray;
};
