#include "Core/MyGameStateBase.h"

#include "Net/UnrealNetwork.h"
#include "Core/MyPlayerState.h"

AMyGameStateBase::AMyGameStateBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMyGameStateBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if(HasAuthority() && CurrentState == EGameStateType::PLAYING)
	{
		if(RemainTime > 0.f)
		{
			RemainTime -= DeltaSeconds;
			if(RemainTime < 0.f)
			{
				RemainTime = 0.f;
				FinishRound();
			}
		}
	}
}

void AMyGameStateBase::BeginPlay()
{
	Super::BeginPlay();
	
	SetCurrentState(EGameStateType::WAITING);
	SetRemainTime(60.f);
}

void AMyGameStateBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>&OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMyGameStateBase, CurrentState);
	DOREPLIFETIME(AMyGameStateBase, WinnerPlayerState);
	DOREPLIFETIME(AMyGameStateBase, RemainTime);
}

void AMyGameStateBase::SetCurrentState(EGameStateType NewState)
{
	if (HasAuthority())
	{
		CurrentState = NewState;
		OnRep_CurrentState();
	}
}

void AMyGameStateBase::SetRemainTime(float NewTime)
{
	if (HasAuthority())
	{
		RemainTime = NewTime;
		OnRep_RemainTime();
	}
}

void AMyGameStateBase::StartRound(float InRoundTime)
{
	if (HasAuthority())
	{
		RemainTime = InRoundTime;
		SetCurrentState(EGameStateType::PLAYING);
		OnRep_CurrentState();
	}
}

void AMyGameStateBase::FinishRound()
{
	if (HasAuthority())
	{
		FindWinner(); 
		SetCurrentState(EGameStateType::WAITING);
		OnRep_CurrentState();
	}
}

void AMyGameStateBase::FindWinner()
{
	AMyPlayerState* CurrentWinner = nullptr;
	int32 HighestScore = -1;

	for (APlayerState* PS : PlayerArray)
	{
		if (AMyPlayerState* MyPS = Cast<AMyPlayerState>(PS))
		{
			if (MyPS->GetMyScore() > HighestScore)
			{
				HighestScore = MyPS->GetMyScore();
				CurrentWinner = MyPS;
			}
			else if (MyPS->GetMyScore() == HighestScore)
			{
				CurrentWinner = nullptr;
			}
		}
	}
	WinnerPlayerState = CurrentWinner;
}

void AMyGameStateBase::OnRep_CurrentState()
{
	switch (CurrentState)
	{
	case EGameStateType::PLAYING:
		OnGameStartDel.Broadcast();
		break;
	case EGameStateType::WAITING:
		OnGameFinishDel.Broadcast();
		break;
	default:
		break;
	}
}

void AMyGameStateBase::OnRep_RemainTime()
{

}
