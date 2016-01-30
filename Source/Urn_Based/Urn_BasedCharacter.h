// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/Character.h"
#include "Urn_BasedCharacter.generated.h"


UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class EActionType
{
	AT_WALK 		UMETA(DisplayName = "Walk"),
	AT_RUN 			UMETA(DisplayName = "Run"),
	AT_ATTACK		UMETA(DisplayName = "Attack")
};

UENUM(BlueprintType)
enum class EAttackType : uint8 {
	ATT_MELEE 		UMETA(DisplayName = "Melee"),
	ATT_RANGED 		UMETA(DisplayName = "Ranged"),
	ATT_MAGIC 		UMETA(DisplayName = "Magic")
};


USTRUCT(BlueprintType)
struct FAttackInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
		EAttackType attackType;

	UPROPERTY()
		int32 attackStrength;

	UPROPERTY()
		AActor* attackingActor;

	//Set Attack Strength
	void SetAttackStrength(const int32 AttackStrength_)
	{
		attackStrength = AttackStrength_;
	}
	//Get Attack Strength
	int32 GetAttackStrength() {
		return attackStrength;
	}

	//Get Attacking Actor
	AActor* GetAttackingActor()
	{
		if (attackingActor->IsValidLowLevel())
			return attackingActor;
		else
			return NULL;
	}

	//Constructor
	FAttackInfo()
	{
		attackType = EAttackType::ATT_MELEE;
		attackStrength = 10;
		attackingActor = NULL;
	}
};



UCLASS(Blueprintable)
class AUrn_BasedCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;


public:
	AUrn_BasedCharacter();

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	
	// Set Stats
	UFUNCTION(BlueprintCallable, Category = "OnStart")
		void SetStartingStats(int32 hp = 10, int32 spd = 3, int32 ap = 3, int32 prw = 10, int32 acc = 10, int32 str = 10, int32 end = 10, int32 agi = 10, int32 wll = 10, int32 intel = 10, int32 arm = 10, int32 sz = 3);


	// Hit Point Management

	UFUNCTION(BlueprintCallable, Category = "Health")
		void AddHealth(int32 deltaHP);
	UFUNCTION(BlueprintCallable, Category = "Health")
		void OutOfHealth();

	//Damage Calculations

	UFUNCTION(BlueprintCallable, Category = "Damage")
		virtual void CalculateDamageTaken(FAttackInfo attackInfo);

	// Action Points

	UFUNCTION(BlueprintCallable, Category = "Actions")
		bool PerformAction(EActionType Action_, int32 APCost_);
	UFUNCTION(BlueprintCallable, Category = "Actions")
		bool CanSpendActionPoints(int32 APCost_);
	UFUNCTION(BlueprintCallable, Category = "Actions")
		void SpendActionPoints(int32 APSpent_);
	UFUNCTION(BlueprintCallable, Category = "Actions")
		void RefreshActionPoints();




	// Properties - Character Statistics

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Stats")
		int32 hitPoints;        // How much health you have left before dying
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Stats")
		int32 maxHitPoints;     // Maximum health you can heal back up to
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Stats")
		int32 speed;            // How far you can move in meters per Action Point
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Stats")
		int32 actionPoints;	    // Action Points allow you to take actions per turn
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Stats")
		int32 maxActionPoints;  // Action Points gained per turn
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Stats")
		int32 powerPoints;      // Power points allow you to cast spells, each spell has a specific power point cost
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Stats")
		int32 maxPowerPoints;   // How many Power points you can have total
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Stats")
		int32 prowess;          // Determines likelihood to hit and be hit in melee
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Stats")
		int32 accuracy;         // Determines likelihood to hit enemies at range
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Stats")
		int32 strength;         // Determines power with which you hit enemies in melee
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Stats")
		int32 endurance;        // Determines how resistant you are to status effects
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Stats")
		int32 agility;          // Determines how well you can dodge attacks that reflexes would assist with
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Stats")
		int32 willpower;        // Determines likelihood you are to retreat and how many Power Points you regenerate each turn
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Stats")
		int32 intelligence;     // Determines strength of spells
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Stats")
		int32 armour;           // Determines how resistant to damage you are
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Stats")
		int32 size;             // Determines how big you are, therefore what you can hide behind




};

