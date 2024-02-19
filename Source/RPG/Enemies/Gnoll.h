#pragma once

#include "CoreMinimal.h"
#include "RPGEnemyCharacter.h"
#include "Gnoll.generated.h"

/**
 * 
 */
UCLASS()
class RPG_API AGnoll: public ARPGEnemyCharacter
{
	GENERATED_BODY()

public:
	AGnoll();

protected:

	//virtual void AutoAttack(EDefaultAttackType AttackType) override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;


};
