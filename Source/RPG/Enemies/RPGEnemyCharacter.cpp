#include "RPGEnemyCharacter.h"
#include "RPGEnemyController.h"

ARPGEnemyCharacter::ARPGEnemyCharacter()
{
	AIControllerClass = ARPGEnemyController::StaticClass();
}


void ARPGEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ARPGEnemyCharacter::AutoAttack(EDefaultAttackType AttackType)
{

}

void ARPGEnemyCharacter::BeginAttackSequence()
{
	GEngine->AddOnScreenDebugMessage(0, 1, FColor::White, TEXT("BeginAttSeq"));
	AnimInstance->Montage_Play(PrimaryAttackMontage);
}