// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "InputDataAsset.generated.h"

class UInputAction;
/**
 *
 */
UCLASS()
class PF_PW_API UInputDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Motion, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Motion, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Motion, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	/*=============================================================================================*/

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Action, meta = (AllowPrivateAccess = "true"))
	UInputAction* MainAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Action, meta = (AllowPrivateAccess = "true"))
	UInputAction* SubAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Action, meta = (AllowPrivateAccess = "true"))
	UInputAction* ReloadAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Action, meta = (AllowPrivateAccess = "true"))
	UInputAction* ThrowAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Action, meta = (AllowPrivateAccess = "true"))
	UInputAction* SpawnAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Action, meta = (AllowPrivateAccess = "true"))
	UInputAction* InterAction;

	/*=============================================================================================*/

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Select, meta = (AllowPrivateAccess = "true"))
	UInputAction* FirstSelect;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Select, meta = (AllowPrivateAccess = "true"))
	UInputAction* SecondSelect;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Select, meta = (AllowPrivateAccess = "true"))
	UInputAction* ThirdSelect;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Select, meta = (AllowPrivateAccess = "true"))
	UInputAction* ForthSelect;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Select, meta = (AllowPrivateAccess = "true"))
	UInputAction* PocketmonNextSlot;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Select, meta = (AllowPrivateAccess = "true"))
	UInputAction* PocketmonPrevSlot;
};
