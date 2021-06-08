#include "Main.h"

#include <Windows.h>
#include <vector>
#include "RecoilTables.h"
#include "Recoil.h"
#include <string>
#include <string.h>
#include <iostream>
#include <fstream>
#include <winbase.h>
#include <tchar.h>
#include <WinInet.h>


#pragma comment(lib,"Wininet.lib")

#pragma comment(lib, "winmm.lib")

#define _WIN32_WINNT 0x0500


using namespace std;

const char* Weapon = "NONE";
const char* Scope = "NONE";
const char* Barrel = "NONE";

bool bReload, bAK47, bLR300, bMP5, bCSMG, bSemi, Bhardak, bPhyton, bTHOMPSON, bm39, bM249, bSound, b8x, b16x, bHolo, bSimple, bSuppressor, bhýp, bMuzzleBoost = false;

float Sensitivity = 0.2;

namespace CurrentWeapon {
    double x(int Bullet) {
        if (bAK47 == true)
            return (((Recoil_Ak47[Bullet].x * ScopeAttachment()) * BarrelAttachment()) / 4) / Sensitivity;
        else if (bLR300 == true)
            return (((Recoil_Lr300[Bullet].x * ScopeAttachment()) * BarrelAttachment()) / 4) / Sensitivity;
        else if (bMP5 == true)
            return (((Recoil_Mp5a4[Bullet].x * ScopeAttachment()) * BarrelAttachment()) / 4) / Sensitivity;
        else if (bTHOMPSON == true)
            return (((Recoil_Thompson_g[Bullet].x * ScopeAttachment()) * BarrelAttachment()) / 4) / Sensitivity;
        else if (bCSMG == true)
            return (((Recoil_Custom_g[Bullet].x * ScopeAttachment()) * BarrelAttachment()) / 4) / Sensitivity;
        else if (bM249 == true)
            return (((Recoil_M249[Bullet].x * ScopeAttachment()) * BarrelAttachment()) / 4) / Sensitivity;
        else if (bSemi == true)
            return (((Recoil_Semi_r[Bullet].x * ScopeAttachment()) * BarrelAttachment()) / 4) / Sensitivity;
        else if (bm39 == true)
            return (((Recoil_m39[Bullet].x * ScopeAttachment()) * BarrelAttachment()) / 4) / Sensitivity;
        else if (bPhyton == true)
            return (((Recoil_Phyton[Bullet].x * ScopeAttachment()) * BarrelAttachment()) / 4) / Sensitivity;
        else
            return 0;
    }
    double y(int Bullet) {
        if (bAK47 == true)
            return (((Recoil_Ak47[Bullet].y * ScopeAttachment()) * BarrelAttachment()) / 4) / Sensitivity;
        else if (bLR300 == true)
            return (((Recoil_Lr300[Bullet].y * ScopeAttachment()) * BarrelAttachment()) / 4) / Sensitivity;
        else if (bMP5 == true)
            return (((Recoil_Mp5a4[Bullet].y * ScopeAttachment()) * BarrelAttachment()) / 4) / Sensitivity;
        else if (bTHOMPSON == true)
            return (((Recoil_Thompson_g[Bullet].y * ScopeAttachment()) * BarrelAttachment()) / 4) / Sensitivity;
        else if (bCSMG == true)
            return (((Recoil_Custom_g[Bullet].y * ScopeAttachment()) * BarrelAttachment()) / 4) / Sensitivity;
        else if (bM249 == true)
            return (((Recoil_M249[Bullet].x * ScopeAttachment()) * BarrelAttachment()) / 4) / Sensitivity;
        else if (bSemi == true)
            return (((Recoil_Semi_r[Bullet].y * ScopeAttachment()) * BarrelAttachment()) / 4) / Sensitivity;
        else if (bm39 == true)
            return (((Recoil_m39[Bullet].y * ScopeAttachment()) * BarrelAttachment()) / 4) / Sensitivity;
        else if (Bhardak == true)
            return (((Recoil_Phyton[Bullet].y * ScopeAttachment()) * BarrelAttachment()) / 4) / Sensitivity;
        else
            return 0;
    }
    double Delay() {
        if (bAK47 == true)
            return WeaponData::AK47.Delay;
        else if (bLR300 == true)
            return WeaponData::LR300.Delay;
        else if (bMP5 == true)
            return WeaponData::MP5.Delay;
        else if (bTHOMPSON == true)
            return WeaponData::THOMPSON.Delay;
        else if (bCSMG == true)
            return WeaponData::CUSTOM_SMG.Delay;
        else if (bM249 == true)
            return WeaponData::M249.Delay;
        else if (bSemi == true)
            return WeaponData::SEMI.Delay;
        else if (bm39 == true)
            return WeaponData::m39.Delay;
        else if (bPhyton == true)
            return WeaponData::Phyton.Delay;

        else
            return 0;
    }
    double Control(int bullet) {
        if (bAK47 == true)
            return ControlTime_Ak47[bullet];
        else if (bLR300 == true)
            return ControlTime_Lr300[bullet];
        else if (bMP5 == true)
            return ControlTime_Mp5a4[bullet];
        else if (bTHOMPSON == true)
            return ControlTime_Recoil_Thompson_g[bullet];
        else if (bCSMG == true)
            return ControlTime_Recoil_Custom_g[bullet];
        else if (bM249 == true)
            return ControlTime_M249[bullet];
        else if (bSemi == true)
            return WeaponData::SEMI.Delay;
        else if (bm39 == true)
            return WeaponData::m39.Delay;
        else if (bPhyton == true)
            return WeaponData::Phyton.Delay;
        else
            return 0;
    }
    int Bullet() {
        if (bAK47 == true)
            return Recoil_Ak47.size() - 1;
        else if (bLR300 == true)
            return Recoil_Lr300.size() - 1;
        else if (bMP5 == true)
            return Recoil_Mp5a4.size() - 1;
        else if (bm39 == true)
            return Recoil_m39.size() - 1;
        else if (bTHOMPSON == true)
            return Recoil_Thompson_g.size() - 1;
        else if (bCSMG == true)
            return Recoil_Custom_g.size() - 1;
        else if (bM249 == true)
            return Recoil_M249.size() - 1;
        else if (bSemi == true)
            return Recoil_Semi_r.size() - 1;
        else if (bPhyton == true)
            return Recoil_Phyton.size() - 1;
        else
            return 0;
    }
    bool WeaponActive() {
        if (bAK47 == true || bLR300 == true || bMP5 == true || bTHOMPSON == true || bCSMG == true || bSemi == true || bM249 == true)
            return true;
        else
            return false;
    }
    void RecoilBreak(int count) {
        if (bSemi == true) {
            mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
        }
        else if (bM249 == true) {
        }
        else if (bSemi != true || bM249 != true) {
            if (count == CurrentWeapon::Bullet()) {
                if (bSound == true) {
                    Beep(1200, 90);
                    Beep(1500, 90);
                }
                mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
            }
        }
    }
};




