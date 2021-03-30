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
	// 더미 정보 지정하기
	void SetActorInfo(FVector& Location, FVector& Rotation, FVector& Velocity, float DeltaTime);

	// 채팅 모드 활성화
	void SetChatMode(void);

	// 채팅 이력 추가하기
	void AddChat(UChatMsg* Msg);

	// 채팅 입력 UI 초기화
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
	UTextBlock* location_ = nullptr;	// 위치 텍스트

	UPROPERTY(meta = (BindWidget))
	UTextBlock* rotation_ = nullptr;	// 방향 텍스트

	UPROPERTY(meta = (BindWidget))
	UTextBlock* velocity_ = nullptr;	// 속도 텍스트

	UPROPERTY(meta = (BindWidget))
	UTextBlock* deltaTime_ = nullptr;	// 델타타임

	UPROPERTY(meta = (BindWidget))
	UListView* history_ = nullptr;		// 채팅 이력 리스트뷰

	UPROPERTY(meta = (BindWidget))
	UEditableText* input_ = nullptr;	// 채팅 입력부
};
