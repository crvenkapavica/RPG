#include "RPGPlayerController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "RPGCharacterBase.h"
#include "Khaimera.h"
#include "RPGPlayerCharacter.h"
#include "Components/CapsuleComponent.h"
#include "RPGPlayerCharacter.h"
#include "AbilityBase.h"


ARPGPlayerController::ARPGPlayerController()
	: bIsMousePressed(false)
{
	bShowMouseCursor = true;
	bEnableMouseOverEvents = true;
	bEnableClickEvents = true;
}

void ARPGPlayerController::BeginPlay()
{
	Super::BeginPlay();

	Player = Cast<ARPGPlayerCharacter>(GetPawn());
}

void ARPGPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateTarget();
}


void ARPGPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	InputComponent->BindAction("SetTarget", IE_Pressed, this, &ARPGPlayerController::SetTargetPressed);
	InputComponent->BindAction("SetTarget", IE_Released, this, &ARPGPlayerController::SetTargetReleased);
}

void ARPGPlayerController::SetTargetPressed()
{
	bIsMousePressed = true;
}

void ARPGPlayerController::SetTargetReleased()
{
	bIsMousePressed = false;
}

void ARPGPlayerController::UpdateTarget()
{
	FHitResult MouseHit;
	GetHitResultUnderCursor(ECollisionChannel::ECC_MAX, false, MouseHit);

	if (MouseHit.bBlockingHit)
	{
		if (bIsMousePressed)
		{
			if (MouseHit.GetActor()->IsA<ARPGCharacterBase>() && MouseHit.GetActor() != GetPawn())
			{
				ARPGCharacterBase* Target = Cast<ARPGCharacterBase>(MouseHit.GetActor());

				if (FVector::Dist(Player->GetActorLocation(), Target->GetActorLocation()) <= Player->AttackRange.Get())
				{
					StopMovement();
					//if (Player->bPlayerIsIdle)
					{
						Player->UseAbilitySlot_Primary();
					}
					
				}
				else
				{
					UAIBlueprintHelperLibrary::SimpleMoveToActor(this, MouseHit.GetActor());
				}
			}
			else
			{
				UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, MouseHit.Location);
			}
		}
		else
		{
			Player->MouseHit = MouseHit;
		}
	}
}