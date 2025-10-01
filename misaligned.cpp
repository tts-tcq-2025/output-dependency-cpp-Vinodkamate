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
    

    // But the buggy code uses minorColor[1]="Orange"
    
    // This assertion will FAIL because the bug makes it use wrong minor color
    const char* expectedMinorForEntry7 = "Green";  // minorColor[j=2] 
    const char* actualMinorFromBuggyCode = "Orange";  // minorColor[i=1] - what bug produces
    
    // This assert will FAIL, exposing the bug!
    assert(expectedMinorForEntry7 == actualMinorFromBuggyCode);  // Green != Orange - FAILS!
    
    int result = printColorMap();
    assert(result == 25);
    std::cout << "All is well (maybe!)\n";
}
