#include "WeaponBase.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "../Player/RPGPlayerCharacter.h"
#include "../Characters/RPGCharacterBase.h"

AWeaponBase::AWeaponBase()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USphereComponent>(TEXT("Root"));
	Root->SetSphereRadius(4.f);
	SetRootComponent(Root);

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Component"));
	CapsuleComp->SetupAttachment(Root);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(CapsuleComp);
}

void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();	


	Player = Cast<ARPGPlayerCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());

	OnActorBeginOverlap.AddDynamic(this, &AWeaponBase::ActorBeginOverlap);
	OnActorEndOverlap.AddDynamic(this, &AWeaponBase::ActorEndOverlap);
}

void AWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWeaponBase::ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	ARPGCharacterBase* HitCharacter = Cast<ARPGCharacterBase>(OtherActor);
	if (!HitCharacter->bWasHit && Player->bIsAttacking)
	{
		HitCharacter->bWasHit = true;

		HitCharacter->ApplyNormalDamage(Player->Damage.Get());

		UE_LOG(LogTemp, Warning, TEXT("%s hit for %d; has %d"), *HitCharacter->GetName(), Player->Damage.GetMin(), HitCharacter->Health.Get());
	}
}

void AWeaponBase::ActorEndOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	Cast<ARPGCharacterBase>(OtherActor)->bWasHit = false;
}

