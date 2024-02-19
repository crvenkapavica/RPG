#include "RPGAnimInstanceBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "RPGCharacterBase.h"
#include "Khaimera.h"

void URPGAnimInstanceBase::UpdateAnimationProperties(float DeltaTime)
{
	if (!Character)
	{
		Character = Cast<ARPGCharacterBase>(TryGetPawnOwner());
	}
	if (Character)
	{
		FVector Velocity{ Character->GetVelocity().Size() };
		Velocity.Z = 0.f;
		Speed = Velocity.Size();

		bIsAccelerating = true;
	}
}

void URPGAnimInstanceBase::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Character = Cast<ARPGCharacterBase>(TryGetPawnOwner());
}
