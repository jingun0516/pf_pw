#include "Actions/ThrowAction.h"
#include "Helper.h"
#include "Characters/BaseCharacter.h"
#include "Components/State/StateComponent.h"
#include "Components/State/StateEnum.h"
#include "Tools/MonsterBall/BaseMonsterball.h"
#include "Components/ToolComponent.h"
#include "Characters/Hero.h"
#include "Camera/CameraComponent.h"

UThrowAction::UThrowAction()
{
	monsterball_class = Helper::GetClass<AActor>(L"/Game/Tools/pokeball/BP_MonsterBall");
	Montages.Add(Helper::GetAsset<UAnimMontage>(L"/Game/Animations/HeroAnims/AM_ThrowAction"));
}

void UThrowAction::DoAction()
{
	Super::DoAction();

	if (OwnerCharacter->GetStateComponent()->GetState() != E_StateType::E_Idle) return;
	
	PlayAnimMontageToIndex(0);
	if (!monsterball_class) return;
	
	FActorSpawnParameters SpawnParameter;
	SpawnParameter.Owner = OwnerCharacter;

	monsterball = GetWorld()->SpawnActor<ABaseMonsterball>(monsterball_class, FVector(), FRotator(), SpawnParameter);
	if (!monsterball) return;
	
	monsterball->AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, L"MonsterBallSocket");
	monsterball->SetLifeSpan(3.0f);
	
	
	OwnerCharacter->GetStateComponent()->SetState(E_StateType::E_Attacking);
	
}

void UThrowAction::TickAction()
{
	Super::TickAction();
}

void UThrowAction::EndAction()
{
	Super::EndAction();
}

void UThrowAction::BeginActionNotify()
{
	Super::BeginActionNotify();
	
	if (monsterball)
	{
		float Speed = 10000.f;
		monsterball->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

		monsterball->GetProjectileComponent()->Velocity = OwnerCharacter->GetActorForwardVector() * Speed;
		monsterball->GetProjectileComponent()->bRotationFollowsVelocity = true;
		monsterball->GetProjectileComponent()->bShouldBounce = true;
		monsterball->GetProjectileComponent()->bSweepCollision = true;
		monsterball->GetProjectileComponent()->Activate();
	}
}

void UThrowAction::EndActionNotify()
{
	Super::EndActionNotify();
}
