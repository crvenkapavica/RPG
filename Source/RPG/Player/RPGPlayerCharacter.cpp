#include "RPGPlayerCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Animation/AnimMontage.h"
#include "WeaponBase.h"
#include "AbilityBase.h"

ARPGPlayerCharacter::ARPGPlayerCharacter()
	: RotateCamera(0)
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 260.f, 0.f);

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Boom"));
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 1250.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bInheritPitch = false;
	CameraBoom->bInheritRoll = false;
	CameraBoom->bInheritYaw = false;
	CameraBoom->bDoCollisionTest = false;

	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Player Camera"));
	PlayerCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	PlayerCamera->bUsePawnControlRotation = false;
}

void ARPGPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ARPGPlayerCharacter::RotateCameraLeft()
{
	RotateCamera = 1;
	CameraCurrentYaw = CameraBoom->GetRelativeRotation().Yaw;
	CameraTargetYaw = CameraCurrentYaw + 15.f;
}

void ARPGPlayerCharacter::RotateCameraRight()
{
	RotateCamera = -1;
	CameraCurrentYaw = CameraBoom->GetRelativeRotation().Yaw;
	CameraTargetYaw = CameraCurrentYaw - 15.f;
}

void ARPGPlayerCharacter::HandleCameraRotation(float DeltaTime)
{
	if (RotateCamera)
	{
		CameraCurrentYaw = FMath::FInterpTo(CameraCurrentYaw, CameraTargetYaw, DeltaTime, 5.f);
		CameraBoom->SetRelativeRotation(FRotator(CameraBoom->GetRelativeRotation().Pitch, CameraCurrentYaw, CameraBoom->GetRelativeRotation().Roll));

		if (CameraCurrentYaw == CameraTargetYaw)
			RotateCamera = 0;
	}
}

// Called every frame
void ARPGPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	HandleCameraRotation(DeltaTime);

	if (AnimInstance->Montage_GetIsStopped(PrimaryAttackMontage))
	{
		bIsAttacking = false;
	}
}

// Called to bind functionality to input
void ARPGPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("RotateCameraLeft", IE_Pressed, this, &ARPGPlayerCharacter::RotateCameraLeft);
	PlayerInputComponent->BindAction("RotateCameraRight", IE_Pressed, this, &ARPGPlayerCharacter::RotateCameraRight);


	PlayerInputComponent->BindAction("AbilitySlotPrimary", IE_Pressed, this, &ARPGPlayerCharacter::UseAbilitySlot_Primary);


	PlayerInputComponent->BindAction("AbilitySlot1", IE_Pressed, this, &ARPGPlayerCharacter::SetSlot1);
	PlayerInputComponent->BindAction("AbilitySlot2", IE_Pressed, this, &ARPGPlayerCharacter::SetSlot2);
	PlayerInputComponent->BindAction("AbilitySlot3", IE_Pressed, this, &ARPGPlayerCharacter::SetSlot3);
	PlayerInputComponent->BindAction("AbilitySlot4", IE_Pressed, this, &ARPGPlayerCharacter::SetSlot4);
}

void ARPGPlayerCharacter::UseAbilityAtSlot(int32 Slot)
{
	if (Abilities.Num() > Slot)
	{
		if (MouseHit.bBlockingHit)
		{
			if (ARPGCharacterBase* MouseTarget = Cast<ARPGCharacterBase>(MouseHit.GetActor()))
			{
				//if (MouseTarget != this) zameniti za cast
				{
					if (!Abilities[Slot]->TryUseAbility(this, MouseTarget))
					{
						GEngine->AddOnScreenDebugMessage(0, 5, FColor::Red, Abilities[Slot]->ErrorMessage);
					}
				}
			}
		}
	}
}

void ARPGPlayerCharacter::UseAbilitySlot_Primary()
{
	AnimInstance->Montage_Play(PrimaryAttackMontage);
	bIsAttacking = true;
}