# Custom Assets System - Unreal Engine 5.6

A student's C++ Unreal Engine project by SENHAJ Mehdi that demonstrates the creation of custom asset types with a complete editor integration. The system provides a custom data asset with visual node-based editing capabilities through an integrated graph editor.

## Features

- **Custom Data Asset**: `UMyCustomAsset` class with configurable properties (Name, Description, Value)
- **Asset Factory**: Automated creation of custom assets through the content browser
- **Visual Graph Editor**: Node-based editing interface for custom assets
- **Asset Type Definition**: Complete integration with Unreal Engine's asset system
- **Custom Graph Schema**: Drag-and-drop functionality with custom node types
- **Properties Panel**: Real-time property editing with automatic save functionality
- **Editor Integration**: Seamless integration with Unreal Engine's editor workflow

## Project Structure

```
TP_CustomAssets/
├── Source/TP_CustomAssets/             # Runtime module
│   ├── MyCustomAsset.h/.cpp            # Custom data asset class
│   ├── TP_CustomAssets.h/.cpp          # Main module implementation
│   └── TP_CustomAssets.Build.cs        # Build configuration
├── Source/MyCustomEditor/              # Editor-only module
│   ├── MyAssetEditor.h/.cpp            # Main asset editor toolkit
│   ├── MyAssetFactory.h/.cpp           # Asset creation factory
│   ├── MyAssetAssetDefinition.h/.cpp   # Asset type definition
│   ├── MyCustomGraph.h/.cpp            # Graph representation
│   ├── MyCustomGraphSchema.h/.cpp      # Graph interaction rules
│   ├── MyCustomGraphNode.h/.cpp        # Custom node implementation
│   ├── SMyCustomGraphNode.h/.cpp       # Node widget (Slate UI)
│   ├── SMyCustomGraphPin.h/.cpp        # Pin widget (Slate UI)
│   ├── MyCustomGraphDragDropAction.h/.cpp # Drag & drop functionality
│   └── MyCustomEditor.Build.cs         # Editor module build config
└── Content/                            # Unreal assets
    └── Test.uasset                     # Example custom asset
```

## Prerequisites

- **Unreal Engine 5.6** or later
- **Visual Studio 2022** (with C++ development tools)

## Setup Instructions

### 1. Generate Visual Studio Project Files

Right-click on `TP_CustomAssets.uproject` and select:
**"Generate Visual Studio project files"**

### 2. Build the Project

#### Visual Studio
1. Open `TP_CustomAssets.sln`
2. Set build configuration to **Development Editor**
3. Build the solution (Ctrl+Shift+B)

## Running the Project

1. Launch `TP_CustomAssets.uproject` in Unreal Editor

## How to Use

### Creating Custom Assets

1. **In Content Browser**: Right-click → **Miscellaneous** → **My Custom Asset**
2. **Name your asset** and press Enter
3. **Double-click** the created asset to open the custom editor

### Using the Custom Editor

Once a custom asset is opened, you'll see a multi-panel interface:

#### Graph Editor Panel
- **Visual node-based editing** environment
- **Drag and drop** nodes from the palette
- **Connect nodes** with pins to create relationships
- **Real-time visual feedback** for node connections

#### Properties Panel
- **Edit asset properties**: Name, Description, Value
- **Real-time updates** with automatic saving
- **Inspector-style** interface for detailed configuration

#### Palette Panel
- **Available node types** for the graph editor
- **Drag nodes** directly into the graph editor
- **Categorized tools** for easy navigation

### Asset Properties

Each custom asset contains:
- **Asset Name** (FString): Identifier for the asset
- **Description** (FText): Detailed description with localization support  
- **Value** (float): Numerical value for calculations or configurations

## Architecture Overview

### Runtime Module (TP_CustomAssets)
- Contains the core `UMyCustomAsset` class
- Inherits from `UDataAsset` for serialization and Blueprint integration
- Provides the fundamental data structure

### Editor Module (MyCustomEditor)
- **Asset Editor Toolkit**: Complete editing environment
- **Factory System**: Asset creation through content browser
- **Graph System**: Visual node-based editing
- **Slate UI Components**: Custom widgets for enhanced user experience

## Troubleshooting

### Compilation Issues
- Ensure Visual Studio 2022 with C++ tools is installed
- Regenerate project files if build errors occur
- Check that Unreal Engine 5.6+ is properly installed
- Verify all dependencies in `.Build.cs` files are correct

### Editor Integration Issues
- Check that the editor module loads correctly in Project Settings
- Verify asset type definitions are properly registered
- Ensure factory classes are correctly implementing required interfaces

### Graph Editor Issues
- Confirm graph schema is properly implemented
- Check node and pin widget implementations
- Verify drag-and-drop actions are correctly registered

## Technical Notes

- **Module Loading**: Editor module uses `PostEngineInit` loading phase
- **Asset Registration**: Custom assets appear in Content Browser automatically
- **Graph Integration**: Uses Unreal Engine's native graph editor framework
- **Slate UI**: Custom widgets built with Unreal's Slate framework
- **Property System**: Full integration with Unreal's reflection system