#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "Characters/BaseCharacter.h"
#include "Hero.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;

class UMenuWidget;
class UStatusItemSlotWidget;
class UBaseStatusWidget;
class UToBuildWidget;

struct FInputActionValue;

// Weapon Select Deleagte
DECLARE_MULTICAST_DELEGATE(FMainWeaponSelect);					// 델리게이트 선언
DECLARE_MULTICAST_DELEGATE(FSecondaryWeaponSelect);
DECLARE_MULTICAST_DELEGATE(FThrowableWeaponSelect);
DECLARE_MULTICAST_DELEGATE_OneParam(FScrollSelect, UINT);		// 델리게이트에 파라미터 넘겨주기

// Action Delegate
DECLARE_MULTICAST_DELEGATE(FDoAvoidAction);
DECLARE_MULTICAST_DELEGATE(FEndAvoidAction);

DECLARE_MULTICAST_DELEGATE(FDoSpawnAction);
DECLARE_MULTICAST_DELEGATE(FDoThrowAction);

DECLARE_MULTICAST_DELEGATE(FDoReloadAction);
DECLARE_MULTICAST_DELEGATE(FDoInterAction);

DECLARE_MULTICAST_DELEGATE(FFirstSelect);
DECLARE_MULTICAST_DELEGATE(FSecondSelect);
DECLARE_MULTICAST_DELEGATE(FThirdSelect);
DECLARE_MULTICAST_DELEGATE(FForthSelect); 
DECLARE_MULTICAST_DELEGATE(FPocketmonNextSlot);
DECLARE_MULTICAST_DELEGATE(FPocketmonPrevSlot);
/**
 *
 */

DECLARE_LOG_CATEGORY_EXTERN(HeroLog, Log, All);

class UInputDataAsset;
class UUserStatusComponent;

UCLASS()
class PF_PW_API AHero : public ABaseCharacter
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UUserStatusComponent* UserStatusComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* KeyMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputDataAsset* InputData;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Action, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Action, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Action, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Action, meta = (AllowPrivateAccess = "true"))
	UInputAction* MainAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Action, meta = (AllowPrivateAccess = "true"))
	UInputAction* SubAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Action, meta = (AllowPrivateAccess = "true"))
	UInputAction* ReloadAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Action, meta = (AllowPrivateAccess = "true"))
	UInputAction* ThrowAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Action, meta = (AllowPrivateAccess = "true"))
	UInputAction* SpawnAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Action, meta = (AllowPrivateAccess = "true"))
	UInputAction* InterAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Select, meta = (AllowPrivateAccess = "true"))
	UInputAction* FirstSelect;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Select, meta = (AllowPrivateAccess = "true"))
	UInputAction* SecondSelect;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Select, meta = (AllowPrivateAccess = "true"))
	UInputAction* ThirdSelect;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Select, meta = (AllowPrivateAccess = "true"))
	UInputAction* ForthSelect;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Select, meta = (AllowPrivateAccess = "true"))
	UInputAction* PocketmonNextSlot;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Select, meta = (AllowPrivateAccess = "true"))
	UInputAction* PocketmonPrevSlot;

public:
	AHero();

protected:
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent
	(UInputComponent* PlayerInputComponent) override;

	virtual void SetCharacterMovement() override;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);

	void NotifyActorBeginOverlap(AActor* OtherActor) override;
	void NotifyActorEndOverlap(AActor* OtherActor) override;

public:
	virtual void Tick(float DeltaSecond) override;

	FORCEINLINE USpringArmComponent* GetCameraArm() const { return CameraArm; }
	FORCEINLINE UCameraComponent* GetCamera() const { return Camera; }
	FORCEINLINE UUserStatusComponent* GetUserStatusComponent() { return UserStatusComponent; }

private:
	void CreateCamera();
	void SetInfoWithData(UInputDataAsset* inData);

public:
	FMainWeaponSelect DMainWeaponSelect;
	FSecondaryWeaponSelect DSecondaryWeaponSelect;
	FThrowableWeaponSelect DThrowableWeaponSelect;
	FScrollSelect DScrollSelect;

	FDoAvoidAction DDoAvoidAction;
	FEndAvoidAction DEndAvoidAction;

	FDoReloadAction DDoReloadAction;
	FDoInterAction DDoInterAction;

	FFirstSelect DDoFirstSelect;
	FSecondSelect DDoSecondSelect;
	FThirdSelect DDoThirdSelect;
	FForthSelect DDoForthSelect;
	FPocketmonNextSlot DPocketmonNextSlot;
	FPocketmonPrevSlot DPocketmonPrevSlot;

	FDoSpawnAction DDoSpawnAction;
	FDoThrowAction DDoThrowAction;

	void DoReloadAction();
	void DoAvoidAction();
	void EndAvoidAction(); 
	void DoInterAction();

	void DoSpawnAction();
	void DoThrowAction();

	void DoFirstSelect();
	void DoSecondSelect();
	void DoThirdSelect();
	void DoForthSelect();
	void DoPocketmonNextSlot();
	void DoPocketmonPrevSlot();

	UFUNCTION()
	void ToolSlotChanged(ABaseTool* Tool1, ABaseTool* Tool2, ABaseTool* Tool3, ABaseTool* Tool4);

	UFUNCTION()
	void SetHPBar(float HP, float MaxHP);

	UFUNCTION()
	void SetExpBar(int EXP, int NextEXP);

	UFUNCTION()
	void SetLevelWidget(int LV);

	UFUNCTION(BlueprintCallable)
	void SetBaseStatusWidgetVisible(bool bIsVisible = true);

	void HideAllWidget();

	void OnPocketmonSlotChanged();

	UMenuWidget* GetMenuWidget() { return MenuWidget; }
	UToBuildWidget* GetToBuildWidget() { return ToBuildWidget; }

	UFUNCTION(BlueprintCallable)
	UBaseStatusWidget* GetBaseStatusWidget() { return BaseStatusWidget; }

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USkeletalMeshComponent* Head;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USkeletalMeshComponent* UpperBody;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USkeletalMeshComponent* LowerBody;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USkeletalMeshComponent* Hand;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USkeletalMeshComponent* Shoes;

private:
	TSubclassOf<UMenuWidget> MenuClass;
	TSubclassOf<UToBuildWidget> ToBuildClass;
	TSubclassOf<UBaseStatusWidget> BaseStatusClass;
	UMenuWidget* MenuWidget;
	UToBuildWidget* ToBuildWidget;
	UBaseStatusWidget* BaseStatusWidget;
};
