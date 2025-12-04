#include "MyCustomEditor.h"

#define LOCTEXT_NAMESPACE "FMyCustomEditorModule"

void FMyCustomEditorModule::StartupModule()
{
}

void FMyCustomEditorModule::ShutdownModule()
{
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FMyCustomEditorModule, MyCustomEditor)
