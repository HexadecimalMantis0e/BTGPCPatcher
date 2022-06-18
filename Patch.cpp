#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Patch.hpp"

Patch::Patch(std::fstream &fileStream, const std::string &patchName) : fs(fileStream), name(patchName) {
    state = false;
}

const std::string &Patch::getName() const {
    return name;
}

bool Patch::getState() const {
    return state;
}

void Patch::setState(bool state) {
    this->state = state;
}

DisableIntelWads::DisableIntelWads(std::fstream &fileStream, const std::string &patchName) : Patch(fileStream, patchName) {}

void DisableIntelWads::apply() {
    /* Creator: Hexadecimal Mantis */
    fs.seekp(0x00042D88, std::ios::beg); // 0x00442D88
    std::vector<unsigned char> patchBytes {
        0x90,       // nop
        0x90,       // nop
        0x90,       // nop
        0x90,       // nop
        0xEB, 0x06  // jmp     short loc_442D94
    };
    fs.write(reinterpret_cast<const char *>(patchBytes.data()), patchBytes.size());
}

SwapCpuVendors::SwapCpuVendors(std::fstream &fileStream, const std::string &patchName) : Patch(fileStream, patchName) {}

void SwapCpuVendors::apply() {
    /* Creator: Hexadecimal Mantis */
    fs.seekp(0x000C5DAC, std::ios::beg); // 0x004C5DAC
    std::vector<unsigned char> patchBytes {
        0x47, 0x65, 0x6E, 0x75, // dword_4C5DAC     dd 756E6547h
        0x69, 0x6E, 0x65, 0x49, // dword_4C5DB0     dd 49656E69h
        0x6E, 0x74, 0x65, 0x6C, // dword_4C5DB4     dd 6C65746Eh
        0x00,                   // byte_4C5DB8      db 0
        0x00, 0x00, 0x00,       //                  align 4
        0x41, 0x75, 0x74, 0x68, // dword_4C5DBC     dd 68747541h
        0x65, 0x6E, 0x74, 0x69, // dword_4C5DC0     dd 69746E65h
        0x63, 0x41, 0x4D, 0x44  // dword_4C5DC4     dd 444D4163h
    };
    fs.write(reinterpret_cast<const char *>(patchBytes.data()), patchBytes.size());
}

EnableCoordinates::EnableCoordinates(std::fstream &fileStream, const std::string &patchName) : Patch(fileStream, patchName) {}

void EnableCoordinates::apply() {
    /* Creator: Hexadecimal Mantis */
    fs.seekp(0x00055B23, std::ios::beg); // 0x00455B23
    std::vector<unsigned char> patchBytes {
        0x0F, 0x84, 0xA2, 0x00, 0x00, 0x00  // jz      loc_455BCB
    };
    fs.write(reinterpret_cast<const char *>(patchBytes.data()), patchBytes.size());
}

EnableMilliseconds::EnableMilliseconds(std::fstream &fileStream, const std::string &patchName) : Patch(fileStream, patchName) {}

void EnableMilliseconds::apply() {
    /* Creator: Hexadecimal Mantis */
    fs.seekp(0x00057617, std::ios::beg); // 0x00457617
    std::vector<unsigned char> patchBytes {
        0x0F, 0x84, 0xA6, 0x00, 0x00, 0x00  // jz      loc_4576C3
    };
    fs.write(reinterpret_cast<const char *>(patchBytes.data()), patchBytes.size());
}
