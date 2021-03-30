// Fill out your copyright notice in the Description page of Project Settings.


#include "Chat.h"
#include "ChatMsg.h"

void UChat::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	UChatMsg* Data = Cast< UChatMsg >(ListItemObject);

	if (Data == nullptr)
		return;

	if (msg_)
		msg_->SetText(FText::FromString(FString::Printf(TEXT("%6d: %s"), Data->GetIndex(), *Data->GetMsg())));
}