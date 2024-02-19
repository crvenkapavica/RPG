// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RPGPlayerCharacter.h"
#include "Morigesh.generated.h"

/**
 * 
 */
UCLASS()
class RPG_API AMorigesh: public ARPGPlayerCharacter
{
	GENERATED_BODY()

public:
	AMorigesh();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	//virtual void UseAbilitySlot_Primary() override;
};
