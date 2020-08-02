// Copyright Epic Games, Inc. All Rights Reserved.

#include "MessagingChatPlugin.h"
#include "MessagingChatPluginCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "ChatWindow.h"

static const FName ChatWindowPluginTabName1("ChatWindowPlugin1");
static const FName ChatWindowPluginTabName2("ChatWindowPlugin2");

#define LOCTEXT_NAMESPACE "FMessagingChatPluginModule"

void FMessagingChatPluginModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	// Register Messaging Chat command
	FMessagingChatPluginCommands::Register();

	// Initialize Plugin Commands
	PluginCommands = MakeShareable(new FUICommandList);
	// Mapping Messaging Commands with action delegates
	PluginCommands->MapAction(
		FMessagingChatPluginCommands::Get().ChatCommand1,
		FExecuteAction::CreateRaw(this, &FMessagingChatPluginModule::OnChat1ButtonClick)
	);
	PluginCommands->MapAction(
		FMessagingChatPluginCommands::Get().ChatCommand2,
		FExecuteAction::CreateRaw(this, &FMessagingChatPluginModule::OnChat2ButtonClick)
	);


	// Get Level Editor Module of the editor
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");

	// Create FExtender and add new toolbar extension part
	TSharedPtr<FExtender> NewToolbarExtender = MakeShareable(new FExtender);
	NewToolbarExtender->AddToolBarExtension("Settings",
		EExtensionHook::After,
		PluginCommands,
		FToolBarExtensionDelegate::CreateRaw(this, &FMessagingChatPluginModule::AddToolbarButton)
	);
	
	// Create FExtender and add new menu extension part
	TSharedPtr<FExtender> NewMenuExtender = MakeShareable(new FExtender);
	NewMenuExtender->AddMenuExtension("LevelEditor",
		EExtensionHook::After,
		PluginCommands,
		FMenuExtensionDelegate::CreateRaw(this, &FMessagingChatPluginModule::AddMenuEntry)
	);

	// Add the extender to the toolbar
	LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(NewToolbarExtender);
	// Add the extender to the menu bar
	LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(NewMenuExtender);	

	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(ChatWindowPluginTabName1, FOnSpawnTab::CreateRaw(this, &FMessagingChatPluginModule::OnSpawnChatWindow1))
		.SetDisplayName(LOCTEXT("FMessagingChatPluginTabTitle1", "Chat 1"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);

	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(ChatWindowPluginTabName2, FOnSpawnTab::CreateRaw(this, &FMessagingChatPluginModule::OnSpawnChatWindow2))
		.SetDisplayName(LOCTEXT("FMessagingChatPluginTabTitle2", "Chat 2"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
	
}

void FMessagingChatPluginModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.	

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(ChatWindowPluginTabName1);
	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(ChatWindowPluginTabName2);

	// Unregister the Messaging Chat command
	FMessagingChatPluginCommands::Unregister();
}


// Add new button to the toolbar
void FMessagingChatPluginModule::AddToolbarButton(FToolBarBuilder& Builder)
{

	FUIAction TempCompileOptionsCommand;

	Builder.AddComboButton(TempCompileOptionsCommand,
		FOnGetContent::CreateRaw(this, &FMessagingChatPluginModule::FillComboButton, PluginCommands),
		LOCTEXT("Chat", "Chat"),
		LOCTEXT("MessagingChatPlugin", "Messaging Chat Plugin"),
		TAttribute<FSlateIcon>(),
		false
		);
}

// Add submenu
void FMessagingChatPluginModule::AddMenuEntry(FMenuBuilder& MenuBuilder)
{
	MenuBuilder.BeginSection("CustomMenu", TAttribute<FText>(FText::FromString("TestMenu")));

	//MenuBuilder.AddMenuEntry(FMessagingChatPluginCommands::Get().ChatCommand);
	MenuBuilder.AddSubMenu(FText::FromString("Chat"), 
		FText::FromString("Messaging Chat Plugin"),
		FNewMenuDelegate::CreateRaw(this, &FMessagingChatPluginModule::FillSubmenu)
		);
	MenuBuilder.EndSection();
}


// Add menu entries to the sub menu
void FMessagingChatPluginModule::FillSubmenu(FMenuBuilder& MenuBuilder)
{
	MenuBuilder.AddMenuEntry(FMessagingChatPluginCommands::Get().ChatCommand1);
	MenuBuilder.AddMenuEntry(FMessagingChatPluginCommands::Get().ChatCommand2);
}

TSharedRef<SWidget> FMessagingChatPluginModule::FillComboButton(TSharedPtr<FUICommandList> Commands)
{
	FMenuBuilder MenuBuilder(true, Commands);

	MenuBuilder.AddMenuEntry(FMessagingChatPluginCommands::Get().ChatCommand1);
	MenuBuilder.AddMenuEntry(FMessagingChatPluginCommands::Get().ChatCommand2);

	return MenuBuilder.MakeWidget();
}

TSharedRef<SDockTab> FMessagingChatPluginModule::OnSpawnChatWindow1(const FSpawnTabArgs& SpawnTabArgs)
{		
	TSharedRef<SChatWindow> TempChatWindow = SNew(SChatWindow);

	TSharedRef<SDockTab> SpawnedTab = SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			// Tab contents
			TempChatWindow
		];	
	

	return SpawnedTab;
}

TSharedRef<SDockTab> FMessagingChatPluginModule::OnSpawnChatWindow2(const FSpawnTabArgs& SpawnTabArgs)
{
	TSharedRef<SChatWindow> TempChatWindow = SNew(SChatWindow);

	TSharedRef<SDockTab> SpawnedTab = SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			// Tab contents
			TempChatWindow
		];


	return SpawnedTab;
}

void FMessagingChatPluginModule::OnChat1ButtonClick()
{
	FGlobalTabmanager::Get()->InvokeTab(ChatWindowPluginTabName1);
}

void FMessagingChatPluginModule::OnChat2ButtonClick()
{
	FGlobalTabmanager::Get()->InvokeTab(ChatWindowPluginTabName2);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FMessagingChatPluginModule, MessagingChatPlugin)