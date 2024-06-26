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
		// 두 액터 간의 상대 위치 벡터 계산
		FVector DeltaVector = Actor2Location - Actor1Location;

		// 상대 위치 벡터를 정규화하여 방향 벡터로 만듭니다.
		FVector NormalizedDeltaVector = DeltaVector;
		NormalizedDeltaVector.Normalize();
		// 액터의 포워드 벡터를 정규화하여 방향 벡터로 만듭니다.
		FVector NormalizedForwardVector = ActorForward;
		NormalizedForwardVector.Normalize();

		// 내적 계산
		double DotProduct = NormalizedDeltaVector.Dot(NormalizedForwardVector);

		// 내적을 이용하여 각도 계산
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

