// Fill out your copyright notice in the Description page of Project Settings.


#include "MessagingChatPluginCommands.h"
#include "MessagingChatPlugin.h"

#define LOCTEXT_NAMESPACE "FMessagingChatPluginModule"

void FMessagingChatPluginCommands::RegisterCommands()
{
	UI_COMMAND(ChatCommand1, "Chat 1", "Messaging Window 1", EUserInterfaceActionType::Button, FInputGesture());
	UI_COMMAND(ChatCommand2, "Chat 2", "Messaging Window 2", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
