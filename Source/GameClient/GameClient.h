#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/TextBlock.h"
#include "Components/EditableText.h"
#include "Components/ListView.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Animation/AnimInstance.h"
#include "NetClient.h"

#define MaxChatLength 2048

enum class Protocol
{
	Unknown = 0,
	ReqDummyInfo,
	ResDummyInfo,
	MoveToLocation,
	Chat,
	InSight,
	OutOfSight,
};