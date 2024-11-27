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

int cheat::initialArmor = 0;
bool cheat::isInfArmorOn = false;

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
// Implémentation des fonctions pour les grenades infinies

void cheat::infnadeon() noexcept {
    if (isInfNadeOn) {
        return; // Si les grenades infinies sont déjà activées, on ne fait rien
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

    initialNade = memory.Read<int>(nadeAddress); // Stocker la valeur initiale des grenades

    isInfNadeOn = true; // Activer les grenades infinies

    std::thread([nadeAddress]() {
        auto& mem = getMemory();
        while (cheat::isInfNadeOn) {
            int currentNades = mem.Read<int>(nadeAddress); // Lire le nombre de grenades actuelles

            if (currentNades != 999) { // Si le nombre de grenades n'est pas 999, on le remplace par 999
                mem.Write<int>(nadeAddress, 999);
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(10)); // Attendre un court instant avant de vérifier à nouveau
        }
        }).detach(); // Détacher le thread pour qu'il fonctionne en parallèle
}

void cheat::infnadeoff() noexcept {
    if (!isInfNadeOn) {
        return; // Si les grenades infinies ne sont pas activées, ne rien faire
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

    isInfNadeOn = false; // Désactiver les grenades infinies

    memory.Write<int>(nadeAddress, initialNade); // Restaurer la valeur initiale des grenades
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

            // Si les munitions sont à 950 ou moins, les remettre à 999
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

void cheat::infarmoron() noexcept {
    if (cheat::isInfArmorOn) {
        return; // Si le mode armure infinie est déjà activé, ne rien faire
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

    const auto armorAddress = localPlayerPtr + m_iArmor;

    if (armorAddress == 0) {
        std::cerr << "Erreur : Adresse de l'armure est nulle." << std::endl;
        return;
    }

    initialArmor = memory.Read<int>(armorAddress); // Stocker la valeur initiale de l'armure

    isInfArmorOn = true; // Activer l'armure infinie

    std::thread([armorAddress]() {
        auto& mem = getMemory();
        while (cheat::isInfArmorOn) {
            int currentArmor = mem.Read<int>(armorAddress); // Lire la valeur actuelle de l'armure

            if (currentArmor < 100) { // Si l'armure est inférieure à 100, la réinitialiser à 100
                mem.Write<int>(armorAddress, 100);
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(10)); // Répéter toutes les 10ms
        }
        }).detach(); // Détacher le thread
}


void cheat::norecoilon() noexcept {}

void cheat::norecoiloff() noexcept {}

void cheat::getinfoon() noexcept {}
