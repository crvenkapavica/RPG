// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilityBase.h"
#include "Ability_IceBolt.generated.h"

/**
 * 
 */
UCLASS()
class RPG_API UAbility_IceBolt : public UAbilityBase
{
	GENERATED_BODY()

public:
	UAbility_IceBolt();
	
	UFUNCTION()
	void OnActorHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);


	void UseAbility_Projectile() override;

};
