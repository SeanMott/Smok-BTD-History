#pragma once

//defines various custom draw commands

#include <BTDSTD/Types.hpp>
#include <BTDSTD/Math/Vector.hpp>

#include <imgui.h>

#include <backends/imgui_impl_vulkan.h>

namespace Smok::TyGUI::Widget
{
    ////draws a input field for a C char* string
    //inline bool InputFieldCString(const char* label, char* buffer, const char* data)
    //{
    //    strcpy_s(buffer, sizeof(buffer), data);
    //    if (ImGui::InputText(label, buffer, sizeof(buffer)))
    //    {
    //        strcpy_s((char*)data, sizeof(data), buffer);
    //        return true;
    //    }

    //    return false;
    //}

    //inline bool InputFieldString(const char* label, char* buffer, char* data)
    //{
    //    strcpy(buffer, data);
    //    if (ImGui::InputText(label, buffer, sizeof(buffer)))
    //    {
    //        strcpy(data, buffer);
    //        return true;
    //    }

    //    return false;
    //}

    //draws a input field for uint64 || returns true if modified
    inline bool InputUInt32(const char* label, uint32* data)
    {
        return ImGui::InputScalar(label, ImGuiDataType_U32, data);
    }

    //draws a input field for uint64 || returns true if modified
    inline bool InputUInt64(const char* label, uint64* data)
    {
        return ImGui::InputScalar(label, ImGuiDataType_U64, data);
    }

    //draws a input field for double vec 2 || returns true if modified
    inline bool InputDoubleVec2(const char* label, BTD::Math::DVec2* data)
    {
        return ImGui::InputScalarN(label, ImGuiDataType_Double, data, 2, NULL, NULL, "%.3f", 0);
    }

    //draws a input field for double vec 3 || returns true if modified
    inline bool InputDoubleVec3(const char* label, BTD::Math::DVec3* data)
    {
        return ImGui::InputScalarN(label, ImGuiDataType_Double, data, 3, NULL, NULL, "%.3f", 0);
    }

    //draws a input field for float vec 2 || returns true if modified
    inline bool InputFloatVec2(const char* label, BTD::Math::FVec2* data)
    {
        return ImGui::InputScalarN(label, ImGuiDataType_Float, data, 2, NULL, NULL, "%.3f", 0);
    }

    //draws a input field for float vec 3 || returns true if modified
    inline bool InputFloatVec3(const char* label, BTD::Math::FVec3* data)
    {
        return ImGui::InputScalarN(label, ImGuiDataType_Float, data, 3, NULL, NULL, "%.3f", 0);
    }

    //draws a input field for color || returns true if modified
    inline bool InputColor(const char* label, BTD::Math::Color* data)
    {
        return ImGui::InputScalarN(label, ImGuiDataType_Float, data, 4, NULL, NULL, "%.3f", 0);
    }


    //ImGuiDataType_S8,       // signed char / char (with sensible compilers)
    //    ImGuiDataType_U8,       // unsigned char
    //    ImGuiDataType_S16,      // short
    //    ImGuiDataType_U16,      // unsigned short
    //    ImGuiDataType_S32,      // int
    //    ImGuiDataType_U32,      // unsigned int
    //    ImGuiDataType_S64,      // long long / __int64
    //    ImGuiDataType_U64,      // unsigned long long / unsigned __int64
    //    ImGuiDataType_Float,    // float
    //    ImGuiDataType_Double,   // double
    //    ImGuiDataType_COUNT
}