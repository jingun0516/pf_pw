#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"

#include "BaseTool.h"
#include "ToolsEnum.h"

#include "ToolsDataAsset.generated.h"

enum class EToolType;
class ABaseTool;
class USoundCue;

UCLASS(BlueprintType)
class PF_PW_API UToolsDataAsset : public UDataAsset
{
	GENERATED_BODY()
	

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Required)
	TSubclassOf<ABaseTool> ToolClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Required)
	FName ToolName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Required)
	FName HandleSocketName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Required)
	EToolType ToolType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Property)
	float Damage = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Property)
	float DamageToTree = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Property)
	float DamageToRock = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Property)
	float Weight = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Property)
	float Durability = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Property)
	float MaxDurability = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Property)
	UTexture2D* texture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Property)
	USoundCue* SoundCue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Property)
	float CraftTime = 5.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Property)
	TArray<TSubclassOf<ABaseItem>> RequiredItems;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Property)
	TArray <int> RequiredCounts;
};
