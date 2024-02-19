// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "RPGEnemyController.generated.h"

class ARPGCharacterBase;

/**
 * 
 */
UCLASS()
class RPG_API ARPGEnemyController : public AAIController
{
	GENERATED_BODY()

public:
	ARPGEnemyController();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void MoveToPlayer();

	//void BeginAttackSequence();

private:

	class ARPGEnemyCharacter* Enemy;

	ARPGCharacterBase* Player;
	
};
