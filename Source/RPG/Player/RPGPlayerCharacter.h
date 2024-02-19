// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RPGCharacterBase.h"
#include "RPGPlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class RPG_API ARPGPlayerCharacter : public ARPGCharacterBase
{
	GENERATED_BODY()

public:
	ARPGPlayerCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void BeginPlay() override;

	void UseAbilityAtSlot(int32 Slot);
	void UseAbilitySlot_Primary();	

protected:

	void RotateCameraLeft();
	void RotateCameraRight();
	void HandleCameraRotation(float DeltaTime);


	void SetSlot1() { AbilitySlot = 0; UseAbilityAtSlot(0); }
	void SetSlot2() { AbilitySlot = 1; UseAbilityAtSlot(1); }
	void SetSlot3() { AbilitySlot = 2; UseAbilityAtSlot(2); }
	void SetSlot4() { AbilitySlot = 3; UseAbilityAtSlot(3); }

protected:

	UPROPERTY(VisibleAnywhere)
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* PlayerCamera;

	class ARPGEnemyCharacter* EnemyChar;

public:

	//virtual void StartAbilitySlotPrimary() override;

private:

	// Camera
	int RotateCamera;
	float CameraCurrentYaw;
	float CameraTargetYaw;


};
