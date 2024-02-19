#include "AbilityBase.h"
#include "Components/CapsuleComponent.h"
#include "Components/ShapeComponent.h"
#include "RPGCharacterBase.h"
#include "ProjectileBase.h"
#include "Kismet/GameplayStatics.h"

UAbilityBase::UAbilityBase()
{
	FWorldDelegates::OnPostWorldCreation.AddUFunction<UAbilityBase>(this, TEXT("BeginPlay"));


	//FWorldDelegates::OnWorldTickStart.Clear();


	//static ConstructorHelpers::FClassFinder<AProjectileBase> ProjectileBPClass(TEXT("Blueprint'/Game/_Game/Projectiles/ProjectileBase_BP.ProjectileBase_BP_C'"));

	//AbilityInfo.AbilitySpec.AbilityProjectile.ProjectileClass = ProjectileBPClass.Class;

	bInitialized = true;
}

void UAbilityBase::BeginPlay()
{
	ReceiveBeginPlay();
}

// Called upon Construction ONLY
void UAbilityBase::PostInitProperties()
{
	Super::PostInitProperties();
}

void UAbilityBase::Tick()
{
	UE_LOG(LogTemp, Warning, TEXT("%f"), DeltaTime);
}


void UAbilityBase::SetAbilityInfo(FAbilityInfo& DefaultAbilityInfo)
{
	AbilityInfo = DefaultAbilityInfo;
}


FAbilityInfo UAbilityBase::ConstructDefaultAbilityInfo(EAbilityType AbilityType, ETargetType TargetType, EResourceType ResourceType, FAbilitySpec& AbilitySpec)
{
	FAbilityInfo DefaultAbilityInfo;
	DefaultAbilityInfo.AbilityType = AbilityType;
	DefaultAbilityInfo.TargetType = TargetType;
	DefaultAbilityInfo.ResourceType = ResourceType;
	DefaultAbilityInfo.AbilitySpec = AbilitySpec;
	
	return DefaultAbilityInfo;
}

bool UAbilityBase::_PrepareAbility(ARPGCharacterBase* InInstigator, ARPGCharacterBase* InTarget)
{
	if (!InInstigator || !InTarget)
	{
		return 0;
	}

	Instigator = InInstigator;
	Target = InTarget;

	return 1;
}

bool UAbilityBase::_CheckUsable()
{
	if (Instigator->Resource.Get() < AbilityResourceCost)
	{
		ErrorMessage = FString{ "Inssufficient resources" };
		return 0;
	}
	if (bIsAbilityOnCooldown)
	{
		ErrorMessage = FString{ "Spell not ready yet" };
		return 0;
	}
	if (FVector::Dist(Instigator->GetActorLocation(), Target->GetActorLocation()) > AbilityRange)
	{
		// TODO - maybe move towards range
		ErrorMessage = FString{ "Out of Range" };
		return 0;
	}

	return 1;
}

void UAbilityBase::_FinishAbility()
{ 
	bIsAbilityOnCooldown = true;
	GetWorld()->GetTimerManager().SetTimer(CooldownTimerHandle, this, &UAbilityBase::_ResetAbilityCooldown, AbilityCooldown);

	Instigator->Resource.Update(-AbilityResourceCost);
}

void UAbilityBase::_ResetAbilityCooldown()
{
	bIsAbilityOnCooldown = false;
}

bool UAbilityBase::TryUseAbility(ARPGCharacterBase* InInstigator, ARPGCharacterBase* InTarget)
{
	if (!_PrepareAbility(InInstigator, InTarget))
	{
		return 0;
	}
	if (!_CheckUsable())
	{
		return 0;
	}
	

	switch (AbilityInfo.AbilityType)
	{
	case EAbilityType::EAT_Projectile:
		UseAbility_Projectile();
		break;
	}

	_FinishAbility();

	return 1;
}


void UAbilityBase::UseAbility_Projectile()
{

}
