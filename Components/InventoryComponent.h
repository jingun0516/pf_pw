#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

class ABaseItem;
class AHero;
class UMainInventoryWidget;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PF_PW_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInventoryComponent();

protected:
	virtual void BeginPlay() override;

	TArray<ABaseItem*> InventoryItems;
	AHero* OwnerHero;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void AddItems(ABaseItem* item);
	void SubItems(TSubclassOf<ABaseItem> itemClass, int counts);
	int GetNumsOfItem(TSubclassOf<ABaseItem> item);
	ABaseItem* GetItem(int index);
	void SetItem(int index, ABaseItem* inItem);
	void SetNullItem(int index);
	int GetEmptySlot();
	bool CheckAddCountable(ABaseItem* item);
	
private:
	int InvenSize = 42;
		
};
