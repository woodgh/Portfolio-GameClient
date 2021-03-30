#pragma once
#include "CoreMinimal.h"
#include "NetPlay.h"

DECLARE_DELEGATE_RetVal_OneParam(bool, Delivery, NetPlay::Packet*);

class GAMECLIENT_API FNetClient : public NetPlay::IEventHandler
{
public:
	FNetClient() = default;

	virtual ~FNetClient() = default;

public:
	template< typename... FArgs >
	bool Connect(const FString& Address, unsigned short Port, FArgs... Args)
	{
		if (NetPlay::CreateClient(&client_) == false)
			return false;

		if (client_->Connect(TCHAR_TO_UTF8(*Address), Port, this) == false)
			return false;

		delivery_.BindUObject(Args...);

		return true;
	}

	void Update(void);

	bool Shutdown(void);

	bool Send(NetPlay::Packet* SendPacket);

public:
	virtual bool OnJoin(NetPlay::RemoteID* RemoteID) override;

	virtual bool OnDelivery(NetPlay::RemoteID* RemoteID, NetPlay::Packet* Packet, void* UserData) override;

	virtual bool OnLeave(NetPlay::RemoteID* RemoteID, int Reason) override;

private:
	class NetPlay::Client* client_ = nullptr;

	class NetPlay::RemoteID* remoteID_ = nullptr;

	Delivery delivery_;
};
