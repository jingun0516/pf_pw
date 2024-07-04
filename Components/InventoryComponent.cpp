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
		bool bFound = false;
		for (int i = 0; i < 42; i++)
		{
			if (InventoryItems[i] != nullptr && InventoryItems[i]->GetClass() == item->GetClass())
			{
				ABaseItem* findItem = InventoryItems[i];
				int count = findItem->GetCounts() + item->GetCounts();
				UE_LOG(LogTemp, Log, TEXT("findItem->Count: %d // item->Count: %d // count: %d"), findItem->GetCounts(), item->GetCounts(), count);
				findItem->SetCounts(count);
				item->SetActorHiddenInGame(true);
				item->SetActorEnableCollision(false);
				if (!(OwnerHero->GetMenuWidget())) return;
				TMap<int, UInventorySlotWidget*> slots = OwnerHero->GetMenuWidget()->GetInventoryWidget()->GetMainInventoryWidget()->GetInventorySlotsWidget()->GetInventorySlot();
				if (!slots[i]) return;

				slots[i]->SetInvenText(findItem->GetCounts());
				slots[i]->InvenText->SetVisibility(ESlateVisibility::Visible);

				bFound = true;
				UE_LOG(LogTemp, Log, TEXT("Countable Yes Find"));
				break;
			}
		}

		if(!bFound)
		{
			if (GetEmptySlot() != -1)
			{
				int emptySlot = GetEmptySlot();
				InventoryItems[emptySlot] = item;
				item->SetActorHiddenInGame(true);
				item->SetActorEnableCollision(false);
				if (OwnerHero->GetMenuWidget())
				{
					TMap<int, UInventorySlotWidget*> slots = OwnerHero->GetMenuWidget()->GetInventoryWidget()->GetMainInventoryWidget()->GetInventorySlotsWidget()->GetInventorySlot();
					if (slots[emptySlot])
					{
						slots[emptySlot]->InvenImage->SetBrushFromTexture(item->texture);
						slots[emptySlot]->SetInvenText(item->GetCounts());
						slots[emptySlot]->InvenText->SetVisibility(ESlateVisibility::Visible);
					}
				}
			}
		}
	}
	else
	{
		if (GetEmptySlot() != -1)
		{
			int emptySlot = GetEmptySlot();
			InventoryItems[emptySlot] = item;
			item->SetActorHiddenInGame(true);
			item->SetActorEnableCollision(false);
			if (OwnerHero->GetMenuWidget())
			{
				TMap<int, UInventorySlotWidget*> slots = OwnerHero->GetMenuWidget()->GetInventoryWidget()->GetMainInventoryWidget()->GetInventorySlotsWidget()->GetInventorySlot();
				if (slots[emptySlot])
				{
					slots[emptySlot]->InvenImage->SetBrushFromTexture(item->texture);
				}
			}
		}

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
	InventoryItems[index] = inItem;
	TMap<int, UInventorySlotWidget*> slots = OwnerHero->GetMenuWidget()->GetInventoryWidget()->GetMainInventoryWidget()->GetInventorySlotsWidget()->GetInventorySlot();

	if (inItem->GetCountable() == ECountableType::E_Countable)
	{
		if (slots[index])
		{
			slots[index]->InvenImage->SetBrushFromTexture(inItem->texture);
			slots[index]->SetInvenText(inItem->GetCounts());
			slots[index]->InvenText->SetVisibility(ESlateVisibility::Visible);
		}
	}
	else
	{
		if (slots[index])
		{
			slots[index]->InvenImage->SetBrushFromTexture(inItem->texture);
			slots[index]->InvenText->SetVisibility(ESlateVisibility::Hidden);
		}

	}
}

int UInventoryComponent::GetEmptySlot()
{
	for (int index = 0; index < 42; index++)
	{
		if (InventoryItems[index] == nullptr)
		{
			return index;
		}
	}
	return -1;
}

void UInventoryComponent::SetNullItem(int index)
{
	InventoryItems[index] = nullptr;
	TMap<int, UInventorySlotWidget*> slots = OwnerHero->GetMenuWidget()->GetInventoryWidget()->GetMainInventoryWidget()->GetInventorySlotsWidget()->GetInventorySlot();

	if (slots[index])
	{
		slots[index]->InvenImage->SetBrushFromTexture(nullptr);
		slots[index]->InvenText->SetVisibility(ESlateVisibility::Hidden);
	}

}

void UInventoryComponent::SubItems(TSubclassOf<ABaseItem> itemClass, int counts)
{
	ABaseItem* item = GetWorld()->SpawnActor<ABaseItem>(itemClass);

	if (!item)
	{
		UE_LOG(LogTemp, Log, TEXT("item Fail"));
		return;
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("item Success %s"), *item->GetName());
	}
	
	if (item->GetCountable() == ECountableType::E_Countable)
	{
		for (int i = 0; i < 42; i++)
		{
			if (InventoryItems[i] != nullptr && InventoryItems[i]->GetClass() == item->GetClass())
			{
				ABaseItem* findItem = InventoryItems[i];
				
				findItem->SetCounts(findItem->GetCounts() - counts);
				
				if (OwnerHero->GetMenuWidget())
				{
					TMap<int, UInventorySlotWidget*> slots = OwnerHero->GetMenuWidget()->GetInventoryWidget()->GetMainInventoryWidget()->GetInventorySlotsWidget()->GetInventorySlot();
					if (slots[i])
					{
					 	if (findItem->GetCounts() > 0)
						{
							slots[i]->SetInvenText(findItem->GetCounts());
							UE_LOG(LogTemp, Log, TEXT("ItemCount: %d"), findItem->GetCounts());
							slots[i]->InvenText->SetVisibility(ESlateVisibility::Visible);
						}
						else
						{
							InventoryItems[i] = nullptr;
							slots[i]->InvenImage->SetBrushFromTexture(nullptr);
							slots[i]->InvenText->SetVisibility(ESlateVisibility::Hidden);
						}
					}
				}
				
			}
		}
	}
	else
	{
		for (int i = 0; i < 42; i++)
		{
			if (InventoryItems[i] != nullptr && InventoryItems[i]->GetClass() == item->GetClass())
			{
				ABaseItem* findItem = InventoryItems[i];
				
				if (OwnerHero->GetMenuWidget())
				{
					TMap<int, UInventorySlotWidget*> slots = OwnerHero->GetMenuWidget()->GetInventoryWidget()->GetMainInventoryWidget()->GetInventorySlotsWidget()->GetInventorySlot();
					if (slots[i])
					{
						InventoryItems[i] = nullptr;
						slots[i]->InvenImage->SetBrushFromTexture(nullptr);
					}
				}
				
			}
		}

		UE_LOG(LogTemp, Log, TEXT("UnCountable"));
	}
	
}

int UInventoryComponent::GetNumsOfItem(TSubclassOf<ABaseItem> item)
{
	int count = 0;

	for (int i = 0; i < 42; i++)
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

