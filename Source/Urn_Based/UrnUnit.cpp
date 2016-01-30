// Fill out your copyright notice in the Description page of Project Settings.

#include "Urn_Based.h"
#include "UrnUnit.h"


// Sets default values
AUrnUnit::AUrnUnit()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AUrnUnit::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AUrnUnit::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void AUrnUnit::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}


// Set Starting Stats

void AUrnUnit::SetStartingStats(int32 hp, int32 spd, int32 ap, int32 prw, int32 acc, int32 str, int32 end, int32 agi, int32 wll, int32 intel, int32 arm, int32 sz, int32 rng) {

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
	size = sz;             // Determines how big you are, therefore what you can hide behind
	range = rng;			// Range of your default attack


}


/// Hit Point Management

void AUrnUnit::AddHealth(int32 deltaHealth) {

	hitPoints += deltaHealth;
	if (hitPoints > maxHitPoints)
		hitPoints = maxHitPoints;
	else if (hitPoints <= 0)
		OutOfHealth();

}


void AUrnUnit::OutOfHealth() {

	// Death prep procedures here

}


void AUrnUnit::CalculateDamageTaken(FAttackInfo attackInfo) {

	int32 damageTaken = attackInfo.GetAttackStrength(); // base damage sent by attacker
	damageTaken -= armour;                              // reduced by Armour
	AddHealth(-damageTaken);

}


// Action Point Management

bool AUrnUnit::PerformAction(EActionType Action_, int32 APCost_) {

	if (CanSpendActionPoints(APCost_)) {

		switch (Action_)
		{
		case EActionType::AT_WALK:
			break;
		case EActionType::AT_RUN:
			break;
		case EActionType::AT_ATTACK:
			break;
		default:
			break;
		}

		SpendActionPoints(APCost_);

		return true;

	}

	return false;

}


bool AUrnUnit::CanSpendActionPoints(int32 APCost_) {
	// Are my current actionPoints good to go?	
	return (actionPoints >= APCost_);
}


void AUrnUnit::SpendActionPoints(int32 APSpent_) {

	// Spend AP
	actionPoints = actionPoints - APSpent_;
	// Don't accidentally go negative
	if (actionPoints < 0)
		actionPoints = 0;

}

void AUrnUnit::RefreshActionPoints() {

	// Set Action Points back to maximum
	actionPoints = maxActionPoints;

}

