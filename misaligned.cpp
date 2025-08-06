#include <iostream>
#include <vector>
#include <string>
#include <assert.h>

// Function to generate the color map
std::vector<std::string> generateColorMap() {
    const char* majorColor[] = {"White", "Red", "Black", "Yellow", "Violet"};
    const char* minorColor[] = {"Blue", "Orange", "Green", "Brown", "Slate"};
    std::vector<std::string> colorMap;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            colorMap.push_back(std::to_string(i * 5 + j) + " | " + majorColor[i] + " | " + minorColor[i]); // Bug: minorColor[i] should be minorColor[j]
        }
    }
    return colorMap;
}

// Function to print the color map
void printColorMap(const std::vector<std::string>& colorMap) {
    for (const auto& entry : colorMap) {
        std::cout << entry << "\n";
    }
}

// Test function
void testGenerateColorMap() {
    std::vector<std::string> colorMap = generateColorMap();

    // Strengthened tests
    assert(colorMap.size() == 25); // Check the size of the color map
    assert(colorMap[0] == "0 | White | Blue"); // Check the first entry
    assert(colorMap[24] == "24 | Violet | Slate"); // Check the last entry

    // This assertion will fail due to the bug in the code
    assert(colorMap[5] == "5 | Red | Blue"); // Check a middle entry
}

int main() {
    std::cout << "\nTesting color map generation\n";
    testGenerateColorMap(); // This will fail
    std::cout << "All tests passed (not really!)\n";

    return 0;
}
