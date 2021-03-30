#pragma once
#include "GameClient.h"
#include "Chat.h"
#include "ChatMsg.h"
#include "Blueprint/UserWidget.h"
#include "MainHUD.generated.h"

UCLASS()
class GAMECLIENT_API UMainHUD : public UUserWidget
{
	GENERATED_BODY()
	
public:
	using FTextCommitted = UEditableText::FOnEditableTextCommittedEvent;

public:
	void SetActorInfo(FVector& Location, FVector& Rotation, FVector& Velocity, float DeltaTime);

	void SetChatMode(void);

	void AddChat(UChatMsg* Msg);

	void ClearChat(void);

public:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:
	inline void SetTextCommitted(FTextCommitted& Delegate)
	{
		if (input_)
			input_->OnTextCommitted = Delegate;
	}

private:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* location_ = nullptr;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* rotation_ = nullptr;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* velocity_ = nullptr;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* deltaTime_ = nullptr;

	UPROPERTY(meta = (BindWidget))
	UListView* history_ = nullptr;

	UPROPERTY(meta = (BindWidget))
	UEditableText* input_ = nullptr;

private:
	TArray< FString > items_;
};
