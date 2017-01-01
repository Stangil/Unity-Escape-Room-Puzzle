// Copyright is mine 2016

#pragma once

#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoorEvent);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;
	UPROPERTY(BluePrintAssignable)
	FDoorEvent OnOpen;
	UPROPERTY(BluePrintAssignable)
	FDoorEvent OnClose;

private:
	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressuePlate = nullptr;
	UPROPERTY(EditAnywhere)
	float TriggerMass = 30.f;//can change in UE
	// The owning door
	AActor* Owner = nullptr;

	// Returns total mass in KG
	float GetTotalMassOfActorsOnPlate();
};
