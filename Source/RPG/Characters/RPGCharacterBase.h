// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RPGCharacterBase.generated.h"

class UAnimMontage;
class UAbilityBase;
class AWeaponBase;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnApplyDamage, float, Damage, ARPGCharacterBase*, Instigator, ARPGCharacterBase*, Target);

DECLARE_MULTICAST_DELEGATE(FOnStatChanged);

USTRUCT(BlueprintType)
struct FStat
{
	GENERATED_BODY()

public:
	FStat()
		: Base(0)
		, Min(0)
		, Max(0)
		, Bonus(0)
		, Actual(0)
	{ }

	FStat(float Value)
		: Base(Value)
		, Min(0)
		, Max(Value)
		, Bonus(0)
		, Actual(Value)
	{ }

	FOnStatChanged OnStatChanged;

	FORCEINLINE void Update(float Value) {
		Actual += Value;
		Min += Value;
		Max += Value;
	}
	FORCEINLINE void Set(float Value) { Actual = Min = Max = Value; }
	FORCEINLINE float Get() const { return Actual; }

	FORCEINLINE void UpdateMin(float Value) { Min += Value; }
	FORCEINLINE void SetMin(float Value) { Min = Value; }
	FORCEINLINE float GetMin() const { return Min; }

	FORCEINLINE void UpdateMax(float Value) { Max += Value; }
	FORCEINLINE void SetMax(float Value) { Max = Value; }
	FORCEINLINE float GetMax() const { return Max; }

	FORCEINLINE void UpdateBonus(float Value) { 
		Bonus += Value; 
		OnStatChanged.Broadcast();
	}
	FORCEINLINE void SetBonus(float Value) { Bonus = Value; }
	FORCEINLINE float GetBonus() const { return Bonus; }

private:
	float Base;
	float Min;
	float Max;
	float Bonus;
	float Actual;
};



UCLASS()
class RPG_API ARPGCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	ARPGCharacterBase();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:


	virtual void ApplyDamageInstant(ARPGCharacterBase* DamageCauser);

	UFUNCTION(BlueprintCallable)
	void ApplyNormalDamage(const int32& InDamage);

	virtual void PrimaryAttack();

	void ResetCooldown();

	UFUNCTION(BlueprintCallable)
	void RotateTowardsEnemy(ARPGCharacterBase* Target);

	FORCEINLINE uint8 GetCharacterLevel() { return CharacterLevel; }

public:

	uint8 CharacterLevel;

	FStat	Resource;
	FStat	Health;
	FStat	AttackPower;
	FStat	CriticalChance;
	FStat	Damage;
	FStat	AttackRange;
	FStat	AttackSpeed;
	
protected:

	UAnimInstance* AnimInstance;

	// MONTAGES
	//////////////////////////////////////////////////////////////////////////////////////////////////
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Combat)
	UAnimMontage* PrimaryAttackMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Combat)
	UAnimMontage* PrimaryAttackCombo1Montage;
	////////////////////////////////////////////////////////////////////////////////////////////////////


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<AWeaponBase>> WeaponsClass;
	TArray<AWeaponBase*> Weapons;

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<UAbilityBase>> AbilitiesClass;
	TArray<UAbilityBase*> Abilities;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UAbilityBase> AilityPrimaryClass;
	UAbilityBase* AbilitySlotPrimary;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UAbilityBase> AilitySecondaryClass;
	UAbilityBase* AbilitySlotSecondary;
	

	UPROPERTY(BlueprintReadWrite)
	TArray<ARPGCharacterBase*> CharactersHit;


	int32 AbilitySlot;
public:

	bool bPlayerIsIdle;

	virtual void InitializeAbilities();

	//virtual void UseAbilityAtSlot(int32 Slot);

	//virtual void UseAbilitySlot_Primary();

public:

	
	UFUNCTION(BlueprintCallable)
	float GetAttackSpeed() const { return AttackSpeed.Get(); }

	UFUNCTION(BlueprintCallable)
	int32 GetMinDamage() const {return Damage.GetMin(); }

	UFUNCTION(BlueprintCallable)
	void SetMinDamage(int32 Value) { Damage.SetMin(Value); }
	
	UFUNCTION(BlueprintCallable)
	int32 GetMaxDamage() const { return Damage.GetMax(); }

	UFUNCTION(BlueprintCallable)
	TArray<ARPGCharacterBase*> GetCharactersHit() const { return CharactersHit; }

	UFUNCTION(BlueprintCallable)
	void AddCharacterHit(ARPGCharacterBase* CharacterHit) { CharactersHit.Add(CharacterHit); }

	UFUNCTION(BlueprintCallable)
	void ClearCharactersHit() { CharactersHit.Empty(); }


private:

	void CheckDeathCondition();

	void _InitializeAbilityPirimary();

	void _InitializeAbilitySecondary();

	int PrimaryAttackCombo = 0;

	bool bIsAbilityOnCooldown;
	FTimerHandle Ability_1_TimerHandle;

public:

	//UFUNCTION(BlueprintCallable, BlueprintAssignable)
	//FOnApplyDamage OnApplyDamage(float Damage, ARPGCharacterBase* Instigator, ARPGCharacterBase* Target);


	FOnStatChanged OnStatChanged;
		
	UPROPERTY(BlueprintReadWrite)
	bool bIsAttacking;

	UPROPERTY(BlueprintReadWrite)
	bool bWasHit;

	UPROPERTY(BlueprintReadWrite)
	int32 TargetHits;

	FHitResult MouseHit;
};
