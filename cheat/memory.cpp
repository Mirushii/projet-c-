#include "memory.h"

// D�finition de la fonction getMemory
Memory& getMemory() {
    static Memory memory("ac_client.exe"); // instance unique
    return memory;
}
