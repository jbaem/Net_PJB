#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "ScoreItemSpawner.generated.h"

UCLASS()
class NET_PJB_API AScoreItemSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	AScoreItemSpawner();

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

protected:
	UFUNCTION(BlueprintCallable)
	void StartSpawning();
	UFUNCTION(BlueprintCallable)
	void StopSpawning();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "My")
	TObjectPtr<class UBoxComponent> SpawnVolume;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "My|Spawn")
	float SpawnInterval = 3.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "My|Spawn")
	float SpawnDelay = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "My|Spawn")
	TSubclassOf<AActor> ScoreItemClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "My|Spawn")
	int32 SpawnCount = 5;

private:
	FTimerHandle SpawnTimerHandle;
	void SpawnItems();
	void SpawnEachItem();
	FVector GetRandomPointInVolume() const;
};
