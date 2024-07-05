#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseResource.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(ResourceLog, Log, All);

class UParticleSystem;
class USoundCue;
class ABaseItem;
class UCapsuleComponent;
class UAIPerceptionStimuliSourceComponent;

UCLASS()
class PF_PW_API ABaseResource : public AActor
{
	GENERATED_BODY()
	
public:	
	ABaseResource();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

public:
	FORCEINLINE void SetHP(float InHP) { HP = InHP; }

	FORCEINLINE float GetHP() { return HP; }
	FORCEINLINE float GetMaxHP() { return MaxHP; }

public:	
	virtual void Tick(float DeltaTime) override;

	virtual float TakeDamage
	(
		float DamageAmount,
		struct FDamageEvent const& DamageEvent,
		class AController* EventInstigator,
		AActor* DamageCauser
	) override;

	UParticleSystem* GetGather() { return gather; }
	USoundCue* GetSound() { return sound; }

	void Respawn();
	virtual void Die();

protected:
	UPROPERTY(Visibleanywhere)
	UStaticMeshComponent* mesh = nullptr;

	UPROPERTY(EditAnywhere)
	UCapsuleComponent* col = nullptr;

	UPROPERTY(EditAnywhere)
	UAIPerceptionStimuliSourceComponent* StimuliSourceComponent;

	TSubclassOf<ABaseItem> SpawnItemClass;

	UParticleSystem* gather;
	USoundCue* sound;
private:
	float HP = 50.f;
	float MaxHP = 50.f;
};
