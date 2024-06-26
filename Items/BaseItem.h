#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Components/CapsuleComponent.h>
#include "BaseItem.generated.h"

class AHero;
class ABaseCharacter;

UENUM(BlueprintType)
enum class ECountableType
{
	E_Countable,
	E_UnCountable
};

UENUM(BlueprintType)
enum class EUsableType
{
	E_Usable,
	E_UnUsable
};


UCLASS()
class PF_PW_API ABaseItem : public AActor
{
	GENERATED_BODY()
	
public:	
	ABaseItem();

	FORCEINLINE ECountableType GetCountable() { return countable; }
	FORCEINLINE int GetCounts() { return counts; }
	FORCEINLINE void SetCounts(int count) { counts = count; }
	void SetOwnerHero(ABaseCharacter* InOwner);
	FORCEINLINE UTexture2D* GetTexture() { return texture; }
protected:
	virtual void BeginPlay() override;

	ECountableType countable = ECountableType::E_Countable;
	EUsableType usable = EUsableType::E_Usable;
	int counts = 1;

public:	
	virtual void Tick(float DeltaTime) override;

protected:
	ABaseCharacter* OwnerCharacter;
	AHero* OwnerHero;
	AHero* PlayerC;

	UPROPERTY(Visibleanywhere, BlueprintReadWrite)
	UCapsuleComponent* ItemCol = nullptr;

	UPROPERTY(Visibleanywhere, BlueprintReadWrite)
	USkeletalMeshComponent* ItemMesh_Skel = nullptr;

	UPROPERTY(Visibleanywhere, BlueprintReadWrite)
	UStaticMeshComponent* ItemMesh = nullptr;

	TSubclassOf<UUserWidget> WidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Weight = 0.1f;

public:
	UPROPERTY()
	TArray<TSubclassOf<ABaseItem>> RequiredItems;

	UPROPERTY()
	TArray<int> RequiredCounts;

	UPROPERTY(Visibleanywhere)
	UUserWidget* BaseWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* texture;
};
