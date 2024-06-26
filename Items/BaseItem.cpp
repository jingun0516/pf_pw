#include "Items/BaseItem.h"
#include "Characters/Hero.h"
#include "Characters/BaseCharacter.h"
#include "Blueprint/UserWidget.h"
#include "Components/InventoryComponent.h"
#include "Helper.h"

ABaseItem::ABaseItem()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = Helper::CreateSceneComponent<USceneComponent>(this, "RootSceneComponent");
	ItemMesh = Helper::CreateSceneComponent<UStaticMeshComponent>(this, "Item Mesh", RootComponent);
	ItemMesh_Skel = Helper::CreateSceneComponent<USkeletalMeshComponent>(this, "ItemMesh Skel", RootComponent);
	ItemCol = Helper::CreateSceneComponent<UCapsuleComponent>(this, "Collision", RootComponent);

	ItemMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	ItemMesh_Skel->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	WidgetClass = Helper::GetClass<UUserWidget>(TEXT("/Game/Widgets/BuildingWidget/WB_BaseInteraction"));
}

void ABaseItem::SetOwnerHero(ABaseCharacter* InOwner)
{
	OwnerCharacter = InOwner;
	if (AHero* hero = Cast<AHero>(InOwner)) OwnerHero = hero;
}

void ABaseItem::BeginPlay()
{
	Super::BeginPlay();

	if (WidgetClass)
	{
		BaseWidget = CreateWidget(GetWorld(), WidgetClass);

		if (BaseWidget)
		{
			BaseWidget->AddToViewport();
			BaseWidget->SetVisibility(ESlateVisibility::Hidden);
		}
	}
	if (Cast<ABaseCharacter>(GetOwner()))
		OwnerCharacter = Cast<ABaseCharacter>(GetOwner());
}

void ABaseItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

