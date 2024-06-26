#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PocketmonComponent.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(PokemonComp, Log, All);

class ABaseCharacter;
class ABaseMonster;
class AHero;
class UBaseAction;
class UThrowAction;
class UPocketmonSlotWidget;
enum class EPocketmonSlot;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PF_PW_API UPocketmonComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPocketmonComponent();

	UFUNCTION()
	FORCEINLINE ABaseMonster* GetCurPocketmon() { return Pocketmons.FindRef(CurrentSlot); }

	UFUNCTION()
	FORCEINLINE ABaseMonster* GetPocketmon(EPocketmonSlot slot) { return Pocketmons.FindRef(slot); }

	UFUNCTION()
	FORCEINLINE EPocketmonSlot GetCurrentSlot() { return CurrentSlot; }
	UFUNCTION()
	FORCEINLINE EPocketmonSlot GetPrevSlot() { return PrevSlot; }
	UFUNCTION()
	FORCEINLINE EPocketmonSlot GetNextSlot() { return NextSlot; }

	FORCEINLINE ABaseMonster* GetSpawnedMon() { return CurSpawnedMon; }
	ABaseMonster* CheckIsSpawned();

	UFUNCTION()
	EPocketmonSlot IsEmptySlot();

	void AddPocketmon(EPocketmonSlot Slot, ABaseMonster* pocketmon);
	FORCEINLINE void SetCurrentSlot(EPocketmonSlot Slot) { CurrentSlot = Slot; }

	float CalCatchPercent(ABaseMonster* pocketmon);

	UFUNCTION()
	void PocketmonNextSlot();

	UFUNCTION()
	void PocketmonPrevSlot();

	UFUNCTION()
	void SetNextPrevSlot();

protected:
	virtual void BeginPlay() override;
	
private:
	ABaseMonster* CurrentPocketmon;
	TMap<EPocketmonSlot, ABaseMonster*> Pocketmons;
	ABaseCharacter* OwnerCharacter;
	AHero* OwnerHero;
	EPocketmonSlot CurrentSlot;
	EPocketmonSlot PrevSlot;
	EPocketmonSlot NextSlot;
	ABaseMonster* CurSpawnedMon;

	TSubclassOf<UPocketmonSlotWidget> PokcetmonSlotWidgetClass;
};
