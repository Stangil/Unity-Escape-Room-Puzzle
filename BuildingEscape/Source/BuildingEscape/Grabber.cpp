// Copyright is mine 2016

#include "BuildingEscape.h"
#include "Grabber.h"

#define OUT//Using OUT allows us to remind ourselves that these parameters will be changed
// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	FindPhysicsHandleComponent();
	SetUpInputComponent();
}
/// Look for attached Physics Handle
void UGrabber::FindPhysicsHandleComponent()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	FString PhysicsHandleOwner = GetOwner()->GetName();
	if (PhysicsHandle)
	{
		// Physics handle is found
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Physics handle for %s not found! Add Physics Handler to Pawn"),
			*PhysicsHandleOwner)
	}
}
/// Look for attached input component (Only appears at runtime)
void UGrabber::SetUpInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("Input component found"))
			///Bind input action
			InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Input component for %s not found! Add Input component to Pawn"),
			*GetOwner()->GetName())
	}
}
/// Grab Stuff
void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("You are Grabbing Shit!!!"))
		/// LINE TRACE and see if we reach any actors with physics body collision channel set
		GetFirstPhysicsBodyInReach();
		///If we hit somethin then attach a physics handle
		// TODO attach physics handle
}
/// Release stuff
void UGrabber::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("You are Releasing Shit!!!"))
		// TODO release physics
}
// Called every frame
void UGrabber::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// if the physics handle is attached
		// move the object we are holding


}
const FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{
	/// Get player viewpoint this tick
	FVector PlayerViewPointLocation;
	FRotator PlaverViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,//Using OUT allows us to remind ourselves that these parameters will be changed
		OUT PlaverViewPointRotation
	);
	FVector LineTraceEnd = PlayerViewPointLocation + PlaverViewPointRotation.Vector() * Reach;
	/// Setup query parameters
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());
	/// Line -trace (AKA Ray-cast) out to reach distance
	FHitResult Hit;
	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		PlayerViewPointLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters
	);
	/// See what we hit
	AActor* ActorHit = Hit.GetActor();//create an actor from hit
	if (ActorHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("What we hit is %s "), *(ActorHit->GetName()))
	}
	return FHitResult();
}

