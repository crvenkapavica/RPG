// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectileBase.generated.h"

class ARPGCharacterBase;

UCLASS()
class RPG_API AProjectileBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AProjectileBase();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	FORCEINLINE void SetSpeed(float Speed) { ProjectileSpeed = Speed; }
	FORCEINLINE void SetTarget(ARPGCharacterBase* InTarget) { Target = InTarget; }

	float radius = 1.0f;
	

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* ProjectileMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UParticleSystemComponent* Particles;

private:

	void Interpolate(float DeltaTime);

	ARPGCharacterBase* Target;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float ProjectileSpeed;
};
