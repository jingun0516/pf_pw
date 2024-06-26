#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ToolComponent.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(ToolComp, Log, All);

class UBaseAction;
class ABaseTool;
class UToolDataAsset;
class ABaseCharacter;
class AHero;
class UBaseAction;
class ABaseKick;
enum class EToolSlot;
enum class EToolType;
enum class EWeaponType;

DECLARE_MULTICAST_DELEGATE(FOnToolSlotChanged);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PF_PW_API UToolComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UToolComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void EquipTool(EToolSlot slot);
	void AttachTool();
	void DetachTool();

	void AddTool(EToolSlot Slot, ABaseTool* Tool);
	void UnEquipTool(EToolSlot Slot);
	FORCEINLINE void SetCurrentSlot(EToolSlot Slot) { CurrentSlot = Slot; }
	FORCEINLINE EToolSlot GetCurrentSlot() { return CurrentSlot; }

	FORCEINLINE ABaseTool* GetTool(EToolSlot slot) { return Tools.FindRef(slot); }
	FORCEINLINE ABaseTool* GetCurTool() { return Tools.FindRef(CurrentSlot); }

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TMap<EToolSlot, ABaseTool*> Tools;		// 슬롯마다 도구 저장
	void InitToolSlot(EToolSlot slot);
	
	ABaseCharacter* OwnerCharacter;
	AHero* OwnerHero;
	EToolSlot CurrentSlot;							// 현재 슬롯
	UBaseAction* CurrentAction;

	bool bAttack = false;
	TSubclassOf<ABaseKick> KickClass;
	ABaseKick* tempKick;

	void ToolInteraction(ABaseTool* tool);
public:
	UFUNCTION()
	void DoMainAction();

	UFUNCTION()
	void EndMainAction();

	UFUNCTION()
	void DoSubAction();

	UFUNCTION()
	void EndSubAction();

	UFUNCTION()
	void DoAvoidAction();

	UFUNCTION()
	void EndAvoidAction();

	UFUNCTION()
	void DoReloadAction();

	UFUNCTION()
	void DoSpawnAction();

	UFUNCTION()
	void DoThrowAction();

	UFUNCTION()
	void DoFirstSelect();

	UFUNCTION()
	void DoSecondSelect();

	UFUNCTION()
	void DoThirdSelect();

	UFUNCTION()
	void DoForthSelect();

public:
	FOnToolSlotChanged DOnToolSlotChanged;
	
	UFUNCTION()
	void OnToolSlotChanged();

	UFUNCTION()
	EToolSlot IsEmptySlot();

	bool CheckEmptySlot(EToolSlot slot);
};
