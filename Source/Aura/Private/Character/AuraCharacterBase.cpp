// Copyright of FrankCo


#include "Character/AuraCharacterBase.h"

AAuraCharacterBase::AAuraCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AAuraCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}


