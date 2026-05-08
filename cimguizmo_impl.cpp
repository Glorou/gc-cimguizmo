#include "cimgui_user.h"

ImGuiAssertCallback g_AssertCallback = nullptr;

extern "C" __declspec(dllexport) void igCustom_SetAssertCallback(ImGuiAssertCallback callback)
{
    g_AssertCallback = callback;
}
