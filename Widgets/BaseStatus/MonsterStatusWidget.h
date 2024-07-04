// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Components/ProgressBar.h>
#include <Components/TextBlock.h>
#include "MonsterStatusWidget.generated.h"

class UTextBlock;
class UProgressBar;
class ABaseCharacter;
class UStatusComponent;
/**
 * 
 */
UCLASS()
class PF_PW_API UMonsterStatusWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* MonsterName;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* MonsterName_1;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* MonsterName_2;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* TeamMonster;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* TeamMonster_1;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* TeamMonster_2;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* CurHP;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* MaxHP;
	UPROPERTY(meta = (BindWidget))
	UProgressBar* MonsterHPBar;

	void SetMonsterName(FText InName);
	void SetHP(ABaseCharacter* InMonster);
	void SetTeamMonsterName();
};
