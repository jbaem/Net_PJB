#include "UI/MyMainWidget.h"

#include "GameFramework/GameStateBase.h"
#include "Core/MyPlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TextBlock.h"
#include "Components/Border.h"
#include "UI/ScoreInfoWidget.h"

#include "Core/MyGameStateBase.h"

void UMyMainWidget::NativeConstruct()
{
	Super::NativeConstruct();

	GetWorld()->GetTimerManager().SetTimer(
		PlayerCheckTimer,
		this,
		&UMyMainWidget::FindAndBindPlayers,
		1.0f,
		true
	);

	FindAndBindPlayers();
}

void UMyMainWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	UpdateTimerText();

	WinnerWidget->SetVisibility(ESlateVisibility::Hidden);
	LoserWidget->SetVisibility(ESlateVisibility::Hidden);

	if (AMyGameStateBase* GS = GetWorld()->GetGameState<AMyGameStateBase>())
	{
		GS->OnGameStartDel.AddDynamic(this, &UMyMainWidget::HandleGameStart);
		GS->OnGameFinishDel.AddDynamic(this, &UMyMainWidget::HandleGameFinish);
	}

}

void UMyMainWidget::HandleGameStart()
{
	WinnerWidget->SetVisibility(ESlateVisibility::Hidden);
	LoserWidget->SetVisibility(ESlateVisibility::Hidden);
}

void UMyMainWidget::HandleGameFinish()
{
	AMyGameStateBase* GS = GetWorld()->GetGameState<AMyGameStateBase>();
	if (!GS)
	{
		return;
	}

	APlayerState* MyPS = GetOwningPlayerState();
	APlayerState* WinnerPS = GS->GetWinnerPlayerState();

	if (MyPS && WinnerPS)
	{
		if (MyPS == WinnerPS)
		{
			WinnerWidget->SetVisibility(ESlateVisibility::Visible);
		}
		else
		{
			LoserWidget->SetVisibility(ESlateVisibility::Visible);
		}
	}
}

void UMyMainWidget::UpdateMyName(const FString& InName)
{
	MyScoreInfo->UpdateName(InName);
}

void UMyMainWidget::UpdateMyScore(int32 InScore)
{
	MyScoreInfo->UpdateScore(InScore);
}

void UMyMainWidget::UpdateOtherName(const FString & InName)
{
	OtherScoreInfo->UpdateName(InName);
}

void UMyMainWidget::UpdateOtherScore(int32 InScore)
{
	OtherScoreInfo->UpdateScore(InScore);
}

void UMyMainWidget::SetCachedGameState(AMyGameStateBase* InGameStateBase)
{
	if(InGameStateBase)
	{
		CachedGameState = InGameStateBase;
	}
}

void UMyMainWidget::UpdateTimerText()
{
	if(!CachedGameState.IsValid())
	{
		AMyGameStateBase* GS = Cast<AMyGameStateBase>(UGameplayStatics::GetGameState(GetWorld()));
		SetCachedGameState(GS);
	}
	else
	{
		int32 RemainTimeInt = FMath::CeilToInt(CachedGameState->GetRemainTime());
		MainTimer->SetText(FText::AsNumber(RemainTimeInt));
	}
}

void UMyMainWidget::FindAndBindPlayers()
{
	AGameStateBase* GS = UGameplayStatics::GetGameState(GetWorld());
	if (!GS)
	{
		return;
	}
	APlayerState* OwningPS = GetOwningPlayerState();

	for (APlayerState* PS : GS->PlayerArray)
	{
		AMyPlayerState* MyPS = Cast<AMyPlayerState>(PS);
		if (!MyPS)
		{
			continue;
		}

		if (MyPS == OwningPS)
		{
			UpdateMyName(MyPS->GetMyName());
			UpdateMyScore(MyPS->GetMyScore());

			MyScoreInfo->UpdateName(MyPS->GetMyName());
			MyScoreInfo->UpdateScore(MyPS->GetMyScore());

			if(!MyPS->OnNameChangedDel.IsAlreadyBound(this, &UMyMainWidget::UpdateMyName))
			{
				MyPS->OnNameChangedDel.AddDynamic(this, &UMyMainWidget::UpdateMyName);
			}
			if(!MyPS->OnScoreChangedDel.IsAlreadyBound(this, &UMyMainWidget::UpdateMyScore))
			{
				MyPS->OnScoreChangedDel.AddDynamic(this, &UMyMainWidget::UpdateMyScore);
			}
		}
		else
		{
			UpdateOtherName(MyPS->GetMyName());
			UpdateOtherScore(MyPS->GetMyScore());

			if(!MyPS->OnNameChangedDel.IsAlreadyBound(this, &UMyMainWidget::UpdateOtherName))
			{
				MyPS->OnNameChangedDel.AddDynamic(this, &UMyMainWidget::UpdateOtherName);
			}
			if(!MyPS->OnScoreChangedDel.IsAlreadyBound(this, &UMyMainWidget::UpdateOtherScore))
			{
				MyPS->OnScoreChangedDel.AddDynamic(this, &UMyMainWidget::UpdateOtherScore);
			}
		}
	}
}

