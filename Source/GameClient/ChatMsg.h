// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameClient.h"
#include "UObject/NoExportTypes.h"
#include "ChatMsg.generated.h"

/**
 * 
 */
UCLASS()
class GAMECLIENT_API UChatMsg : public UObject
{
	GENERATED_BODY()
	
public:
	inline int32 GetIndex(void) 
	{
		return index_;
	}

	inline void SetIndex(int32 Index)
	{
		index_ = Index;
	}

	inline const FString& GetMsg(void)
	{
		return msg_;
	}

	inline void SetMsg(const FString& Msg)
	{
		msg_ = Msg;
	}

private:
	int32 index_ = 0;

	FString msg_;
};
