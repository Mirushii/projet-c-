#pragma once

#include <cstdint>
#include <string>

namespace cheat {
    extern int updatedHealth;
    extern int updatedNade;
    extern int updatedAmmo;
    extern int initialHealth;
    extern int initialNade;
    extern int initialAmmo;

    extern bool isGodModeOn;
    extern bool isInfNadeOn;
    extern bool isInfAmmoOn;
    extern bool isNoRecoilOn;
    extern bool isGetInfoOn;
    extern bool isInfArmorOn;
    extern bool isInfArmorOn;

    extern std::uintptr_t headPtr;
    extern std::uintptr_t entityL;
    extern std::uintptr_t entity;
    extern float headValue;

    static int initialArmor; // Valeur initiale de l'armure
    static bool isInfArmorOn; // Indicateur pour l'état de l'armure infinie

    void godmodeon() noexcept;
    void godmodeoff() noexcept;

    void infnadeon() noexcept;
    void infnadeoff() noexcept;

    void infammoon() noexcept;
    void infammooff() noexcept;

    void infarmoron() noexcept;
    void infarmoroff() noexcept;

    void norecoilon() noexcept;
    void norecoiloff() noexcept;

    void getinfoon() noexcept;
}