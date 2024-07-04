#include "Components/UserStatusComponent.h"
#include "Characters/Hero.h"
#include "Components/StatusComponent.h"

UUserStatusComponent::UUserStatusComponent()
{
}


void UUserStatusComponent::AddHPPoint(int point)
{  
	HPPoint += point;
	UStatusComponent* statComp = OwnerHero->GetStatusComponent();
	if (!statComp) return;

	statComp->SetHP(statComp->GetHP() + point);
	statComp->SetMaxHP(statComp->GetMaxHP() + point);
}

void UUserStatusComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerHero = Cast<AHero>(GetOwner());

	if (!OwnerHero) return;
}

