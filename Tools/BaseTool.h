#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ToolsEnum.h"
#include "Items/BaseItem.h"
#include "BaseTool.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(ToolLog, Log, All);

class UBaseAction;
class UActionDataAsset;
class UToolsDataAsset;
class UCapsuleComponent;
class ABaseCharacter;
class AHero;

UCLASS()
class PF_PW_API ABaseTool : public ABaseItem
{
	GENERATED_BODY()
	
public:	
	ABaseTool();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	float GetDamage() { return Damage; }

	UFUNCTION()
	float GetDamageToTree() { return DamageToTree; }

	UFUNCTION()
	float GetDamageToRock() { return DamageToRock; }

public:
	FORCEINLINE FName GetSocketName() { return HandleSocketName; }

public:
	void SpawnActions();
	virtual void SetDatas();

protected:
	UPROPERTY()
	FName ToolName;

	UPROPERTY()
	FName HandleSocketName;

	UPROPERTY()
	EToolType ToolType;

	UPROPERTY()
	float Damage = 1.0f;

	UPROPERTY()
	float DamageToTree = 1.0f;

	UPROPERTY()
	float DamageToRock = 1.0f;

	UPROPERTY()
	float Durability = 1.f;

	UPROPERTY()
	float MaxDurability = 1.f;

	UPROPERTY()
	USoundCue* SoundCue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Property)
	UToolsDataAsset* Data;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Actions)
	UActionDataAsset* Actions;

	UPROPERTY()
	UBaseAction* MainAction;

	UPROPERTY()
	UBaseAction* SubAction;

	UPROPERTY()
	UBaseAction* ReloadAction;

	UPROPERTY()
	UBaseAction* ThrowAction;

	UPROPERTY()
	UBaseAction* SpawnAction;

	void InterAction();

protected:
	void NotifyActorBeginOverlap(AActor* OtherActor) override;
	void NotifyActorEndOverlap(AActor* OtherActor) override;
};
