#ifndef PATCH_HPP
#define PATCH_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class Patch {
    public:
        const std::string &getName() const;
        bool getState() const;
        void setState(bool state);
        virtual void apply() = 0;

    protected:
        Patch(std::fstream &fileStream, const std::string &patchName);
        std::fstream &fs;
        const std::string name;
        bool state;
};

class DisableIntelWads : public Patch {
    public:
        DisableIntelWads(std::fstream &fileStream, const std::string &patchName);
        void apply();
};

class SwapCpuVendors : public Patch {
    public:
        SwapCpuVendors(std::fstream &fileStream, const std::string &patchName);
        void apply();
};

class EnableCoordinates : public Patch {
    public:
        EnableCoordinates(std::fstream &fileStream, const std::string &patchName);
        void apply();
};

class EnableMilliseconds : public Patch {
    public:
        EnableMilliseconds(std::fstream &fileStream, const std::string &patchName);
        void apply();
};

#endif
