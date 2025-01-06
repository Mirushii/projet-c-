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
    if (isGodModeOn) {
        return;
    }

    auto& memory = getMemory();
    const auto moduleBase = memory.GetModuleAddress("ac_client.exe");

    if (moduleBase == 0) {
        std::cerr << "Erreur : Module ac_client.exe introuvable." << std::endl;
        return;
    }

    const auto localPlayerPtr = memory.Read<std::uintptr_t>(moduleBase + localPlayer);

    if (localPlayerPtr == 0) {
        std::cerr << "Erreur : Pointeur localPlayerPtr est nul." << std::endl;
        return;
    }

    const auto healthAddress = localPlayerPtr + m_iHealth;

    if (healthAddress == 0) {
        std::cerr << "Erreur : Adresse de la santé est nulle." << std::endl;
        return;
    }

    initialHealth = memory.Read<int>(healthAddress);

    isGodModeOn = true;

    std::thread([](std::uintptr_t healthAddr) {
        auto& mem = getMemory();
        while (cheat::isGodModeOn) {
            int currentHealth = mem.Read<int>(healthAddr);

            if (currentHealth < 9999) {
                mem.Write<int>(healthAddr, 9999);
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
        }, healthAddress).detach();
}

void cheat::godmodeoff() noexcept {
    if (!isGodModeOn) {
        return;
    }

    auto& memory = getMemory();
    const auto moduleBase = memory.GetModuleAddress("ac_client.exe");

    if (moduleBase == 0) {
        std::cerr << "Erreur : Module ac_client.exe introuvable." << std::endl;
        return;
    }

    const auto localPlayerPtr = memory.Read<std::uintptr_t>(moduleBase + localPlayer);

    if (localPlayerPtr == 0) {
        std::cerr << "Erreur : Pointeur localPlayerPtr est nul." << std::endl;
        return;
    }

    const auto healthAddress = localPlayerPtr + m_iHealth;

    if (healthAddress == 0) {
        std::cerr << "Erreur : Adresse de la santé est nulle." << std::endl;
        return;
    }

    isGodModeOn = false;

    memory.Write<int>(healthAddress, initialHealth);
}

void cheat::infnadeon() noexcept {
    if (isInfNadeOn) {
        return;
    }

    auto& memory = getMemory();
    const auto moduleBase = memory.GetModuleAddress("ac_client.exe");

    if (moduleBase == 0) {
        std::cerr << "Erreur : Module ac_client.exe introuvable." << std::endl;
        return;
    }

    const auto localPlayerPtr = memory.Read<std::uintptr_t>(moduleBase + localPlayer);

    if (localPlayerPtr == 0) {
        std::cerr << "Erreur : Pointeur localPlayerPtr est nul." << std::endl;
        return;
    }

    const auto nadeAddress = localPlayerPtr + m_Nades;

    if (nadeAddress == 0) {
        std::cerr << "Erreur : Adresse des grenades est nulle." << std::endl;
        return;
    }

    initialNade = memory.Read<int>(nadeAddress);

    isInfNadeOn = true;

    std::thread([nadeAddress]() {
        auto& mem = getMemory();
        while (cheat::isInfNadeOn) {
            int currentNades = mem.Read<int>(nadeAddress);

            if (currentNades != 999) {
                mem.Write<int>(nadeAddress, 999);
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
        }).detach();
}

void cheat::infnadeoff() noexcept {
    if (!isInfNadeOn) {
        return;
    }

    auto& memory = getMemory();
    const auto moduleBase = memory.GetModuleAddress("ac_client.exe");

    if (moduleBase == 0) {
        std::cerr << "Erreur : Module ac_client.exe introuvable." << std::endl;
        return;
    }

    const auto localPlayerPtr = memory.Read<std::uintptr_t>(moduleBase + localPlayer);

    if (localPlayerPtr == 0) {
        std::cerr << "Erreur : Pointeur localPlayerPtr est nul." << std::endl;
        return;
    }

    const auto nadeAddress = localPlayerPtr + m_Nades;

    if (nadeAddress == 0) {
        std::cerr << "Erreur : Adresse des grenades est nulle." << std::endl;
        return;
    }

    isInfNadeOn = false;

    memory.Write<int>(nadeAddress, initialNade);
}

void cheat::infammoon() noexcept {
    if (isInfAmmoOn) {
        return;
    }

    auto& memory = getMemory();
    const auto moduleBase = memory.GetModuleAddress("ac_client.exe");

    if (moduleBase == 0) {
        std::cerr << "Erreur : Module ac_client.exe introuvable." << std::endl;
        return;
    }

    const auto localPlayerPtr = memory.Read<std::uintptr_t>(moduleBase + localPlayer);

    if (localPlayerPtr == 0) {
        std::cerr << "Erreur : Pointeur localPlayerPtr est nul." << std::endl;
        return;
    }

    const auto ammoAddress = localPlayerPtr + m_iAmmo;

    if (ammoAddress == 0) {
        std::cerr << "Erreur : Adresse des munitions est nulle." << std::endl;
        return;
    }

    initialAmmo = memory.Read<int>(ammoAddress);

    isInfAmmoOn = true;

    std::thread([ammoAddress]() {
        auto& mem = getMemory();
        while (cheat::isInfAmmoOn) {
            int currentAmmo = mem.Read<int>(ammoAddress);

            if (currentAmmo <= 950) {
                mem.Write<int>(ammoAddress, 999);
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
        }).detach();
}

void cheat::infammooff() noexcept {
    if (!isInfAmmoOn) {
        return;
    }

    auto& memory = getMemory();
    const auto moduleBase = memory.GetModuleAddress("ac_client.exe");

    if (moduleBase == 0) {
        std::cerr << "Erreur : Module ac_client.exe introuvable." << std::endl;
        return;
    }

    const auto localPlayerPtr = memory.Read<std::uintptr_t>(moduleBase + localPlayer);

    if (localPlayerPtr == 0) {
        std::cerr << "Erreur : Pointeur localPlayerPtr est nul." << std::endl;
        return;
    }

    const auto ammoAddress = localPlayerPtr + m_iAmmo;

    if (ammoAddress == 0) {
        std::cerr << "Erreur : Adresse des munitions est nulle." << std::endl;
        return;
    }

    isInfAmmoOn = false;

    memory.Write<int>(ammoAddress, initialAmmo);
}

void cheat::norecoilon() noexcept {
    if (isNoRecoilOn) {
        return;
    }

    auto& memory = getMemory();
    const auto moduleBase = memory.GetModuleAddress("ac_client.exe");

    if (moduleBase == 0) {
        std::cerr << "Erreur : Module ac_client.exe introuvable." << std::endl;
        return;
    }

    const auto localPlayerPtr = memory.Read<std::uintptr_t>(moduleBase + 0x109B74);

    if (localPlayerPtr == 0) {
        std::cerr << "Erreur : Pointeur localPlayerPtr est nul." << std::endl;
        return;
    }

    const auto recoilAddress = localPlayerPtr + 0x00004C;

    if (recoilAddress == 0) {
        std::cerr << "Erreur : Adresse du recul est nulle." << std::endl;
        return;
    }

    isNoRecoilOn = true;

    std::thread([recoilAddress]() {
        auto& mem = getMemory();
        while (cheat::isNoRecoilOn) {
            float currentRecoil = mem.Read<float>(recoilAddress);

            if (currentRecoil != 0.0f) {
                mem.Write<float>(recoilAddress, 0.0f);
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
        }).detach();
}

void cheat::norecoiloff() noexcept {
    if (!isNoRecoilOn) {
        return;
    }

    isNoRecoilOn = false;
}

void cheat::getinfoon() noexcept {}
