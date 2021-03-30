// Fill out your copyright notice in the Description page of Project Settings.


#include "Chat.h"
#include "ChatMsg.h"

void UChat::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	// 채팅 UI 목록에 대한 아이템 데이타 지정하기
	UChatMsg* Data = Cast< UChatMsg >(ListItemObject);

	if (Data == nullptr)
		return;

	if (msg_)
		msg_->SetText(FText::FromString(FString::Printf(TEXT("%6d: %s"), Data->GetIndex(), *Data->GetMsg())));
}