using UnrealBuildTool;

public class MyCustomEditor : ModuleRules
{
	public MyCustomEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"UnrealEd",
			"UMG",
			"Slate",
			"SlateCore",
			"EditorStyle",
			"EditorWidgets",
			"AssetDefinition",
			"ToolMenus",
			"PropertyEditor",
			"BlueprintGraph",
			"GraphEditor",
			"KismetCompiler",
			"ApplicationCore",
			"InputCore"
		});
		
		PrivateDependencyModuleNames.AddRange(new string[] {
			"TP_CustomAssets"
		});
	}
 
}
