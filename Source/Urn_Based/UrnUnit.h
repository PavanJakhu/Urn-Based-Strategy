// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "UrnUnit.generated.h"


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
struct FUnitStats
{
	GENERATED_USTRUCT_BODY()

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
		int32 size;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Stats")
		int32 range;

	
	FUnitStats(int32 hp = 10, int32 spd = 3, int32 ap = 3, int32 prw = 10, int32 acc = 10, int32 str = 10, int32 end = 10, int32 agi = 10, int32 wll = 10, int32 intel = 10, int32 arm = 10, int32 sz = 3, int32 rng = 1) {
		// Death prep procedures here
		hitPoints = hp;			// How much health you have left before dying
		maxHitPoints = hp;		// Maximum health you can heal back up to
		speed = spd;					// How far you can move in meters per Action Point
		actionPoints = ap;	    // Action Points allow you to take actions per turn
		maxActionPoints = ap;  // Action Points gained per turn
		powerPoints = intel * 2;      // Power points allow you to cast spells, each spell has a specific power point cost
		maxPowerPoints = intel * 2;					// How many Power points you can have total
		prowess = prw;          // Determines likelihood to hit and be hit in melee
		accuracy = acc;         // Determines likelihood to hit enemies at range
		strength = str;         // Determines power with which you hit enemies in melee
		endurance = end;        // Determines how resistant you are to status effects
		agility = agi;          // Determines how well you can dodge attacks that reflexes would assist with
		willpower = wll;        // Determines likelihood you are to retreat and how many Power Points you regenerate each turn
		intelligence = intel;     // Determines strength of spells
		armour = arm;           // Determines how resistant to damage you are
		size = sz;
		range = rng;
	}

};


USTRUCT(BlueprintType)
struct FAttackInfo
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Stats")
		EAttackType attackType;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Stats")
		int32 attackStrength;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Stats")
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



UCLASS()
class URN_BASED_API AUrnUnit : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AUrnUnit();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	// Set Stats
	UFUNCTION(BlueprintCallable, Category = "OnStart")
		void SetStartingStats(int32 hp = 10, int32 spd = 3, int32 ap = 3, int32 prw = 10, int32 acc = 10, int32 str = 10, int32 end = 10, int32 agi = 10, int32 wll = 10, int32 intel = 10, int32 arm = 10, int32 sz = 3, int32 rng = 1);


	// Hit Point Management

	UFUNCTION(BlueprintCallable, Category = "Health")
		void AddHealth(int32 deltaHP);
	UFUNCTION(BlueprintCallable, Category = "Health")
		void OutOfHealth();

	//Damage Calculations

	UFUNCTION(BlueprintCallable, Category = "Damage")
		virtual int32 CalculateDamageTaken(FAttackInfo attackInfo);

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
		FUnitStats myStats;        // Contains all my stats	
	
};
