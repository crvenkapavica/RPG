#include "RPGCharacterBase.h"
#include "AbilitySystemComponent.h"
#include "RPGPlayerCharacter.h"
#include "WeaponBase.h"
#include "Components/CapsuleComponent.h"
#include "AbilityBase.h"

ARPGCharacterBase::ARPGCharacterBase()
	: CharacterLevel(1)
	, bIsAttacking(false)
	, bIsAbilityOnCooldown(false)
	, bWasHit(false)
	, TargetHits(0)
{
	PrimaryActorTick.bCanEverTick = true;

}

void ARPGCharacterBase::BeginPlay()
{
	Super::BeginPlay();

	AnimInstance = GetMesh()->GetAnimInstance();

	InitializeAbilities();



	//RemainingCooldowns.Add(GetWorldTimerManager().GetTimerElapsed(Abilities[0]->CooldownTimerHandle));
}

void ARPGCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CheckDeathCondition();
}

void ARPGCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ARPGCharacterBase::ApplyDamageInstant(ARPGCharacterBase* DamageCauser)
{
	FString n1 = GetName();
	FString n2 = n1 + "  " + DamageCauser->GetName();
	GEngine->AddOnScreenDebugMessage(1, 3, FColor::Green, n2);
}
                            
void ARPGCharacterBase::ApplyNormalDamage(const int32& InDamage)
{
	Health.Update(-InDamage);
}

void ARPGCharacterBase::PrimaryAttack()
{
}

void ARPGCharacterBase::ResetCooldown()
{
	bIsAbilityOnCooldown = false;
}

void ARPGCharacterBase::InitializeAbilities()
{

//	OnStatChanged.AddUObject(this, &ARPGCharacterBase::asd);

	// Initialize MB1 click abilit
	_InitializeAbilityPirimary();

	//Initialize MB2 click ability
	_InitializeAbilitySecondary();

	for (auto Ability : AbilitiesClass)
	{
		Abilities.Add(NewObject<UAbilityBase>(GetWorld(), Ability));
	}
}

void ARPGCharacterBase::CheckDeathCondition()
{
	
	if (Health.Get() <= 0)
	{
		if (GEngine)
		{
			//GEngine->AddOnScreenDebugMessage(0, 20.f, FColor::Red, FString("TARGET DEAD"));
		}
		//if not player
		// play death animations !!!!
		// drop loot
		Destroy();


		//if player
		//play death screen
	}
}

void ARPGCharacterBase::_InitializeAbilityPirimary()
{
	
}

void ARPGCharacterBase::_InitializeAbilitySecondary()
{
	
}

void ARPGCharacterBase::RotateTowardsEnemy(ARPGCharacterBase* Target)
{
	SetActorRotation(Target->GetActorLocation().Rotation());
}
