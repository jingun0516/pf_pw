#include "Tools/MonsterBall/BaseMonsterball.h"
#include "Helper.h"
#include "Logging/LogMacros.h"
#include "Characters/Monsters/BaseMonster.h"
#include "Characters/BaseCharacter.h"
#include "Characters/Hero.h"
#include <Kismet/GameplayStatics.h>
#include "Components/Pocketmon/PocketmonComponent.h"
#include "Components/Pocketmon/PocketmonEnum.h"
#include "Particles/ParticleSystem.h"
#include "CatchActor.h"
#include "AI/BaseAI.h"
#include "AI/BaseAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Tools/BaseTool.h"

DEFINE_LOG_CATEGORY(BallLog);

ABaseMonsterball::ABaseMonsterball()
{
	RootComponent = Helper::CreateSceneComponent<USceneComponent>(this, "RootSceneComponent");
	UpperBody = Helper::CreateSceneComponent<UStaticMeshComponent>(this, "UpperBody", RootComponent);
	LowerBody = Helper::CreateSceneComponent<UStaticMeshComponent>(this, "DownBody", RootComponent);
	collision = Helper::CreateSceneComponent<USphereComponent>(this, "collision", UpperBody);
	ProjectileMovementComponent = Helper::CreateActorComponent<UProjectileMovementComponent>(this, "Projectile Comp");

	UpperBody->SetStaticMesh(Helper::GetAsset<UStaticMesh>(L"/Game/Tools/pokeball/Ingredients/MonsterBall_UpperBody"));
	LowerBody->SetStaticMesh(Helper::GetAsset<UStaticMesh>(L"/Game/Tools/pokeball/Ingredients/MonsterBall_LowerBody"));

	UpperBody->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	LowerBody->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	UpperBody->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
	LowerBody->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);

	UpperBody->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	LowerBody->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);

	ProjectileMovementComponent->bAutoActivate = false;

	effect = Helper::GetAsset<UParticleSystem>(L"/Game/Assets/AdvancedMagicFX13/Particles/P_ky_burst");
}

void ABaseMonsterball::SetCollisionEnable()
{
	UpperBody->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	LowerBody->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

void ABaseMonsterball::BeginPlay()
{
	Super::BeginPlay();

	collision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	collision->SetCollisionProfileName("OverlapAllDynamic");

	collision->OnComponentBeginOverlap.AddDynamic(this, &ABaseMonsterball::OnOverlap);
	ProjectileMovementComponent->OnComponentActivated.AddDynamic(this, &ABaseMonsterball::OnActivated);


	OwnerCharacter = Cast<ABaseCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());
	OwnerHero = Cast<AHero>(GetWorld()->GetFirstPlayerController()->GetCharacter());
}

