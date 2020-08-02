// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MessagingData.generated.h"


USTRUCT()
struct FChatMessage
{
	GENERATED_BODY()

	FString Nickname;
	FString Message;
	FChatMessage() = default;
	FChatMessage(const FString& nick, const FString& message) : Nickname(nick), Message(message) {}
};

