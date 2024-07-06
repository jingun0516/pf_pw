// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AIMonster/WereWolf_AI.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/ToolComponent.h"
#include "Tools/BaseTool.h"
#include "Characters/Monsters/MonsterStatusDataAsset.h"
#include "Helper.h"

AWereWolf_AI::AWereWolf_AI()
{
	GetMesh()->SetSkeletalMesh(Helper::GetAsset<USkeletalMesh>
		(L"/Game/Assets/werewolf/Mesh/SK_Werewolf_cloth"));
	GetMesh()->SetRelativeLocation(FVector(0, 0, -90));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	GetMesh()->SetAnimInstanceClass(Helper::GetClass<UAnimInstance>
		(L"/Game/Monsters/Werewolf/Animations/ABP_Werewolf"));

	stats = Helper::GetAsset<UMonsterStatusDataAsset>(L"/Game/Monsters/Werewolf/DA_WereWolf");

	MonsterToolClass = Helper::GetClass<ABaseTool>(L"/Game/Tools/InvisibleTool/BP_Melee");
}

void AWereWolf_AI::BeginPlay()
{
	Super::BeginPlay();
}

void AWereWolf_AI::SetCharacterMovement()
{
	Super::SetCharacterMovement();

	UCharacterMovementComponent* Comp = GetCharacterMovement();

	Comp->bOrientRotationToMovement = false;
	Comp->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

	Comp->JumpZVelocity = 700.0f;
	Comp->AirControl = 0.35f;
	Comp->MaxWalkSpeed = MaxSpeed;
	Comp->MaxAcceleration = 500.f;

	Comp->BrakingDecelerationWalking = 2000.0f;
	Comp->BrakingDecelerationFalling = 1500.0f;
}
