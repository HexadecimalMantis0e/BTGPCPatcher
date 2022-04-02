#include <iostream>
#include <cstdio>
#include <string>
#include <vector>

class Patch {
    public:
        Patch(std::FILE *filePointer, std::string patchName) {
            fp = filePointer;
            name = patchName;
            state = false;
        }

        virtual ~Patch() {}

        std::string getName() {
            return name;
        }

        bool getState() {
            return state;
        }

        void setState(bool state) {
            this->state = state;
        }

        virtual void apply() = 0;

    protected:
        std::FILE *fp;
        std::string name;
        bool state;
};

class DisableIntelWads : public Patch {
    public:
        DisableIntelWads(std::FILE *filePointer, std::string patchName) : Patch(filePointer, patchName) {}
        void apply() {
            /* Creator: Hexadecimal Mantis */
            std::fseek(fp, 0x00042D88, SEEK_SET); // 0x00442D88
            std::vector<unsigned char> patchBytes {
                0x90,       // nop
                0x90,       // nop
                0x90,       // nop
                0x90,       // nop
                0xEB, 0x06  // jmp     short loc_442D94
            };
            std::fwrite(&patchBytes[0], sizeof(std::vector<unsigned char>::value_type), patchBytes.size(), fp);
        }
};

void usage() {
    std::cout << "Usage: BTGPCPatcher -e executable [-p [patch] ...]" << std::endl;
    std::cout << "Arguments:" << std::endl;
    std::cout << "    -e, --executable    Executable to patch" << std::endl;
    std::cout << "    -p, --patch         Patch(es) to apply" << std::endl;
}

bool linearScan(std::vector<Patch *> &patchList, std::string argument) {
    bool searchFlag = false;
    for (auto &patch : patchList) {
        if (argument == patch->getName()) {
            patch->setState(true);
            searchFlag = true;
            break;
        }
    }
    return searchFlag;
}

void applyPatches(std::vector<Patch *> &patchList, bool applyAll) {
    for (auto &patch : patchList) {
        if (applyAll == true) {
            patch->setState(true);
        }
        if (patch->getState() == true) {
            std::cout << "Applying " << patch->getName() << "..." << std::endl;
            patch->apply();
        }
    }
}

void freePatches(std::vector<Patch *> &patchList) {
    for (auto &patch : patchList) {
        delete patch;
    }
}

int main(int argc, char *argv[]) {

    if (argc < 2) {
        usage();
        return 0;
    }

    if ((std::string(argv[1]) == "-e" || std::string(argv[1]) == "--executable") && (argc > 2)) {
        std::FILE *f0 = std::fopen(argv[2], "r+b");
        if (f0 == NULL) {
            std::cout << "Could not open exe!" << std::endl;
            return 1;
        }

        std::vector<Patch *> patches {
            new DisableIntelWads(f0, "DisableIntelWads"),
        };

        if (argc > 3) {
            if ((std::string(argv[3]) == "-p" || std::string(argv[3]) == "--patch") && (argc > 4)) {
                for (int i = 4; i < argc; i++) {
                    if (linearScan(patches, std::string(argv[i])) == false) {
                        std::cout << "Invalid patch!" << std::endl;
                        std::fclose(f0);
                        freePatches(patches);
                        return 1;
                    }
                }
                applyPatches(patches, false);
            }
            else {
                usage();
            }
        }
        else {
            applyPatches(patches, true);
        }
        std::fclose(f0);
        freePatches(patches);
    }
    else {
        usage();
    }
    return 0;
}