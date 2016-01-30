// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "Urn_Based.h"
#include "Urn_BasedCharacter.h"

AUrn_BasedCharacter::AUrn_BasedCharacter()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->AttachTo(RootComponent);
	CameraBoom->bAbsoluteRotation = true; // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->RelativeRotation = FRotator(-60.f, 0.f, 0.f);
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->AttachTo(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

}


// Set Starting Stats

void AUrn_BasedCharacter::SetStartingStats(int32 hp, int32 spd, int32 ap, int32 prw, int32 acc, int32 str, int32 end, int32 agi, int32 wll, int32 intel, int32 arm, int32 sz) {

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


}


/// Hit Point Management

void AUrn_BasedCharacter::AddHealth(int32 deltaHealth) {

	hitPoints += deltaHealth;
	if (hitPoints > maxHitPoints)
		hitPoints = maxHitPoints;
	else if (hitPoints <= 0)
		OutOfHealth();

}


void AUrn_BasedCharacter::OutOfHealth() {

	// Death prep procedures here

}


void AUrn_BasedCharacter::CalculateDamageTaken(FAttackInfo attackInfo) {

	int32 damageTaken = attackInfo.GetAttackStrength(); // base damage sent by attacker
	damageTaken -= armour;                              // reduced by Armour
	AddHealth(-damageTaken);

}


// Action Point Management

bool AUrn_BasedCharacter::PerformAction(EActionType Action_, int32 APCost_) {

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


bool AUrn_BasedCharacter::CanSpendActionPoints(int32 APCost_) {
	// Are my current actionPoints good to go?	
	return (actionPoints >= APCost_);
}


void AUrn_BasedCharacter::SpendActionPoints(int32 APSpent_) {

	// Spend AP
	actionPoints = actionPoints - APSpent_;
	// Don't accidentally go negative
	if (actionPoints < 0)
		actionPoints = 0;

}

void AUrn_BasedCharacter::RefreshActionPoints() {

	// Set Action Points back to maximum
	actionPoints = maxActionPoints;

}
