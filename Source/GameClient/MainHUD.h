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
	// ���� ���� �����ϱ�
	void SetActorInfo(FVector& Location, FVector& Rotation, FVector& Velocity, float DeltaTime);

	// ä�� ��� Ȱ��ȭ
	void SetChatMode(void);

	// ä�� �̷� �߰��ϱ�
	void AddChat(UChatMsg* Msg);

	// ä�� �Է� UI �ʱ�ȭ
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
	UTextBlock* location_ = nullptr;	// ��ġ �ؽ�Ʈ

	UPROPERTY(meta = (BindWidget))
	UTextBlock* rotation_ = nullptr;	// ���� �ؽ�Ʈ

	UPROPERTY(meta = (BindWidget))
	UTextBlock* velocity_ = nullptr;	// �ӵ� �ؽ�Ʈ

	UPROPERTY(meta = (BindWidget))
	UTextBlock* deltaTime_ = nullptr;	// ��ŸŸ��

	UPROPERTY(meta = (BindWidget))
	UListView* history_ = nullptr;		// ä�� �̷� ����Ʈ��

	UPROPERTY(meta = (BindWidget))
	UEditableText* input_ = nullptr;	// ä�� �Էº�
};
