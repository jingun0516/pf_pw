#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StatusComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnExpAdded);
DECLARE_MULTICAST_DELEGATE(FOnLevelUp);
DECLARE_MULTICAST_DELEGATE(FOnSetHP);
DECLARE_MULTICAST_DELEGATE(FOnSetMaxHP);

class ABaseCharacter;
class AHero;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PF_PW_API UStatusComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UStatusComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	void SetHP(float hp);
	void SetMaxHP(float Maxhp);

	UFUNCTION(BlueprintCallable)
	inline float GetHP() { return this->HP; }

	UFUNCTION(BlueprintCallable)
	inline float GetMaxHP() { return this->MaxHP; }

	FORCEINLINE void SetDamage(float damage) { this->Damage = damage; }
	FORCEINLINE float GetDamage() { return this->Damage; }

	FORCEINLINE void SetDamageToTree(float damage) { this->DamageToTree = damage; }
	FORCEINLINE float GetDamageToTree() { return this->DamageToTree; }

	FORCEINLINE void SetDamageToRock(float damage) { this->DamageToRock = damage; }
	FORCEINLINE float GetDamageToRock() { return this->DamageToRock; }

	FORCEINLINE void SetArmor(float armor) { this->Armor = armor; }
	FORCEINLINE float GetArmor() { return this->Armor; }

	FORCEINLINE void SetCurWeight(float weight) { this->CurWeight = weight; }
	FORCEINLINE float GetCurWeight() { return this->CurWeight; }

	FORCEINLINE void SetMaxWeight(float weight) { this->MaxWeight = weight; }
	FORCEINLINE float GetMaxWeight() { return this->MaxWeight; }

	FORCEINLINE void SetLV(int lv) { this->LV = lv; }

	UFUNCTION()
	void LevelUp();

	UFUNCTION(BlueprintCallable)
	inline int GetLevel() { return this->LV; }

	UFUNCTION()
	void AddEXP(int InExp);

	FORCEINLINE void SetEXP(int InExp) { this->exp = InExp; }

	UFUNCTION(BlueprintCallable)
	inline int GetEXP() { return exp; }

	FOnExpAdded DOnExpAdded;
	FOnLevelUp DOnLevelUp;
	FOnSetHP DOnSetHP;

	UFUNCTION()
	void OnExpAdded();

	UFUNCTION()
	void OnLevelUp();

	UFUNCTION()
	void OnSetHP();

	UFUNCTION()
	inline int GetNextEXP() { return NextEXP; }

	UFUNCTION()
	inline int GetPrevEXP() { return PrevEXP; }

	int GetStatusPoint() { return StatusPoint; }
	void SetStatusPoint(int point) { StatusPoint = point; }

private:
	float HP = 100.f;
	float MaxHP = 100.f;
	float Damage = 1.f;
	float DamageToTree = 1.f;
	float DamageToRock = 1.f;
	float Armor = 0.f;
	float CurWeight = 0.f;
	float MaxWeight = 500.f;
	int LV = 1;
	int MaxLV = 50;
	int exp = 0;
	int NextEXP = 0;
	int PrevEXP = 0;
	int StatusPoint = 0;
	UParticleSystem* LevelUpEffect;
	ABaseCharacter* OwnerCharacter;
	AHero* OwnerHero;

	class UDataTable* LevelUpDataTable;
};
