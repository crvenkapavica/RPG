#include "Khaimera.h" 	
#include "WeaponBase.h"


AKhaimera::AKhaimera()
{
	Damage.SetMin(2);
	Damage.SetMax(5);
	Health.Set(100);
	AttackRange.Set(125.f);
	AttackSpeed.Set(2.f);
	Resource = 20000.f;
}

void AKhaimera::BeginPlay()
{
	Super::BeginPlay();.
}

void AKhaimera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}