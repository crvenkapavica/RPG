// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RPGPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class RPG_API ARPGPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	ARPGPlayerController();
protected:

	virtual void SetupInputComponent() override;
	void BeginPlay() override;
	void Tick(float DeltaTime) override;


	void SetTargetPressed();
	void SetTargetReleased();

	void UpdateTarget();


	void asd();

private:

	class ARPGPlayerCharacter* Player;

	bool bIsMousePressed;
};
