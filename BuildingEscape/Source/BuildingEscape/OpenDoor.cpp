// Copyright is mine 2016

#include "BuildingEscape.h"
#include "OpenDoor.h"


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	Owner = GetOwner();	//Find the owning actor
	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();//pawn is a actor

}

void UOpenDoor::OpenDoor()
{
	//Set the door rotation
	Owner->SetActorRotation(FRotator(0.0f, OpenAngle, 0.0f));
}


void UOpenDoor::CloseDoor()
{
	Owner->SetActorRotation(FRotator(0.0f, 90.f, 0.0f));
}
// Called every frame
void UOpenDoor::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// Poll the trigger volume every frame 
	// If the ActorThatOpens is in the volume
	if (PressuePlate->IsOverlappingActor(ActorThatOpens)) 
	{
		//Counter = 0.f;
		OpenDoor();
		LastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}
	
	if (GetWorld()->GetTimeSeconds() - LastDoorOpenTime >DoorCloseDelay)
	{
		CloseDoor();
	}

	// Check if its time to close door
}

