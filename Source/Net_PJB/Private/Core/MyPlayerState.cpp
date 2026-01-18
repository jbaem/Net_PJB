#include "Core/MyPlayerState.h"

#include "Net/UnrealNetwork.h"

#include "Player/MyCharacter.h"
#include "Blueprint/UserWidget.h"
#include "UI/MyHUD.h"
#include "UI/MyMainWidget.h"

AMyPlayerState::AMyPlayerState()
{
	bReplicates = true;
}

void AMyPlayerState::BeginPlay()
{
	Super::BeginPlay();

	ResetMyScore();
}

void AMyPlayerState::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (OnScoreChangedDel.IsBound())
	{
		OnScoreChangedDel.Clear();
	}

	if (OnNameChangedDel.IsBound())
	{
		OnNameChangedDel.Clear();
	}

	if (OnStateChangedDel.IsBound())
	{
		OnStateChangedDel.Clear();
	}

	Super::EndPlay(EndPlayReason);
}

void AMyPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMyPlayerState, ReadyType);
	DOREPLIFETIME(AMyPlayerState, MyScore);
	DOREPLIFETIME(AMyPlayerState, MyName);
}

void AMyPlayerState::SetReadyType(EReadyType NewReadyType)
{
	if(HasAuthority())
	{
		ReadyType = NewReadyType;
		OnStateChangedDel.Broadcast(ReadyType);
		OnRep_ReadyType();
	}
}

void AMyPlayerState::AddMyScore(int32 ScoreToAdd)
{
	if (HasAuthority())
	{
		MyScore += ScoreToAdd;
		OnScoreChangedDel.Broadcast(MyScore);
		OnRep_MyScore();
	}

}

void AMyPlayerState::ResetMyScore()
{
	if(HasAuthority())
	{
		MyScore = 0;
		OnScoreChangedDel.Broadcast(MyScore);
		OnRep_MyScore();
	}
}

void AMyPlayerState::SetMyName(const FString& NewName)
{
	if(HasAuthority())
	{
		MyName = NewName;
		OnNameChangedDel.Broadcast(MyName);
		OnRep_MyName();
	}
}

void AMyPlayerState::OnRep_ReadyType()
{
	
}

void AMyPlayerState::OnRep_MyScore()
{
	APlayerController* PC = GetPlayerController();
	if (PC && PC->IsLocalController())
	{
		AHUD* HUD = GetWorld()->GetFirstPlayerController()->GetHUD();
		AMyHUD* MyHUD = Cast<AMyHUD>(HUD);
		if(MyHUD)
		{
			UMyMainWidget* MainWidget = Cast<UMyMainWidget>(MyHUD->GetMainWidget());
			if(MainWidget)
			{
				//MainWidget->UpdateScoreText(MyScore);
			}
		}
	}
}

void AMyPlayerState::OnRep_MyName()
{
	
}
