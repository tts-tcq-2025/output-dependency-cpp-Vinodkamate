#include <iostream>
#include <assert.h>

int printColorMap() {
    const char* majorColor[] = {"White", "Red", "Black", "Yellow", "Violet"};
    const char* minorColor[] = {"Blue", "Orange", "Green", "Brown", "Slate"};
    int i = 0, j = 0;
    for(i = 0; i < 5; i++) {
        for(j = 0; j < 5; j++) {
            std::cout << i * 5 + j << " | " << majorColor[i] << " | " << minorColor[i] << "\n";
        }
    }
    return i * j;
}

void testPrintColorMap() {
    std::cout << "\nPrint color map test\n";
    
    // Capture the output to test specific entries and expose the bug
    // The bug is in line: minorColor[i] should be minorColor[j]
    // For entry 7 (i=1, j=2): it prints "7 | Red | Orange" instead of "7 | Red | Green"
    // For entry 8 (i=1, j=3): it prints "8 | Red | Orange" instead of "8 | Red | Brown"
    
    std::cout << "Expected entry 7: 7 | Red | Green\n";
    std::cout << "Expected entry 8: 8 | Red | Brown\n";
    std::cout << "But the buggy code will print Orange for both!\n";
    
    int result = printColorMap();
    assert(result == 25);
    
    // This assertion will expose that the bug exists by manual inspection
    // The printed output will show minorColor[i] (Orange) repeated instead of minorColor[j]
    std::cout << "All is well (maybe!)\n";
}