void Smoothing(double delay, double control_time, int x, int y) {
    int x_ = 0, y_ = 0, t_ = 0;
    for (int i = 1; i <= (int)control_time; ++i) {
        int xI = i * x / (int)control_time;
        int yI = i * y / (int)control_time;
        int tI = i * (int)control_time / (int)control_time;
        mouse_event(1, (int)xI - (int)x_, (int)yI - (int)y_, 0, 0);
        pQuerySleep((int)tI - (int)t_);
        x_ = xI; y_ = yI; t_ = tI;
    }
    pQuerySleep((int)delay - (int)control_time);
}

int IsMuzzleBoost(float Delay) {
    if (bMuzzleBoost == true) {
        float difference = Delay * 0.1f;
        Delay = Delay - difference;
        return (int)Delay + 2;
    }
    else
        return (int)Delay;
}

double BarrelAttachment() {
    if (bSuppressor == true) {
        if (bM249 == true)
            Multiplyer::Barrel.Suppressor = 0.75;
        if (bCSMG == true)
            Multiplyer::Barrel.Suppressor = 0.85;
        if (bSimple == true || bHolo == true)
            return 0.75;
        if (b8x == true && bSuppressor == true)
            return 1.46;
        else
            return Multiplyer::Barrel.Suppressor;
    }
    else if (bMuzzleBoost == true) {
        return Multiplyer::Barrel.None;
    }
    else
        return Multiplyer::Barrel.None;
}
double ScopeAttachment() {
    if (b8x == true) {
        if (bCSMG == true || bTHOMPSON == true) {
            if (b8x == true)
                return Multiplyer::Scope.x8 + 0.75;
        }
        return Multiplyer::Scope.x8;
    }
    if (b16x == true) {
        if (bCSMG == true || bTHOMPSON == true) {
            if (b16x == true)
                return Multiplyer::Scope.x16 + 0.75;
        }
        return Multiplyer::Scope.x16;
    }
    else if (bSimple == true) {
        if (bCSMG == true || bTHOMPSON == true) {
            if (bSimple == true)
                return Multiplyer::Scope.Simple + 0.1;
        }
        return Multiplyer::Scope.Simple;
    }

    else if (bHolo == true) {
        if (bCSMG == true || bTHOMPSON == true) {
            if (bHolo == true)
                return Multiplyer::Scope.Holo + 0.3;
        }
        return Multiplyer::Scope.Holo;
    }
    else
        return Multiplyer::Scope.None;
}

