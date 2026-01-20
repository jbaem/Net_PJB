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

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameStartDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameFinishDelegate);

UCLASS()
class NET_PJB_API AMyGameStateBase : public AGameStateBase
{
	GENERATED_BODY()

public:
	AMyGameStateBase();

	virtual void Tick(float DeltaSeconds) override;

	FOnGameStartDelegate OnGameStartDel;
	FOnGameFinishDelegate OnGameFinishDel;

protected:
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	UFUNCTION(BlueprintCallable)
	void StartRound(float InRoundTime);

	UFUNCTION(BlueprintCallable)
	float GetRemainTime() const { return RemainTime; }

	UFUNCTION(BlueprintCallable)
	EGameStateType GetCurrentState() const { return CurrentState; }

	UFUNCTION()
	APlayerState* GetWinnerPlayerState() const { return WinnerPlayerState; }

protected:
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

protected:
	UPROPERTY(ReplicatedUsing = OnRep_CurrentState)
	EGameStateType CurrentState = EGameStateType::WAITING;

	UPROPERTY(Replicated, BlueprintReadOnly, Category = "My|Result")
	TObjectPtr<APlayerState> WinnerPlayerState = nullptr;

	UPROPERTY(ReplicatedUsing = OnRep_RemainTime)
	float RemainTime = 60.f;
};
