#pragma once

#include "CoreMinimal.h"
#include "RPGCharacterBase.h"
#include "RPGEnemyCharacter.generated.h"


enum class EDefaultAttackType : uint8
{
	EDAT_Melee,
	EDAT_Ranged,
	EDAT_Magic
};


/**
 * 
 */
UCLASS()
class RPG_API ARPGEnemyCharacter : public ARPGCharacterBase
{
	GENERATED_BODY()

public:

	ARPGEnemyCharacter();
	virtual void Tick(float DeltaTime) override;

	virtual void BeginAttackSequence();

protected:


	EDefaultAttackType DefaultAttackType;

	float AggroRange;

	float attackRange = 120.f;

	bool bIsInPlayerRange;

protected:

	virtual void AutoAttack(EDefaultAttackType AttackType);
};
