#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseBuilding.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnBuildingWorkState);

DECLARE_LOG_CATEGORY_EXTERN(BuildingLog, Log, All);

class AHero;
class ABaseItem;
class ABaseCharacter;
class UBoxComponent;
class UBaseBuildingWidget;
class UBuildingClickedWidget;
class AWorkTimeActor;
class UYesNoWidget;
class UDA_ToBuildDataAsset;
enum class EBuildingState;
enum class EWorkerSlot;

enum class EBuildingColor
{
	E_Normal,
	E_Red,
	E_Blue,
	E_Green
};


UCLASS()
class PF_PW_API ABaseBuilding : public APawn
{
	GENERATED_BODY()
	
public:	
	ABaseBuilding();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(Visibleanywhere, BlueprintReadWrite)
	UStaticMeshComponent* mesh = nullptr;

	UPROPERTY(Visibleanywhere, BlueprintReadWrite)
	UBoxComponent* col = nullptr;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void InterAction();
	void SetMovable();
	void SetBuildingColor(EBuildingColor color);
	void SetDatas();

	void SetBuildingState(EBuildingState state);
	FVector GetScaledCol();
	FORCEINLINE EBuildingState GetBuildingState() { return BuildingState; }
	virtual void JobsDone();
	void BuildDone();
	void AddWorkers(ABaseCharacter* worker);
	int GetWorkersNum();

	UFUNCTION()
	virtual void StartWork();

	FORCEINLINE void SetGoalWorkTime(float InGoalWorkTime) { GoalWorkTime = InGoalWorkTime; }
	FORCEINLINE float GetGoalWorkTime() { return GoalWorkTime; }
	EWorkerSlot GetEmptyWorkerSlot();

	FOnBuildingWorkState DOnBuildingWorkState;

	FORCEINLINE UYesNoWidget* GetYesNoWidget() { return YesNoWidget; }

	UPROPERTY(Visibleanywhere)
	UUserWidget* BaseInteractionWidget;

	FORCEINLINE void SetWorkTimeActor(AWorkTimeActor* InActor) { WorkTimeActor = InActor; }
	AWorkTimeActor* GetWorkTimeActor() { return WorkTimeActor; }
	UTexture2D* GetTexture() { return texture; }

	float GetCurrentWorkTime() { return CurrentWorkTime; }
	FORCEINLINE UBuildingClickedWidget* GetBuildingClickedWidget() { return BuildingClickedWidget; }

	FORCEINLINE TArray<TSubclassOf<ABaseItem>> GetRequiredItems() { return RequiredItems; };
	FORCEINLINE TArray<int> GetRequiredCounts() { return RequiredCounts; }

protected:
	float Durability;
	float MaxDurability;
	float CurrentWorkTime = 0.f;
	float GoalWorkTime = 10.f;
	UTexture2D* texture;
	UPROPERTY()
	TArray<TSubclassOf<ABaseItem>> RequiredItems;
	UPROPERTY()
	TArray<int> RequiredCounts;

	AWorkTimeActor* WorkTimeActor;
	ABaseCharacter* OwnerCharacter;
	AHero* OwnerHero;

	UMaterialInterface* blueMaterial;
	UMaterialInterface* redMaterial;
	UMaterialInterface* greenMaterial;
	TArray<UMaterialInterface*> MArray;

	EBuildingState BuildingState;

	TMap<EWorkerSlot, ABaseCharacter*> Workers;

	TSubclassOf<UUserWidget> WidgetClass;

	TSubclassOf<UBaseBuildingWidget> InteractioningWidgetClass;
	UPROPERTY(Visibleanywhere)
	UBaseBuildingWidget* InteractioningWidget;

	TSubclassOf<UYesNoWidget> YesNoWidgetClass;
	UPROPERTY(Visibleanywhere)
	UYesNoWidget* YesNoWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Property)
	UDA_ToBuildDataAsset* BuildData;

	UBuildingClickedWidget* BuildingClickedWidget;
	TSubclassOf<UBuildingClickedWidget> BuildingClickedWidgetClass;
};
