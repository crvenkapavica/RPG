#include "Gnoll.h"
#include "RPGEnemyController.h"

AGnoll::AGnoll()
{
	Damage.SetMin(9);
	Damage.SetMax(17);
	AttackRange.Set(125.f);
	AttackSpeed.Set(3.f);
	Health.Set(50);
}

void AGnoll::BeginPlay()
{
	Super::BeginPlay();
	//OnActorEndOverlap.AddDynamic(this, &AGnoll::OnActorBeginOverlap);
	FVector PlayerLocation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
}



void AGnoll::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime); 

}
