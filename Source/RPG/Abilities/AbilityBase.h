#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AbilityBase.generated.h"

class UAnimMontage;
class ARPGCharacterBase;
class AProjectileBase;
class UWorld;

USTRUCT(BlueprintType)
struct FAbilityBuff
{
	GENERATED_BODY()

	float Duration;
};

USTRUCT(BlueprintType)
struct FAbilityDebuff
{
	GENERATED_BODY()
};

USTRUCT(BlueprintType)
struct FAbilityAOE
{
	GENERATED_BODY()
};

USTRUCT(BlueprintType)
struct FAbilityPassive
{
	GENERATED_BODY()
};

USTRUCT(BlueprintType)
struct FAbilityActive
{
	GENERATED_BODY()
};

USTRUCT(BlueprintType)
struct FAbilityMobile
{
	GENERATED_BODY()
};

USTRUCT(BlueprintType)
struct FAbilityProjectile
{
	GENERATED_BODY()

public:

	//To more biti samo AActor, pa se v spell konstruktoru slaze.....
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AProjectileBase> ProjectileClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ProjectileSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float HitRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxTargets;
};

USTRUCT(BlueprintType)
struct FAbilitySpec
{
	GENERATED_BODY()

public:

	FAbilitySpec() {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FAbilityBuff		AbilityBuff;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FAbilityDebuff		AbilityDebuff;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FAbilityAOE			AbilityAOE;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FAbilityProjectile	AbilityProjectile;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FAbilityPassive		AbilityPassive;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FAbilityActive		AbilityActive;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FAbilityMobile		AbilityMobile;
};

UENUM(BlueprintType)
enum class EAbilityType : uint8
{
	EAT_Buff,
	EAT_Debuff,
	EAT_AOE,
	EAT_Projectile,
	EAT_Passive,
	EAT_Active,
	EAT_Mobile
};

UENUM(BlueprintType)
enum class EResourceType : uint8
{
	ERT_None,
	ERT_Mana,
	ERT_Rage,

	ERT_ETC
};

UENUM(BlueprintType)
enum class ETargetType : uint8
{
	ETT_None,
	ETT_Single,
	ETT_Multi
};

USTRUCT(BlueprintType)
struct FAbilityInfo
{
	GENERATED_BODY()

public:


	FAbilityInfo() {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EAbilityType AbilityType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ETargetType TargetType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EResourceType ResourceType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FAbilitySpec AbilitySpec;
};



/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class RPG_API UAbilityBase : public UObject
{
	GENERATED_BODY()

public:
	UAbilityBase();
	/*
	* ABILITY SPECIFICS
	*/
	//*****************************************
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FAbilityInfo AbilityInfo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAnimMontage* AbilityMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 AbilityResourceCost;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 AbilityCurrentLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 AbilityMaxLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AbilityCooldown;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AbilityRange;

	//******************************************
public:


protected:

	ARPGCharacterBase* Target;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<ARPGCharacterBase*> Targets;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ARPGCharacterBase* Instigator;

protected:
		
	virtual void UseAbility_Projectile();

	void SetAbilityInfo(FAbilityInfo& DefaultAbilityInfo);

	FAbilityInfo ConstructDefaultAbilityInfo(EAbilityType AbilityType, ETargetType TargetType, EResourceType ResourceType, FAbilitySpec& AbilitySpec);


public:

	//virtual bool TryUseAbility(UWorld* InWorld, ARPGCharacterBase* InInstigator, TArray<ARPGCharacterBase*> InTargets);
	virtual bool TryUseAbility(ARPGCharacterBase* InInstigator, ARPGCharacterBase* InTarget);


public:

	UFUNCTION(BlueprintCallable)
	FORCEINLINE FAbilityInfo GetAbilityInfo() const { return AbilityInfo; }

	UFUNCTION(BlueprintCallable)
	void BeginPlay();

	UFUNCTION()
	void Tick();

	float DeltaTime;

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "BeginPlay"))
	void ReceiveBeginPlay();

	FORCEINLINE bool GetIsAbilityOnCooldown() const { return bIsAbilityOnCooldown; }
	FORCEINLINE float GetRemainingCooldown() const { return RemainingCooldown; }

	FORCEINLINE bool IsInitialized() const { return bInitialized; }

	FString ErrorMessage;

	FTimerHandle CooldownTimerHandle;

private:

	bool bIsAbilityOnCooldown;

	float RemainingCooldown;

	bool bInitialized;

	ARPGCharacterBase* _Target;
	
private:
	
	void PostInitProperties() override;

	bool _CheckUsable();

	bool _PrepareAbility(ARPGCharacterBase* InInstigator, ARPGCharacterBase* InTarget);

	void _FinishAbility();

	void _ResetAbilityCooldown();
};
