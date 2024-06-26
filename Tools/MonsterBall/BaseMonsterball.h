#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Components/SphereComponent.h>
#include <GameFramework/ProjectileMovementComponent.h>
#include "BaseMonsterball.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(BallLog, Log, All);

class ABaseCharacter;
class ABaseMonster;
class AHero;
class UParticleSystem;
class ABaseAI;

UCLASS()
class PF_PW_API ABaseMonsterball : public AActor
{
	GENERATED_BODY()
	
public:	
	ABaseMonsterball();

	FORCEINLINE UProjectileMovementComponent* GetProjectileComponent() { return ProjectileMovementComponent; }
	void SetCollisionEnable();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(Visibleanywhere, BlueprintReadWrite)
	UStaticMeshComponent* UpperBody;

	UPROPERTY(Visibleanywhere, BlueprintReadWrite)
	UStaticMeshComponent* LowerBody;

	UPROPERTY(Visibleanywhere, BlueprintReadWrite)
	USphereComponent* collision;

	UPROPERTY(Visibleanywhere, BlueprintReadWrite)
	UProjectileMovementComponent* ProjectileMovementComponent;

	ABaseAI* SpawnMonster;
	ABaseCharacter* OwnerCharacter;
	AHero* OwnerHero;

	TSubclassOf<UParticleSystem> effectClass;
	UParticleSystem* effect;

public:
	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

	UFUNCTION()
	void OnActivated(UActorComponent* Component, bool Reset);

	UFUNCTION()
	FORCEINLINE void SetSpawnMonster(ABaseAI* InMonster) { SpawnMonster = InMonster; }
};