void ABaseMonsterball::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (SpawnMonster)		// 스폰 동작
	{
		if (OtherActor != OwnerCharacter && OtherActor != this)
		{
			FActorSpawnParameters spawnparameters;
			spawnparameters.Owner = OwnerHero;
			ABaseMonster* spawnedMonster = OwnerHero->GetPocketmonComponent()->CheckIsSpawned();

			if (spawnedMonster)		// 스폰된 몬스터가 있으면
			{
				spawnedMonster->SetActorHiddenInGame(true);
				spawnedMonster->SetActorEnableCollision(false);
				spawnedMonster->SetSpawnType(ESpawnedType::E_UnSpawned);

				if (ABaseAI* aiMonster = Cast<ABaseAI>(spawnedMonster))
				{
					aiMonster->ActivateAIController(false);
					ABaseAIController* controller = Cast<ABaseAIController>(aiMonster->GetController());
					if (controller)
					{
						controller->get_blackboard()->SetValueAsObject(L"TargetActor", nullptr);
					}

				}

				UParticleSystemComponent* SpawnedEmitter = UGameplayStatics::SpawnEmitterAtLocation
				(
					this,
					effect,
					GetActorLocation() + spawnedMonster->GetActorScale3D().Z
				);
			}

			if (spawnedMonster != SpawnMonster)	// 스폰된 몬스터와 스폰할 몬스터가 다르다면
			{
				UParticleSystemComponent* SpawnedEmitter = UGameplayStatics::SpawnEmitterAtLocation
				(
					this,
					effect,
					GetActorLocation() + SpawnMonster->GetActorScale3D().Z
				);
				FVector location = GetActorLocation();
				location = location + FVector(0, 0, SpawnMonster->GetActorScale3D().Z);
				FVector forward = OwnerHero->GetActorForwardVector();
				location = location + FVector(forward.X * -100.f, forward.Y * -100.f, 10.f);
				SpawnMonster->SetActorLocation(location);
				SpawnMonster->SetActorHiddenInGame(false);
				SpawnMonster->SetActorEnableCollision(true);
				while(SpawnMonster->GetActorLocation().Z <= -100.f)
					SpawnMonster->SetActorLocation(location);
				SpawnMonster->SetSpawnType(ESpawnedType::E_Spawned);

				if (ABaseAI* aiMonster = Cast<ABaseAI>(SpawnMonster))
				{
					aiMonster->ActivateAIController(true);
					UE_LOG(BallLog, Log, TEXT("Activate Succeed!!"));
				}

				UE_LOG(BallLog, Log, TEXT("SpawnMonster Succeed!!"));
			}
			
			this->Destroy();
		}
	}
	else              // Catch 동작
	{
		/*
		if (!(Cast<ABaseCharacter>(OtherActor)) && !(Cast<ABaseMonsterball>(OtherActor)))
		{
			UE_LOG(BallLog, Log, TEXT("%s << overlapped SetSimulatePhysics"), *OtherActor->GetName());
			UpperBody->SetSimulatePhysics(true);
			LowerBody->SetSimulatePhysics(true);
			return;

		}
		*/
		FVector OverlapPoint;
		
		if (ABaseMonster* monster = Cast<ABaseMonster>(OtherActor))
		{
			if (!monster->GetIsWild()) return;		// 야생의 몬스터가 아닐 경우
			TArray<UPrimitiveComponent*> OverlappingComponents;
			monster->GetOverlappingComponents(OverlappingComponents);

			// 오버랩 컴포넌트가 있는지 확인하고 오버랩된 지점을 가져옵니다.
			for (UPrimitiveComponent* Component : OverlappingComponents)
			{
				// 오버랩 지점을 가져옵니다.
				Component->GetClosestPointOnCollision(GetActorLocation(), OverlapPoint);
			}

			UE_LOG(BallLog, Log, TEXT("MonsterBall Overlapped With: %s"), *OtherActor->GetName());
			UParticleSystemComponent* SpawnedEmitter = UGameplayStatics::SpawnEmitterAtLocation
			(
				this,
				effect,
				OverlapPoint
			);
			if (OwnerHero->GetPocketmonComponent())
			{
				ACatchActor* catchActor = GetWorld()->SpawnActor<ACatchActor>(OverlapPoint, FRotator());

				float CatchPercent = monster->GetCatchPercent() + OwnerHero->GetPocketmonComponent()->CalCatchPercent(monster);
				catchActor->SetCatchInfo(CatchPercent, CatchPercent, 0, monster);
				catchActor->CheckCatchFunc(CatchPercent);
				monster->SetActorHiddenInGame(true);
				monster->SetActorEnableCollision(false);
				ABaseAI* aiMonster = Cast<ABaseAI>(monster);
				if (aiMonster)
					aiMonster->ActivateAIController(false);
			}
			this->Destroy();
		}
	}
}

void ABaseMonsterball::OnActivated(UActorComponent* Component, bool Reset)
{
	UE_LOG(BallLog, Log, TEXT("Activated"));
	this->SetActorEnableCollision(true);
	SetCollisionEnable();
}