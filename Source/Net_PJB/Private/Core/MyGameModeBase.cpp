#include "Core/MyGameModeBase.h"

#include "Core/MyPlayerState.h"
#include "Core/MyGameStateBase.h"

void AMyGameModeBase::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	if (AMyPlayerState* PS = NewPlayer->GetPlayerState<AMyPlayerState>())
	{
		PS->ResetMyScore();
		FString NewName = FString::Printf(TEXT("Player_%d"), GetNumPlayers());
		PS->SetMyName(NewName);
	}
}

void AMyGameModeBase::StartMyGame()
{
	if (AMyGameStateBase* GS = GetGameState<AMyGameStateBase>())
	{
		if (GS->GetCurrentState() == EGameStateType::PLAYING)
		{
			return;
		}

		GS->StartRound(RoundTime);
	}
}
