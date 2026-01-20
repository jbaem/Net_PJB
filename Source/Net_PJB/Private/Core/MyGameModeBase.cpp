#include "Core/MyGameModeBase.h"

#include "Core/MyPlayerState.h"

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
