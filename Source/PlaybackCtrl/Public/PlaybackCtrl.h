//
// PlaybackCtrl.h
//
//  Generated on February 19 2020
//  Template created by Peter Gusev on 27 January 2020.
//  Copyright 2013-2019 Regents of the University of California
//

// A Boilerplate code for a C++/BP plugin that handles third-party dependencies automatically.
//
// NOTE: This module is dependent on ReLog plugin. Install it first.
//
// How to use:
// 1. Give a name to your plugin replacing placeholder <#Your Module Name#>
// 2. Rename all plugin files and folders according your plugin's name:
//      Boilerplate.h, Boilerplate.cpp, Boilerplate.Build.cs, Boilerplate.uplugin
// 3. Fix #include "Boilerplate.h" in .cpp file
//
// To add third-party dependencies:
// 1. Place your third-party folder (that has header files and binaries) in the "deps" subfolder.
// 2. Your third-party dependencies must have this folder structure:
//      <third-party lib name>
//          *- include      // headers should be placed here
//          *- lib          // (optional, can skip for header-only dependencies)
//              *- Android  // include only those platforms, that your third-party supports
//              *- IOS
//              *- macOS
//              *- Win64

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "DDBase.h"
#include "OscDataElemStruct.h"

class OscListener;
struct IPlaybackCtrlInterface; //added for component registration

class FPlaybackCtrlModule : public FDDBaseModule
{
public:
    static FPlaybackCtrlModule* GetSharedInstance();
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
    virtual void onPostWorldInitialization(UWorld *world) override;
    
    void onOscReceived(const FName & Address, const TArray<FOscDataElemStruct> & Data, const FString & SenderIp);
    
    // Allow components to register with the module
    
    /// Add the receiver in the listeners list
    void RegisterReceiver(IPlaybackCtrlInterface * receiver);

    /// Remove the receiver in the listeners list
    void UnregisterReceiver(IPlaybackCtrlInterface * receiver);
    
    void SpawnCues(UWorld *world);
    
    void GetAllBlueprintSubclasses(TArray<TAssetSubclassOf<ACueActor>>& Subclasses, FName BaseClassName, bool bAllowAbstract, FString const& Path, FString ClassName);
    
    

private:
    OscListener *listener_;
    // added for component register
    TArray<IPlaybackCtrlInterface *> _receivers;
    /// Protects _receivers
    FCriticalSection _receiversMutex;
    
    void oscDispatcherRegister(class UWorld* world);
};
