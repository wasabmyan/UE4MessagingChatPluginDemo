// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SlateBasics.h"
#include "SlateExtras.h"

/**
 * 
 */
class ChatWindow : public SCompoundWidget
{
public:	
	TSharedRef<STextBlock> DefaulTextBlock = SNew(STextBlock);
	TWeakPtr<class FMessagingChatPluginModule> ChatPluginModule;
public:
	
	SLATE_BEGIN_ARGS(ChatWindow) {}
	SLATE_ARGUMENT(TWeakPtr<class FMessagingChatPluginModule>, ChatPluginModule)
	SLATE_END_ARGS()

	// widget construction
	void Construct(const FArguments& InArgs);	
	

};
