#include <Windows.h>
#include <vector>
#include <iostream>
#include <CommCtrl.h>
#include <thread>
#include <chrono>
#include "../cheat/offset.h"
#include "../cheat/memory.h"
#include "../cheat/cheat.h"

int cheat::updatedHealth = 100;
int cheat::updatedNade = 0;
int cheat::updatedAmmo = 20;
int cheat::initialHealth = 0;
int cheat::initialNade = 0;
int cheat::initialAmmo = 0;
bool cheat::isGodModeOn = false;
bool cheat::isInfNadeOn = false;
bool cheat::isInfAmmoOn = false;
bool cheat::isNoRecoilOn = false;
bool cheat::isGetInfoOn = false;
std::uintptr_t cheat::headPtr = 0;
std::uintptr_t cheat::entityL = 0;
std::uintptr_t cheat::entity = 0;
float cheat::headValue = 0.0f;

void cheat::godmodeon() noexcept {
    if (isGodModeOn) return;

    auto& memory = getMemory();
    const auto moduleBase = memory.GetModuleAddress("ac_client.exe");
    if (moduleBase == 0) return;

    const auto localPlayerPtr = memory.Read<std::uintptr_t>(moduleBase + localPlayer);
    if (localPlayerPtr == 0) return;

    const auto healthAddress = localPlayerPtr + m_iHealth;
    if (healthAddress == 0) return;

    initialHealth = memory.Read<int>(healthAddress);
    isGodModeOn = true;

    std::thread([healthAddress]() {
        auto& mem = getMemory();
        while (cheat::isGodModeOn) {
            if (mem.Read<int>(healthAddress) < 9999) {
                mem.Write<int>(healthAddress, 9999);
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
        }).detach();
}

void cheat::godmodeoff() noexcept {
    if (!isGodModeOn) return;

    auto& memory = getMemory();
    const auto moduleBase = memory.GetModuleAddress("ac_client.exe");
    if (moduleBase == 0) return;

    const auto localPlayerPtr = memory.Read<std::uintptr_t>(moduleBase + localPlayer);
    if (localPlayerPtr == 0) return;

    const auto healthAddress = localPlayerPtr + m_iHealth;
    if (healthAddress == 0) return;

    isGodModeOn = false;
    memory.Write<int>(healthAddress, initialHealth);
}

void cheat::infnadeon() noexcept {
    if (isInfNadeOn) return;

    auto& memory = getMemory();
    const auto moduleBase = memory.GetModuleAddress("ac_client.exe");
    if (moduleBase == 0) return;

    const auto localPlayerPtr = memory.Read<std::uintptr_t>(moduleBase + localPlayer);
    if (localPlayerPtr == 0) return;

    const auto nadeAddress = localPlayerPtr + m_Nades;
    if (nadeAddress == 0) return;

    initialNade = memory.Read<int>(nadeAddress);
    isInfNadeOn = true;

    std::thread([nadeAddress]() {
        auto& mem = getMemory();
        while (cheat::isInfNadeOn) {
            if (mem.Read<int>(nadeAddress) != 999) {
                mem.Write<int>(nadeAddress, 999);
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
        }).detach();
}

void cheat::infnadeoff() noexcept {
    if (!isInfNadeOn) return;

    auto& memory = getMemory();
    const auto moduleBase = memory.GetModuleAddress("ac_client.exe");
    if (moduleBase == 0) return;

    const auto localPlayerPtr = memory.Read<std::uintptr_t>(moduleBase + localPlayer);
    if (localPlayerPtr == 0) return;

    const auto nadeAddress = localPlayerPtr + m_Nades;
    if (nadeAddress == 0) return;

    isInfNadeOn = false;
    memory.Write<int>(nadeAddress, initialNade);
}

void cheat::infammoon() noexcept {
    if (isInfAmmoOn) return;

    auto& memory = getMemory();
    const auto moduleBase = memory.GetModuleAddress("ac_client.exe");
    if (moduleBase == 0) return;

    const auto localPlayerPtr = memory.Read<std::uintptr_t>(moduleBase + localPlayer);
    if (localPlayerPtr == 0) return;

    const auto ammoAddress = localPlayerPtr + m_iAmmo;
    if (ammoAddress == 0) return;

    initialAmmo = memory.Read<int>(ammoAddress);
    isInfAmmoOn = true;

    std::thread([ammoAddress]() {
        auto& mem = getMemory();
        while (cheat::isInfAmmoOn) {
            if (mem.Read<int>(ammoAddress) <= 950) {
                mem.Write<int>(ammoAddress, 999);
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
        }).detach();
}

void cheat::infammooff() noexcept {
    if (!isInfAmmoOn) return;

    auto& memory = getMemory();
    const auto moduleBase = memory.GetModuleAddress("ac_client.exe");
    if (moduleBase == 0) return;

    const auto localPlayerPtr = memory.Read<std::uintptr_t>(moduleBase + localPlayer);
    if (localPlayerPtr == 0) return;

    const auto ammoAddress = localPlayerPtr + m_iAmmo;
    if (ammoAddress == 0) return;

    isInfAmmoOn = false;
    memory.Write<int>(ammoAddress, initialAmmo);
}

void cheat::norecoilon() noexcept {
    if (isNoRecoilOn) return;

    auto& memory = getMemory();
    const auto moduleBase = memory.GetModuleAddress("ac_client.exe");
    if (moduleBase == 0) return;

    const auto localPlayerPtr = memory.Read<std::uintptr_t>(moduleBase + 0x109B74);
    if (localPlayerPtr == 0) return;

    const auto recoilAddress = localPlayerPtr + 0x00004C;
    const auto shootRecoilAddress = localPlayerPtr + 0x000050;
    if (recoilAddress == 0 || shootRecoilAddress == 0) return;

    isNoRecoilOn = true;
    std::thread([recoilAddress, shootRecoilAddress]() {
        auto& mem = getMemory();
        while (cheat::isNoRecoilOn) {
            mem.Write<float>(recoilAddress, 0.0f);
            mem.Write<float>(shootRecoilAddress, 0.0f);
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
        }).detach();
}

void cheat::norecoiloff() noexcept {
    if (!isNoRecoilOn) return;
    isNoRecoilOn = false;
}

void cheat::getinfoon() noexcept {}
