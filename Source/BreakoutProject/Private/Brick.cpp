#include "Brick.h"
#include "Components/StaticMeshComponent.h"

// Constructor
ABrick::ABrick()
{
    // Enable ticking
    PrimaryActorTick.bCanEverTick = false;

    // Create the mesh component
    BrickMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BrickMesh"));
    RootComponent = BrickMesh;
}

// Called when the game starts or when spawned
void ABrick::BeginPlay()
{
    Super::BeginPlay();
}

// Called every frame (not used for bricks, but kept for extensibility)
void ABrick::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

// Handle brick destruction
void ABrick::DestroyBrick()
{
    Destroy(); // Destroy the brick actor
}
