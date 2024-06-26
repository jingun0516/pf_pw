// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ActionDataAsset.generated.h"

class UBaseAction;
/**
 * 
 */
UCLASS()
class PF_PW_API UActionDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Motion, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UBaseAction> MainAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Motion, meta = (AllowPrivateAccess = "true"))
	TArray<UAnimMontage*> MainMontages;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Motion, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UBaseAction> SubAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Motion, meta = (AllowPrivateAccess = "true"))
	TArray<UAnimMontage*> SubMontages;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Motion, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UBaseAction> ReloadAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Motion, meta = (AllowPrivateAccess = "true"))
	TArray<UAnimMontage*> ReloadMontages;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Motion, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UBaseAction> ThrowAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Motion, meta = (AllowPrivateAccess = "true"))
	TArray<UAnimMontage*> ThrowMontages;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Motion, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UBaseAction> SpawnAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Motion, meta = (AllowPrivateAccess = "true"))
	TArray<UAnimMontage*> SpawnMontages;
};
