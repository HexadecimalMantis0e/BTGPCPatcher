#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Patch.hpp"
#include "Util.hpp"

int main(int argc, char *argv[]) {

    std::fstream fs;
    DisableIntelWads disableIntelWads(fs, "DisableIntelWads");
    SwapCpuVendors swapCpuVendors(fs, "SwapCpuVendors");
    EnableCoordinates enableCoordinates(fs, "EnableCoordinates");

    std::vector<Patch *> patches { &disableIntelWads, &swapCpuVendors, &enableCoordinates };

    if (argc < 2) {
        usage(patches);
        return 0;
    }

    if ((std::string(argv[1]) == "-e" || std::string(argv[1]) == "--executable") && (argc > 2)) {

        fs.open(argv[2], std::ios::binary | std::ios::in | std::ios::out);

        if (!fs) {
            std::cout << "Could not open exe!" << std::endl;
            return 1;
        }

        if (argc > 3) {
            if ((std::string(argv[3]) == "-p" || std::string(argv[3]) == "--patch") && (argc > 4)) {
                for (int i = 4; i < argc; i++) {
                    if (!linearScan(patches, std::string(argv[i]))) {
                        std::cout << "Invalid patch!" << std::endl;
                        return 1;
                    }
                }
                applyPatches(patches, false);
            }
            else {
                usage(patches);
            }
        }
        else {
            applyPatches(patches, true);
        }
    }
    else {
        usage(patches);
    }
    return 0;
}
