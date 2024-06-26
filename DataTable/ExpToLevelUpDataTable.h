#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ExpToLevelUpDataTable.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FLevelUpTableRow : public FTableRowBase 
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LevelUp")
	int32 ExpToNextLevel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LevelUp")
	int32 TotalExp;
};

UCLASS()
class PF_PW_API UExpToLevelUpDataTable : public UDataTable
{
	GENERATED_BODY()
};
