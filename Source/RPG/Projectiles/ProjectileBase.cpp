#include "ProjectileBase.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/StaticMeshComponent.h"
#include "RPGCharacterBase.h"

AProjectileBase::AProjectileBase()
	: Target(nullptr)
	, ProjectileSpeed(2.f)
{
	PrimaryActorTick.bCanEverTick = true;

	//ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	//SetRootComponent(ProjectileMesh);

	Particles = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particles"));
	//Particles->SetupAttachment(ProjectileMesh);
	SetRootComponent(Particles);
	Particles->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_MAX);
}

void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();
}

void AProjectileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Interpolate(DeltaTime);
}

void AProjectileBase::Interpolate(float DeltaTime)
{
	FVector CurrentLocation{ GetActorLocation() };
	FVector TargetLocation{ Target->GetActorLocation() };
	
	CurrentLocation = FMath::VInterpConstantTo(CurrentLocation, TargetLocation, DeltaTime, ProjectileSpeed);
	SetActorLocation(CurrentLocation);
}

