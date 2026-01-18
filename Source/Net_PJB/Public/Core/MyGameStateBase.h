#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"

#include "MyGameStateBase.generated.h"

UENUM(BlueprintType)
enum class EGameStateType : uint8
{
	WAITING		UMETA(DisplayName = "Waiting"),
	READY		UMETA(DisplayName = "Ready"),
	PLAYING		UMETA(DisplayName = "Playing")
};

UCLASS()
class NET_PJB_API AMyGameStateBase : public AGameStateBase
{
	GENERATED_BODY()

public:
	AMyGameStateBase();

	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable)
	void TestPlay();

protected:
	virtual void BeginPlay() override;
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(BlueprintCallable)
	void SetCurrentState(EGameStateType NewState);

	UFUNCTION()
	void SetRemainTime(float NewTime);

	UFUNCTION()
	void FinishRound();

	UFUNCTION()
	void OnRep_CurrentState();

	UFUNCTION()
	void OnRep_RemainTime();

public:
	UFUNCTION(BlueprintCallable)
	float GetRemainTime() const { return RemainTime; }

	UFUNCTION(BlueprintCallable)
	EGameStateType GetCurrentState() const { return CurrentState; }

protected:
	UPROPERTY(ReplicatedUsing = OnRep_CurrentState)
	EGameStateType CurrentState = EGameStateType::WAITING;

	UPROPERTY(ReplicatedUsing = OnRep_RemainTime)
	float RemainTime = 60.f;
};