void pQuerySleep(int ms)
{
    LONGLONG timerResolution;
    LONGLONG wantedTime;
    LONGLONG currentTime;

    QueryPerformanceFrequency((LARGE_INTEGER*)&timerResolution);
    timerResolution /= 1000;

    QueryPerformanceCounter((LARGE_INTEGER*)&currentTime);
    wantedTime = currentTime / timerResolution + ms;
    currentTime = 0;
    while (currentTime < wantedTime)
    {
        QueryPerformanceCounter((LARGE_INTEGER*)&currentTime);
        currentTime /= timerResolution;
    }
}

void script()
{



    if (GetAsyncKeyState(VK_NUMPAD1)) {
        bAK47 = !bAK47;
        if (bAK47 == true) {
            Weapon = "AK47";
            bLR300 = false; bMP5 = false; bCSMG = false; bTHOMPSON = false; bSemi = false; bM249 = false;
        }
        else if (bAK47 == false) {
            Weapon = "NONE"; Scope = "NONE"; Barrel = "NONE";
            b8x = false; bHolo = false; bSimple = false; bSuppressor = false; b16x = false;
        }
        Beep(300, 150);
    }
    if (GetAsyncKeyState(VK_NUMPAD2)) {
        bLR300 = !bLR300;
        if (bLR300 == true) {
            Weapon = "LR300";
            bMP5 = false; bCSMG = false; bTHOMPSON = false; bSemi = false; bM249 = false; bAK47 = false;
        }
        else if (bLR300 == false) {
            Weapon = "NONE"; Scope = "NONE"; Barrel = "NONE";
            b8x = false; bHolo = false; bSimple = false; bSuppressor = false; b16x = false;
        }
        Beep(300, 150);
    }
    if (GetAsyncKeyState(VK_NUMPAD3)) {
        bMP5 = !bMP5;
        if (bMP5 == true) {
            Weapon = "MP5A4";
            bLR300 = false; bCSMG = false; bTHOMPSON = false; bSemi = false; bM249 = false; bAK47 = false;
        }
        else if (bMP5 == false) {
            Weapon = "NONE"; Scope = "NONE"; Barrel = "NONE";
            b8x = false; bHolo = false; bSimple = false; bSuppressor = false; b16x = false;
        }
        Beep(300, 150);
    }
    if (GetAsyncKeyState(VK_NUMPAD5)) {
        bCSMG = !bCSMG;
        if (bCSMG == true) {
            Weapon = "CUSTOM_SMG";
            bLR300 = false; bMP5 = false; bTHOMPSON = false; bSemi = false; bM249 = false; bAK47 = false;
        }
        else if (bCSMG == false) {
            Weapon = "NONE"; Scope = "NONE"; Barrel = "NONE";
            b8x = false; bHolo = false; bSimple = false; bSuppressor = false; b16x = false;
        }
        Beep(300, 150);
    }
    if (GetAsyncKeyState(VK_NUMPAD4)) {
        bTHOMPSON = !bTHOMPSON;
        if (bTHOMPSON == true) {
            Weapon = "THOMPSON";
            bLR300 = false; bMP5 = false; bCSMG = false; bSemi = false; bM249 = false; bAK47 = false;
        }
        else if (bTHOMPSON == false) {
            Weapon = "NONE"; Scope = "NONE"; Barrel = "NONE";
            b8x = false; bHolo = false; bSimple = false; bSuppressor = false; b16x = false;
        }
        Beep(300, 150);
    }
    if (GetAsyncKeyState(VK_NUMPAD6)) {
        bSemi = !bSemi;
        if (bSemi == true) {
            Weapon = "SEMI AUTO";
            bLR300 = false; bMP5 = false; bCSMG = false; bTHOMPSON = false; bM249 = false; bAK47 = false;
        }
        else if (bSemi == false) {
            Weapon = "NONE"; Scope = "NONE"; Barrel = "NONE";
            b8x = false; bHolo = false; bSimple = false; bSuppressor = false; b16x = false;
        }
        Beep(300, 150);
    }
    if (GetAsyncKeyState(VK_NUMPAD7)) {
        bM249 = !bM249;
        if (bM249 == true) {
            Weapon = "M249";
            bLR300 = false; bMP5 = false; bCSMG = false; bTHOMPSON = false; bSemi = false; bAK47 = false;
        }
        else if (bM249 == false) {
            Weapon = "NONE"; Scope = "NONE"; Barrel = "NONE";
            b8x = false; bHolo = false; bSimple = false; bSuppressor = false; b16x = false;
        }
        Beep(300, 150);
    }
    if (GetAsyncKeyState(VK_F2)) {
        b8x = !b8x;
        switch (b8x) {
        case(true):
            Scope = "8x"; bHolo = false; bSimple = false; b16x = false;
            break;
        case(false):
            Scope = "NONE";
            break;
        }
        Beep(300, 150);
    }

    if (GetAsyncKeyState(VK_F3)) {
        b16x = !b16x;
        switch (b16x) {
        case(true):
            Scope = "16x"; bHolo = false; bSimple = false; b8x = false;
            break;
        case(false):
            Scope = "NONE";
            break;
        }
        Beep(300, 150);
    }


    if (GetAsyncKeyState(VK_F5)) {
        bSimple = !bSimple;
        if (bSimple == true) {
            Scope = "SIMPLE"; b8x = false; bHolo = false; b16x = false;
        }
        else if (bSimple == false)
            Scope = "NONE";
        Beep(300, 150);
    }
    if (GetAsyncKeyState(VK_F4)) {
        bHolo = !bHolo;
        if (bHolo == true) {
            Scope = "HOLO"; b8x = false; bSimple = false; b16x = false;
        }
        else if (bHolo == false)
            Scope = "NONE";
        Beep(300, 150);
    }
    if (GetAsyncKeyState(VK_NUMPAD8)) {
        bSuppressor = !bSuppressor;
        if (bSuppressor == true) {
            Barrel = "SILENCER"; bMuzzleBoost = false;
        }
        else if (bSuppressor == false)
            Barrel = "NONE";
        Beep(300, 150);
    }
    if (GetAsyncKeyState(VK_F6)) {
        bMuzzleBoost = !bMuzzleBoost;
        if (bMuzzleBoost == true) {
            Barrel = "Boost"; bSuppressor = false;
        }
        else if (bMuzzleBoost == false)
            Barrel = "NONE";
        Beep(300, 150);
    }
    if (GetAsyncKeyState(VK_F12)) {
        keybd_event(VK_F1, 0, 0, 0);

    }


    if (CurrentWeapon::WeaponActive() == true)
    {
        for (int i = 0; i <= CurrentWeapon::Bullet() && GetAsyncKeyState(VK_LBUTTON) & 0x8000 && GetAsyncKeyState(VK_RBUTTON) & 0x8000; i++)
        {
            Smoothing((int)IsMuzzleBoost((float)CurrentWeapon::Delay()), (int)IsMuzzleBoost(CurrentWeapon::Control(i)), (int)CurrentWeapon::x(i), (int)CurrentWeapon::y(i));
            CurrentWeapon::RecoilBreak(i);
        }






    }
}


