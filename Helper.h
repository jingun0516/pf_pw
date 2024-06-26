// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SkeletalMeshAttributes.h"

/**
 *
 */
class PF_PW_API Helper
{
public:
	static double GetAngleBetweenActors(FVector Actor1Location, FVector Actor2Location, FVector ActorForward) {
		// �� ���� ���� ��� ��ġ ���� ���
		FVector DeltaVector = Actor2Location - Actor1Location;

		// ��� ��ġ ���͸� ����ȭ�Ͽ� ���� ���ͷ� ����ϴ�.
		FVector NormalizedDeltaVector = DeltaVector;
		NormalizedDeltaVector.Normalize();
		// ������ ������ ���͸� ����ȭ�Ͽ� ���� ���ͷ� ����ϴ�.
		FVector NormalizedForwardVector = ActorForward;
		NormalizedForwardVector.Normalize();

		// ���� ���
		double DotProduct = NormalizedDeltaVector.Dot(NormalizedForwardVector);

		// ������ �̿��Ͽ� ���� ���
		double AngleRad = acos(DotProduct);
		double AngleDeg = AngleRad * 180.0 / PI;

		return AngleDeg;
	}
	template<typename T>
	static T* CreateSceneComponent(AActor* InOwner, FName InComponentName,
		USceneComponent* InParent = nullptr, FName InSocketName = NAME_None)
	{
		T* Component = InOwner->CreateDefaultSubobject<T>(InComponentName);

		if (InParent != nullptr)
			Component->SetupAttachment(InParent, InSocketName);
		else
			InOwner->SetRootComponent(Component);

		return Component;
	}

	template<typename T>
	static T* CreateActorComponent(AActor* Owner, FName ComponentName)
	{
		return Owner->CreateDefaultSubobject<T>(ComponentName);
	}

	template<typename T>
	static T* GetAsset(FString InPath)
	{
		ConstructorHelpers::FObjectFinder<T> Asset(*InPath);
		return Cast<T>(Asset.Object);
	}

	template<typename T>
	static TSubclassOf<T> GetClass(FString InPath)
	{
		ConstructorHelpers::FClassFinder<T> Asset(*InPath);
		return Asset.Class;
	}
};

#define MAPPING_CLICK(EnhancedInputComponent, InputAction, StartedAction, CompletedAction) \
		if(InputAction) \
		{ \
			EnhancedInputComponent->BindAction(InputAction, ETriggerEvent::Started, this, &StartedAction); \
			EnhancedInputComponent->BindAction(InputAction, ETriggerEvent::Completed, this, &CompletedAction); \
		}

#define MAPPING_TRIGGERED(EnhancedInputComponent, InputAction, Action) \
		if(InputAction) \
			EnhancedInputComponent->BindAction(InputAction, ETriggerEvent::Triggered, this, &Action);

#define MULTICAST_DELEGATE_BROADCAST(Delegate) if(Delegate.IsBound()) Delegate.Broadcast();	

#define SET_GAME_MODE_GAME_ONLY() \
{ \
    APlayerController* PlayerController = GetWorld()->GetFirstPlayerController(); \
    if (PlayerController) \
    { \
        FInputModeGameOnly InputMode; \
        PlayerController->SetInputMode(InputMode); \
        PlayerController->bShowMouseCursor = false; \
    } \
}

