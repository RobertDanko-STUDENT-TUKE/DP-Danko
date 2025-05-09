#include "RayCast.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"

ARayCast::ARayCast(){
	PrimaryActorTick.bCanEverTick = true;
    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
}

void ARayCast::BeginPlay(){
	Super::BeginPlay();
}

void ARayCast::performRayCast(){
    // Set up the RayCast parameters
    FVector startPos = this->rayStart.IsZero() ? GetActorLocation() : this->rayStart; // Default to actor's location
    FVector endPos = ((GetActorUpVector() * this->rayLength) + startPos);

    FHitResult hitResult;

    // Perform the line trace
    FCollisionQueryParams traceParams;
    traceParams.AddIgnoredActor(this); // Ignore self

    bool bHit = GetWorld()->LineTraceSingleByChannel(hitResult, startPos, endPos, ECC_Visibility, traceParams);

    // Draw debug line
    DrawDebugLine(GetWorld(), startPos, endPos, bHit ? FColor::Red : FColor::Green, false, 1.0f, 0, 1.0f);

    //if (bHit) UE_LOG(LogTemp, Warning, TEXT("Hit: %s"), *hitResult.GetActor()->GetName());
}

void ARayCast::Tick(float DeltaTime){
	Super::Tick(DeltaTime);
	this->performRayCast();
}