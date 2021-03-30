#pragma once
#include "GameClient.h"
#include "Blueprint/UserWidget.h"
#include "Dummy.h"
#include "DummyUI.generated.h"

UCLASS()
class GAMECLIENT_API UDummyUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:
	inline void SetOwner(class ADummy* Dummy)
	{
		dummyPtr_ = Dummy;
	}

private:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* index_ = nullptr;							// 매쉬위에 출력될 식별값 텍스트

private:
	TWeakObjectPtr< class ADummy > dummyPtr_ = nullptr;		// 더미 정보
};
