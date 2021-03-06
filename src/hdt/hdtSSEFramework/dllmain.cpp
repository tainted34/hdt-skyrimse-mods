// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "stdafx.h"
#include "HookUtils.h"
#include "FrameworkImpl.h"
#include "../hdtSSEUtils/LogUtils.h"

static hdt::LogToFile s_Log("Data/SKSE/Plugins/hdtSSEFramework.log");

HMODULE g_DllModule = nullptr;
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
		g_DllModule = hModule;
		break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

extern "C"
{

	bool SKSEPlugin_Query(const SKSEInterface * skse, PluginInfo * info)
	{
		// populate info structure
		info->infoVersion = PluginInfo::kInfoVersion;
		info->name = "hdtSSEFramework";
		info->version = 1;

		if (skse->isEditor)
		{
			return false;
		}

		if (!hdt::FrameworkImpl::instance()->isSupportedSkyrimVersion(skse->runtimeVersion))
			return false;

		return true;
	}

	bool SKSEPlugin_Load(const SKSEInterface * skse)
	{
		hdt::FrameworkImpl::instance()->hook();
		return true;
	}
}
