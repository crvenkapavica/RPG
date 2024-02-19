// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RPGPlayerCharacter.h"
#include "Khaimera.generated.h"

/**
 * 
 */
UCLASS()
class RPG_API AKhaimera : public ARPGPlayerCharacter
{
	GENERATED_BODY()

public:
	AKhaimera();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
};
