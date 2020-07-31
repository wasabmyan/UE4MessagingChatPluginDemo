// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SlateBasics.h"
#include "EditorStyleSet.h"

class FMessagingChatPluginCommands : public TCommands<FMessagingChatPluginCommands>
{
public:
	FMessagingChatPluginCommands() : TCommands<FMessagingChatPluginCommands>
		(
			TEXT("MessagingChatPlugin"),
			NSLOCTEXT("Contexts", "MessagingChatPlugin", "MessagingChat Plugin"),
			NAME_None,
			FEditorStyle::GetStyleSetName()
			) {}

	virtual void RegisterCommands() override;

public:

	TSharedPtr<FUICommandInfo> ChatCommand1;
	TSharedPtr<FUICommandInfo> ChatCommand2;
};