int APIENTRY WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{






    WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, LOADER_BRAND, NULL };
    RegisterClassEx(&wc);
    main_hwnd = CreateWindow(wc.lpszClassName, LOADER_BRAND, WS_POPUP, 0, 0, 5, 5, NULL, NULL, wc.hInstance, NULL);


    if (!CreateDeviceD3D(main_hwnd)) {
        CleanupDeviceD3D();
        UnregisterClass(wc.lpszClassName, wc.hInstance);
        return 1;
    }


    ShowWindow(main_hwnd, SW_HIDE);
    UpdateWindow(main_hwnd);


    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO();
    io.IniFilename = nullptr;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    ImGui::StyleColorsDark();



    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        void Theme(); {



            ImGui::GetStyle().FrameRounding = 4.0f;
            ImGui::GetStyle().GrabRounding = 4.0f;

            ImVec4* colors = ImGui::GetStyle().Colors;
            colors[ImGuiCol_Text] = ImVec4(0.95f, 0.96f, 0.98f, 1.00f);
            colors[ImGuiCol_TextDisabled] = ImVec4(0.36f, 0.42f, 0.47f, 1.00f);
            colors[ImGuiCol_WindowBg] = ImVec4(0.11f, 0.15f, 0.17f, 1.00f);
            colors[ImGuiCol_ChildBg] = ImVec4(0.15f, 0.18f, 0.22f, 1.00f);
            colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
            colors[ImGuiCol_Border] = ImVec4(0.08f, 0.10f, 0.12f, 1.00f);
            colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
            colors[ImGuiCol_FrameBg] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
            colors[ImGuiCol_FrameBgHovered] = ImVec4(0.12f, 0.20f, 0.28f, 1.00f);
            colors[ImGuiCol_FrameBgActive] = ImVec4(0.09f, 0.12f, 0.14f, 1.00f);
            colors[ImGuiCol_TitleBg] = ImVec4(0.09f, 0.12f, 0.14f, 0.65f);
            colors[ImGuiCol_TitleBgActive] = ImVec4(0.08f, 0.10f, 0.12f, 1.00f);
            colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
            colors[ImGuiCol_MenuBarBg] = ImVec4(0.15f, 0.18f, 0.22f, 1.00f);
            colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.39f);
            colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
            colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.18f, 0.22f, 0.25f, 1.00f);
            colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.09f, 0.21f, 0.31f, 1.00f);
            colors[ImGuiCol_CheckMark] = ImVec4(0.28f, 0.56f, 1.00f, 1.00f);
            colors[ImGuiCol_SliderGrab] = ImVec4(0.28f, 0.56f, 1.00f, 1.00f);
            colors[ImGuiCol_SliderGrabActive] = ImVec4(0.37f, 0.61f, 1.00f, 1.00f);
            colors[ImGuiCol_Button] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
            colors[ImGuiCol_ButtonHovered] = ImVec4(0.28f, 0.56f, 1.00f, 1.00f);
            colors[ImGuiCol_ButtonActive] = ImVec4(0.06f, 0.53f, 0.98f, 1.00f);
            colors[ImGuiCol_Header] = ImVec4(0.20f, 0.25f, 0.29f, 0.55f);
            colors[ImGuiCol_HeaderHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
            colors[ImGuiCol_HeaderActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
            colors[ImGuiCol_Separator] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
            colors[ImGuiCol_SeparatorHovered] = ImVec4(0.10f, 0.40f, 0.75f, 0.78f);
            colors[ImGuiCol_SeparatorActive] = ImVec4(0.10f, 0.40f, 0.75f, 1.00f);
            colors[ImGuiCol_ResizeGrip] = ImVec4(0.26f, 0.59f, 0.98f, 0.25f);
            colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
            colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
            colors[ImGuiCol_Tab] = ImVec4(0.11f, 0.15f, 0.17f, 1.00f);
            colors[ImGuiCol_TabHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
            colors[ImGuiCol_TabActive] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
            colors[ImGuiCol_TabUnfocused] = ImVec4(0.11f, 0.15f, 0.17f, 1.00f);
            colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.11f, 0.15f, 0.17f, 1.00f);
            colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
            colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
            colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
            colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
            colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
            colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
            colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
            colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
            colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
            colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);











        }
    }


    ImGui_ImplWin32_Init(main_hwnd);
    ImGui_ImplDX9_Init(g_pd3dDevice);



    DWORD window_flags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar;

    RECT screen_rect;
    GetWindowRect(GetDesktopWindow(), &screen_rect);
    auto x = float(screen_rect.right - WINDOW_WIDTH) / 2.f;
    auto y = float(screen_rect.bottom - WINDOW_HEIGHT) / 2.f;

    MSG msg;
    ZeroMemory(&msg, sizeof(msg));
    while (msg.message != WM_QUIT)
    {
        if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
            continue;
        }





        ImGui_ImplDX9_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();
        {
            ImGui::SetNextWindowPos(ImVec2(x, y), ImGuiCond_Once);
            ImGui::SetNextWindowSize(ImVec2(WINDOW_WIDTH, WINDOW_HEIGHT));
            ImGui::SetNextWindowBgAlpha(1.0f);

            ImGui::Begin(LOADER_BRAND, &loader_active, window_flags);
            {



                static bool Sc = true;

                ImGui::Text(" ");
                ImGui::TextColored(ImColor(77, 136, 247), "_________________________________________________________________________");

                ImGui::Text(" ");
                ImGui::Text(" NUMPAD 1  =  AK           F2  =  8x");
                ImGui::Text(" NUMPAD 2  =  LR300        F3  =  16x ");
                ImGui::Text(" NUMPAD 3  =  MP5          F4  =  Holo");
                ImGui::Text(" NUMPAD 4  =  THOMPSON     F5  =  Simple ");
                ImGui::Text(" NUMPAD 5  =  SMG          F6  =  Boost");
                ImGui::Text(" NUMPAD 6  =  SEMI         F10 =  Silencer");
                ImGui::Text(" NUMPAD 7  =  M249                         ");
                ImGui::Text(" NUMPAD 8  =  M39                         ");
                ImGui::TextColored(ImColor(77, 136, 247), "_________________________________________________________________________");
                ImGui::Text(" ");

                if (Sc == true) {

                    script();
                }



                ImGui::Text(" ");
                ImGui::SameLine(18);
                ImGui::TextColored(ImColor(250, 251, 252), "               Weapon:");
                ImGui::SameLine();
                ImGui::TextColored(ImColor(77, 136, 247), Weapon);
                ImGui::Text("");
                ImGui::SameLine(18);
                ImGui::TextColored(ImColor(250, 251, 252), "               Scopes:");
                ImGui::SameLine();
                ImGui::TextColored(ImColor(77, 136, 247), Scope);
                ImGui::Text("");
                ImGui::SameLine(18);
                ImGui::TextColored(ImColor(250, 251, 252), "               Barrel:");

                ImGui::SameLine();
                ImGui::TextColored(ImColor(77, 136, 247), Barrel);
                ImGui::Text(" ");

                ImGui::TextColored(ImColor(250, 251, 252), "      Sensitivity:");
                ImGui::Text(" ");
                ImGui::SameLine(50);
                ImGui::SliderFloat("", &Sensitivity, 0, 2, "% .2f");

                ImGui::TextColored(ImColor(77, 136, 247), "_________________________________________________________________________");


            }
            ImGui::End();
        }
        ImGui::EndFrame();

        g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0, 1.0f, 0);
        if (g_pd3dDevice->BeginScene() >= 0)
        {
            ImGui::Render();
            ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
            g_pd3dDevice->EndScene();
        }


        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
        }

        HRESULT result = g_pd3dDevice->Present(NULL, NULL, NULL, NULL);


        if (result == D3DERR_DEVICELOST && g_pd3dDevice->TestCooperativeLevel() == D3DERR_DEVICENOTRESET) {
            ResetDevice();
        }
        if (!loader_active) {
            msg.message = WM_QUIT;
        }
    }

    ImGui_ImplDX9_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    CleanupDeviceD3D();
    DestroyWindow(main_hwnd);
    UnregisterClass(wc.lpszClassName, wc.hInstance);

    return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;

    switch (msg)
    {
    case WM_SIZE:
        if (g_pd3dDevice != NULL && wParam != SIZE_MINIMIZED)
        {
            g_d3dpp.BackBufferWidth = LOWORD(lParam);
            g_d3dpp.BackBufferHeight = HIWORD(lParam);
            ResetDevice();
        }
        return 0;
    case WM_SYSCOMMAND:
        if ((wParam & 0xfff0) == SC_KEYMENU)
            return 0;
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hWnd, msg, wParam, lParam);
}