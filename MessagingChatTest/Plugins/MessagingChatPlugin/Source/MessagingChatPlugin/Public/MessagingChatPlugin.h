// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FMessagingChatPluginModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
	
	// Plugin Commands
	TSharedPtr<FUICommandList> PluginCommands;

	void AddToolbarButton(FToolBarBuilder& Builder);
	void AddMenuEntry(FMenuBuilder& MenuBuilder);

	void FillSubmenu(FMenuBuilder& MenuBuilder);
	TSharedRef<SWidget> FillComboButton(TSharedPtr<FUICommandList> Command);	
	TSharedRef<SDockTab> OnSpawnChatWindow1(const FSpawnTabArgs& SpawnTabArgs);
	TSharedRef<SDockTab> OnSpawnChatWindow2(const FSpawnTabArgs& SpawnTabArgs);

	void OnChat1ButtonClick();
	void OnChat2ButtonClick();
	
	void OnTabClosed(TSharedRef<SDockTab> Tab);
};
