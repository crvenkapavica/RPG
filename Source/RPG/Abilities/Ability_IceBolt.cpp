#include "Ability_IceBolt.h"
#include "ProjectileBase.h"
#include "Kismet/GameplayStatics.h"
#include "RPGCharacterBase.h"

UAbility_IceBolt::UAbility_IceBolt()
{	
	FAbilitySpec AbilitySpec;
	AbilitySpec.AbilityProjectile.ProjectileSpeed = 350.f;

	static ConstructorHelpers::FClassFinder<AProjectileBase> ProjectileBPClass(TEXT("Blueprint'/Game/_Game/Projectiles/ProjectileBase_BP.ProjectileBase_BP_C'"));
	AbilitySpec.AbilityProjectile.ProjectileClass = ProjectileBPClass.Class;

	FAbilityInfo DefaultAbilityInfo = ConstructDefaultAbilityInfo(EAbilityType::EAT_Projectile, ETargetType::ETT_Single, EResourceType::ERT_Mana, AbilitySpec);
	SetAbilityInfo(DefaultAbilityInfo);

	AbilityRange = 1500.f /* + Character Bonus Range */;
	AbilityCooldown = 20.f  /* - Character Cooldown reduction */;
	AbilityResourceCost = 250.f /* + Char bonuses */;
}

void UAbility_IceBolt::UseAbility_Projectile()
{
	if (AbilityInfo.TargetType == ETargetType::ETT_Single)
	{
		AProjectileBase* Projectile = GetWorld()->SpawnActorDeferred<AProjectileBase>(AbilityInfo.AbilitySpec.AbilityProjectile.ProjectileClass, Instigator->GetTransform());
		Projectile->SetSpeed(AbilityInfo.AbilitySpec.AbilityProjectile.ProjectileSpeed);
		Projectile->SetTarget(Target);
		Projectile->OnActorHit.AddDynamic(this, &UAbility_IceBolt::OnActorHit);
		UGameplayStatics::FinishSpawningActor(Projectile, Instigator->GetTransform());
	}
}

void UAbility_IceBolt::OnActorHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	GEngine->AddOnScreenDebugMessage(1, 15, FColor::White, FString("OVERAJ DELEGETE"));
}



