// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

DECLARE_MULTICAST_DELEGATE(FDoMainAction);
DECLARE_MULTICAST_DELEGATE(FEndMainAction);
DECLARE_MULTICAST_DELEGATE(FDoSubAction);
DECLARE_MULTICAST_DELEGATE(FEndSubAction);

DECLARE_LOG_CATEGORY_EXTERN(CharacterLog, Log, All);

class UToolComponent;
class UStatusComponent;
class UStateComponent;
class UBuildingComponent;
class UPocketmonComponent;
class UInventoryComponent;
class ABaseTool;
class UUserWidget;

UCLASS()
class PF_PW_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UToolComponent* ToolComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UStatusComponent* StatusComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UStateComponent* StateComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UBuildingComponent* BuildingComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UPocketmonComponent* PocketmonComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UInventoryComponent* InventoryComponent;

public:
	ABaseCharacter();

	FORCEINLINE UToolComponent* GetToolComponent() { return ToolComponent; }
	FORCEINLINE UStatusComponent* GetStatusComponent() { return StatusComponent; }
	FORCEINLINE UStateComponent* GetStateComponent() { return StateComponent; }
	FORCEINLINE UBuildingComponent* GetBuildingComponent() { return BuildingComponent; }
	FORCEINLINE UPocketmonComponent* GetPocketmonComponent() { return PocketmonComponent; }
	FORCEINLINE UInventoryComponent* GetInventoryComponent() { return InventoryComponent; }

	FORCEINLINE UAnimMontage* GetHitMontage() { return HitMontage; }
	FORCEINLINE UAnimMontage* GetDeadMontage() { return DeadMontage; }

	virtual float TakeDamage
	(
		float DamageAmount,
		struct FDamageEvent const& DamageEvent,
		class AController* EventInstigator,
		AActor* DamageCauser
	) override;

	int GetDirection() { return direction; }
	void OnApplyDamage(AActor* DamagedActor, AActor* DamagedCauser, float Damage);
	void SetInfos(ABaseTool* tool);
	

	TSubclassOf<UUserWidget> DamageWidgetClass;
	void CalDamageDirection(FVector ActorLocation, FVector DCLocation, FVector forwardVector);
protected:
	virtual void BeginPlay() override;
	ABaseCharacter* PlayerC;

protected:
	virtual void SetCharacterMovement();

	UAnimMontage* HitMontage;
	UAnimMontage* DeadMontage;
public:
	FDoMainAction DDoMainAction;
	FEndMainAction DEndMainAction;
	FDoSubAction DDoSubAction;
	FEndSubAction DEndSubAction;

	void DoMainAction();
	void EndMainAction();
	void DoSubAction();
	void EndSubAction();

	int direction;
};
