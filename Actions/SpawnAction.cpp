#include "Actions/SpawnAction.h"
#include "Helper.h"
#include "Characters/BaseCharacter.h"
#include "Characters/Hero.h"
#include "Components/Pocketmon/PocketmonComponent.h"
#include "Components/State/StateComponent.h"
#include "Components/State/StateEnum.h"
#include "Tools/MonsterBall/BaseMonsterball.h"
#include "Components/ToolComponent.h"

USpawnAction::USpawnAction()
{
	monsterball_class = Helper::GetClass<AActor>(L"/Game/Tools/pokeball/BP_MonsterBall");
	Montages.Add(Helper::GetAsset<UAnimMontage>(L"/Game/Animations/HeroAnims/AM_ThrowAction"));
}

void USpawnAction::DoAction()
{
	Super::DoAction();

	if (!OwnerCharacter->GetPocketmonComponent()->GetCurPocketmon()) return;
	
	if (OwnerCharacter->GetStateComponent()->GetState() == E_StateType::E_Idle)
	{
		PlayAnimMontageToIndex(0);
		if (monsterball_class)
		{
			FActorSpawnParameters SpawnParameter;
			SpawnParameter.Owner = OwnerCharacter;

			monsterball = GetWorld()->SpawnActor<ABaseMonsterball>(monsterball_class, FVector(), FRotator(), SpawnParameter);
			if (monsterball)
			{
				monsterball->AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, L"MonsterBallSocket");
				monsterball->SetLifeSpan(3.0f);
			}
		}
		OwnerCharacter->GetStateComponent()->SetState(E_StateType::E_Attacking);
	}
}

void USpawnAction::TickAction()
{
	Super::TickAction();
}

void USpawnAction::EndAction()
{
	Super::EndAction();
}

void USpawnAction::BeginActionNotify()
{
	Super::BeginActionNotify();

	if (monsterball)
	{
		float Speed = 3000.f;
		monsterball->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		if (OwnerHero->GetPocketmonComponent())
		{
			ABaseMonster* SpawnMonster = OwnerHero->GetPocketmonComponent()->GetCurPocketmon();
			if(SpawnMonster)
				monsterball->SetSpawnMonster(Cast<ABaseAI>(SpawnMonster));
		}
		monsterball->GetProjectileComponent()->Velocity = OwnerCharacter->GetActorForwardVector() * Speed;
		monsterball->GetProjectileComponent()->bShouldBounce = true;
		monsterball->GetProjectileComponent()->bSweepCollision = true;
		monsterball->GetProjectileComponent()->Activate();

	}
}

void USpawnAction::EndActionNotify()
{
	Super::EndActionNotify();
}
