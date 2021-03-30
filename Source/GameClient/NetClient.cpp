#include "NetClient.h"

void FNetClient::Update(void)
{
	if (client_)
		client_->Update();
}

bool FNetClient::Shutdown(void)
{
	if (client_->Shutdown() == false)
		return false;

	client_->Release();

	return true;
}


bool FNetClient::Send(NetPlay::Packet* SendPacket)
{
	if (SendPacket == nullptr)
		return false;

	if (remoteID_ == nullptr)
		return false;

	if (remoteID_->Send(SendPacket) == false)
		return false;

	return true;
}

bool FNetClient::OnJoin(NetPlay::RemoteID* RemoteID)
{
	if (RemoteID == nullptr)
		return false;

	remoteID_ = RemoteID;

	GEngine->AddOnScreenDebugMessage(1, 2.0f, FColor::Green, TEXT("월드에 접속하였습니다."));

	return true;
}

bool FNetClient::OnLeave(NetPlay::RemoteID* RemoteID, int Reason)
{
	if (RemoteID == nullptr)
		return false;

	remoteID_ = nullptr;

	GEngine->AddOnScreenDebugMessage(1, 2.0f, FColor::Red, TEXT("월드에 접속 종료하였습니다."));

	return true;
}

bool FNetClient::OnDelivery(NetPlay::RemoteID* RemoteID, NetPlay::Packet* Packet, void* UserData)
{
	if (RemoteID == nullptr)
		return false;

	if (Packet == nullptr)
		return false;

	unsigned int Length = 0;

	if (Packet->Read(&Length) == false)
		return false;

	if (Length <= 0)
		return false;

	if (delivery_.Execute(Packet) == false)
		return false;

	return true;
}
