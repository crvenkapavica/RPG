// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponBase.generated.h"



DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnItemAdded);

UCLASS()
class RPG_API AWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AWeaponBase();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

	UFUNCTION()
	void ActorEndOverlap(AActor* OverlappedActor, AActor* OtherActor);

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UCapsuleComponent* CapsuleComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USphereComponent* Root;

private:

	class ARPGPlayerCharacter* Player;
};
