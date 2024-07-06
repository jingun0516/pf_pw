#include "Components/InventoryComponent.h"
#include "Characters/Hero.h"
#include "Items/BaseItem.h"
#include "Widgets/Menu/MenuWidget.h"
#include "Widgets/Menu/MenuContents/InventoryWidget/InventoryWidget.h"
#include "Widgets/Menu/MenuContents/InventoryWidget/Inventory/InventorySlotsWidget.h"
#include "Widgets/Menu/MenuContents/InventoryWidget/Inventory/InventorySlotWidget.h"
#include "Widgets/Menu/MenuContents/InventoryWidget/Inventory/MainInventoryWidget.h"

UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	OwnerHero = Cast<AHero>(GetOwner());
}

void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	InventoryItems.Init(nullptr, 42);
}


void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UInventoryComponent::AddItems(ABaseItem* item)
{
	UE_LOG(LogTemp, Log, TEXT("additem!!"));
	if (item->GetCountable() == ECountableType::E_Countable)
	{
		bool bFound = CheckAddCountable(item);

		if(!bFound)		// 같은 Countable Item이 인벤토리에 없을 경우
		{
			int emptySlot = GetEmptySlot();
			
			if (emptySlot == -1) return;

			SetItem(emptySlot, item);
		}
	}
	else
	{
		int emptySlot = GetEmptySlot();
		if (emptySlot == -1) return;
		
		SetItem(emptySlot, item);
		
		UE_LOG(LogTemp, Log, TEXT("UnCountable"));
	}
}

ABaseItem* UInventoryComponent::GetItem(int index)
{
	if (InventoryItems.IsValidIndex(index))
		return InventoryItems[index];

	return nullptr;
}

void UInventoryComponent::SetItem(int index, ABaseItem* inItem)
{
	if (!inItem) return;
	UE_LOG(LogTemp, Log, TEXT("SetItem Execute : %s"), *inItem->GetName());
	InventoryItems[index] = inItem;
	inItem->SetActorHiddenInGame(true);
	inItem->SetActorEnableCollision(false);
	TMap<int, UInventorySlotWidget*> slots = OwnerHero->GetMenuWidget()->GetInventoryWidget()->GetMainInventoryWidget()->GetInventorySlotsWidget()->GetInventorySlot();

	
	if (!slots[index] || !inItem->texture) return;

	slots[index]->BrushInvenImage(inItem->texture);
	if (inItem->GetCountable() == ECountableType::E_Countable)
	{
		slots[index]->SetInvenText(inItem->GetCounts());
		slots[index]->SetInvenTextVisibility(true);
	}
	else
	{
		slots[index]->SetInvenTextVisibility(false);
	}
}

int UInventoryComponent::GetEmptySlot()
{
	for (int index = 0; index < InvenSize; index++)
	{
		if (InventoryItems[index] == nullptr)
		{
			return index;
		}
	}
	return -1;
}

bool UInventoryComponent::CheckAddCountable(ABaseItem* item)
{
	for (int i = 0; i < InvenSize; i++)
	{
		if (InventoryItems[i] != nullptr && InventoryItems[i]->GetClass() == item->GetClass())
		{
			ABaseItem* findItem = InventoryItems[i];
			int count = findItem->GetCounts() + item->GetCounts();
			UE_LOG(LogTemp, Log, TEXT("findItem->Count: %d // item->Count: %d // count: %d"), findItem->GetCounts(), item->GetCounts(), count);
			item->SetCounts(count);
			SetItem(i, item);

			UE_LOG(LogTemp, Log, TEXT("Countable Yes Find"));
			return true;
		}
	}
	return false;
}

void UInventoryComponent::SetNullItem(int index)
{
	InventoryItems[index] = nullptr;
	TMap<int, UInventorySlotWidget*> slots = OwnerHero->GetMenuWidget()->GetInventoryWidget()->GetMainInventoryWidget()->GetInventorySlotsWidget()->GetInventorySlot();

	if (slots[index])
	{
		slots[index]->BrushInvenImage(nullptr);
		slots[index]->SetInvenTextVisibility(false);
	}

}

void UInventoryComponent::SubItems(TSubclassOf<ABaseItem> itemClass, int counts)
{
	ABaseItem* item = GetWorld()->SpawnActor<ABaseItem>(itemClass);
	
	if (item->GetCountable() == ECountableType::E_Countable)
	{
		for (int i = 0; i < InvenSize; i++)
		{
			if (InventoryItems[i] == nullptr) continue;

			if (InventoryItems[i]->GetClass() != item->GetClass()) continue;
			
			ABaseItem* findItem = InventoryItems[i];
				
			findItem->SetCounts(findItem->GetCounts() - counts);
				
			if (!(OwnerHero->GetMenuWidget())) return;
				
			TMap<int, UInventorySlotWidget*> slots = OwnerHero->GetMenuWidget()->GetInventoryWidget()->GetMainInventoryWidget()->GetInventorySlotsWidget()->GetInventorySlot();
			if (!slots[i]) return;
					
			if (findItem->GetCounts() > 0)
			{
				SetItem(i, findItem);
				return;
			}
			else
			{
				SetNullItem(i);
				return;
			}
			
		}
	}
	else
	{
		for (int i = 0; i < InvenSize; i++)
		{
			if (InventoryItems[i] == nullptr) continue;

			if (InventoryItems[i]->GetClass() == item->GetClass())
			{
				ABaseItem* findItem = InventoryItems[i];
				
				if (!(OwnerHero->GetMenuWidget())) return;
				
				TMap<int, UInventorySlotWidget*> slots = OwnerHero->GetMenuWidget()->GetInventoryWidget()->GetMainInventoryWidget()->GetInventorySlotsWidget()->GetInventorySlot();
				if (!slots[i]) return;
				
				SetNullItem(i);
				return;
			}
		}

		UE_LOG(LogTemp, Log, TEXT("UnCountable"));
	}
	
}

int UInventoryComponent::GetNumsOfItem(TSubclassOf<ABaseItem> item)
{
	int count = 0;

	for (int i = 0; i < InvenSize; i++)
	{
		if (InventoryItems[i])
		{
			TSubclassOf<ABaseItem> itemClass = InventoryItems[i]->GetClass();
			if (itemClass == item)
			{
				count += InventoryItems[i]->GetCounts();
			}
		}
	}

	return count;
}

