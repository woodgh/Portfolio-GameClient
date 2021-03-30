// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameClient.h"
#include "Blueprint/UserWidget.h"
#include "Chat.generated.h"

/**
 * 
 */
UCLASS()
class GAMECLIENT_API UChat : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()
	
public:
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

private:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* msg_ = nullptr;		// 채팅 목록에 대한 각각의 텍스트
};
