#include "Core/MyGameStateBase.h"

#include "Net/UnrealNetwork.h"

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

void AMyGameStateBase::TestPlay()
{
	if (HasAuthority())
	{
		SetCurrentState(EGameStateType::PLAYING);
		OnRep_CurrentState();
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

void AMyGameStateBase::FinishRound()
{
	if (HasAuthority())
	{
		SetCurrentState(EGameStateType::WAITING);
	}
}

void AMyGameStateBase::OnRep_CurrentState()
{

}

void AMyGameStateBase::OnRep_RemainTime()
{

}
