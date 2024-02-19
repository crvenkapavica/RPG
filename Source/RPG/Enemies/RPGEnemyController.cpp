#include "RPGEnemyController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "RPGCharacterBase.h"
#include "RPGPlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "RPGEnemyCharacter.h"

ARPGEnemyController::ARPGEnemyController()
{
	
}

void ARPGEnemyController::BeginPlay()
{
	Super::BeginPlay();

	Enemy = Cast<ARPGEnemyCharacter>(GetPawn());
	Enemy->GetCharacterMovement()->MaxWalkSpeed = 200.f;
	Player = Cast<ARPGPlayerCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
}

void ARPGEnemyController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (FVector::Dist(Enemy->GetActorLocation(), Player->GetActorLocation()) <= Enemy->AttackRange.Get())
	{
		StopMovement();
		Enemy->BeginAttackSequence();
	}
	else
		MoveToPlayer();
}

void ARPGEnemyController::MoveToPlayer()
{
	UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, Player->GetActorLocation());
}
