#pragma once
#include "GameClient.h"
#include "GameFramework/PlayerController.h"
#include "MainController.generated.h"

UCLASS()
class GAMECLIENT_API AMainController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AMainController();

public:
	virtual void SetupInputComponent() override;

	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual void Tick(float DeltaTime) override;

public:
	// �������� �Ľ��ϱ�
	bool OnDelivery(class NetPlay::Packet* Packet);

private:
	// ���� ���� �ޱ�
	bool ResDummyInfo(class NetPlay::Packet* Packet);

	// �þ߿� ����
	bool InSight(class NetPlay::Packet* Packet);

	// �þ߿� �־���
	bool OutOfSight(class NetPlay::Packet* Packet);

	// ä��
	bool OnChat(class NetPlay::Packet* Packet);

	// ä�ø�� (UI)
	void ChatMode(void);

private:
	// ä�� �޼��� �Է� �Ϸ� ó��
	UFUNCTION()
	void OnTextCommitted(const FText& Text, ETextCommit::Type CommitMethod);

private:
	UPROPERTY(VisibleAnywhere)
	TSubclassOf< class UMainHUD > ui_;		// HUD UI

	UPROPERTY(VisibleAnywhere)
	TSubclassOf< class UChat > chat_;		// ä�� UI

private:
	TUniquePtr< class FNetClient > client_;	// Ŭ���̾�Ʈ ��ü

	TMap< int, class ADummy* > dummyGroup_;	// �þ߿� ���� ���

	class UMainHUD* hud_ = nullptr;			// HUD ��ü
};
