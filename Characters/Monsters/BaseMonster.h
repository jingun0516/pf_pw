#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Characters/BaseCharacter.h"
#include "Components/Pocketmon/PocketmonEnum.h"
#include "BaseMonster.generated.h"

class ABaseCharacter;
class UActionDataAsset;
class UMonsterStatusDataAsset;
class UMonsterStatusWidget;
class UWidgetComponent;
enum class EPocketmonRating;

DECLARE_LOG_CATEGORY_EXTERN(MonsterLog, Log, All);

UENUM(BlueprintType)
enum class ESpawnedType
{
	E_Spawned UMETA(Displayname = "Spawned"),
	E_UnSpawned UMETA(Displayname = "UnSpawned")
};

UCLASS()
class PF_PW_API ABaseMonster : public ABaseCharacter
{
	GENERATED_BODY()

public:
	ABaseMonster();

	FORCEINLINE float GetCatchPercent() { return CatchPercent; }
	FORCEINLINE UTexture2D* GetTexture() { return texture; }
	FORCEINLINE ESpawnedType GetSpawnType() { return SpawnType; }
	FORCEINLINE void SetSpawnType(ESpawnedType type) { SpawnType = type; }
	FORCEINLINE FText GetMonName() { return Name; }
	FORCEINLINE bool GetIsWild() { return Wild; }
	FORCEINLINE void SetWild(bool InWild) { Wild = InWild; }
	FORCEINLINE float GetMaxSpeed() { return MaxSpeed; }
	FORCEINLINE float GetWalkSpeed() { return WalkSpeed; }
	void SetMonsterStatus();
	void SetTeamMonster();

	virtual float TakeDamage
	(
		float DamageAmount,
		struct FDamageEvent const& DamageEvent,
		class AController* EventInstigator,
		AActor* DamageCauser
	) override;
protected:
	virtual void BeginPlay() override;
	virtual void SetCharacterMovement() override;
	virtual void SetInfos(UMonsterStatusDataAsset* InStats);
	void SetCatchPercent();

	void UpdateWidgetScale();

	virtual void Tick(float DeltaTime) override;

protected:
	FText Name;
	UActionDataAsset* Actions;
	UMonsterStatusDataAsset* stats;
	EPocketmonRating rating = EPocketmonRating::E_Normal;
	float CatchPercent;
	UTexture2D* texture;
	ESpawnedType SpawnType = ESpawnedType::E_UnSpawned;
	bool Wild = true;
	float MaxSpeed = 200.f;
	float WalkSpeed = 100.f;

	UPROPERTY(EditAnywhere)
	UWidgetComponent* MonsterStatusWidgetComp;

	UMonsterStatusWidget* MonsterStatusWidget;
	TSubclassOf<UUserWidget> MonsterStatusClass;
};
