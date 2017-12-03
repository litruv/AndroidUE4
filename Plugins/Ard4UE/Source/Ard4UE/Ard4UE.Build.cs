// Some copyright should be here...

using UnrealBuildTool;
using System; // Console.WriteLine("");

public class Ard4UE : ModuleRules
{
    

    public Ard4UE(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;


        PublicAdditionalLibraries.Add(ModuleDirectory + "\\..\\..\\ThirdParty\\serial.lib");
        PublicIncludePaths.Add(ModuleDirectory + "\\..\\..\\ThirdParty\\serial\\include");

        PublicIncludePaths.AddRange(
			new string[] {
				"Ard4UE/Public"
				
				// ... add public include paths required here ...
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				"Ard4UE/Private",
				
				// ... add other private include paths required here ...
			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				
				// ... add other public dependencies that you statically link with here ...
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",

				// ... add private dependencies that you statically link with here ...	
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);


	}
}
