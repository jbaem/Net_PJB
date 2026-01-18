#include "Item/ScoreItemSpawner.h"

#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "NavigationSystem.h"

AScoreItemSpawner::AScoreItemSpawner()
{
	PrimaryActorTick.bCanEverTick = false;

	SpawnVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnVolume"));
	RootComponent = SpawnVolume;

	SpawnVolume->SetBoxExtent(FVector(500.0f, 500.0f, 500.0f));
}

void AScoreItemSpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

void AScoreItemSpawner::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	GetWorld()->GetTimerManager().ClearTimer(SpawnTimerHandle);

	Super::EndPlay(EndPlayReason);
}

void AScoreItemSpawner::StartSpawning()
{
	if (HasAuthority())
	{
		GetWorld()->GetTimerManager().SetTimer(
			SpawnTimerHandle,
			this,
			&AScoreItemSpawner::SpawnItems,
			SpawnInterval,
			true,
			SpawnDelay
		);
	}
}

void AScoreItemSpawner::StopSpawning()
{
	GetWorld()->GetTimerManager().ClearTimer(SpawnTimerHandle);
}

void AScoreItemSpawner::SpawnItems()
{
	for (int i = 0; i < SpawnCount; ++i)
	{
		SpawnEachItem();
	}
}

void AScoreItemSpawner::SpawnEachItem()
{
	if (!ScoreItemClass)
	{
		return;
	}

	FVector SpawnLocation = GetRandomPointInVolume();
	FRotator SpawnRotation = FRotator::ZeroRotator;
	
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	GetWorld()->SpawnActor<AActor>(
		ScoreItemClass,
		SpawnLocation,
		SpawnRotation,
		SpawnParams
	);
}

FVector AScoreItemSpawner::GetRandomPointInVolume() const
{
	FVector Origin = SpawnVolume->GetComponentLocation();
	FVector BoxExtent = SpawnVolume->GetScaledBoxExtent();

	return UKismetMathLibrary::RandomPointInBoundingBox(Origin, BoxExtent);
}
