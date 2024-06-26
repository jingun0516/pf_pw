#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "MonsterStatusDataAsset.generated.h"

class UAnimMontage;

UCLASS(BlueprintType)
class PF_PW_API UMonsterStatusDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Property)
	FText Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Property)
	float MaxHP = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Property)
	float Damage = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Property)
	float Armor = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Property)
	int LV = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Property)
	int EXP = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Property)
	UTexture2D* texture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Property)
	float MaxSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Property)
	float WalkSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Montage)
	UAnimMontage* HitMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Montage)
	UAnimMontage* DeadMontage;
};
