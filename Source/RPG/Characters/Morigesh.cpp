#include "Morigesh.h"
#include "UObject/ConstructorHelpers.h"

AMorigesh::AMorigesh()
{
	Damage.SetMin(17);
	Damage.SetMax(29);
	Health.Set(177);
	AttackSpeed.Set(5.f);
	AttackRange.Set(250.f);
}
void AMorigesh::BeginPlay()
{
	Super::BeginPlay();
}

void AMorigesh::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
