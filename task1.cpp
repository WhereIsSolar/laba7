#include "task1.h"
using namespace std;

void cantorSet(int level, int maxLevels) {
    if (level == 0) return;
    int baseLength = 1;
    int segmentLength = baseLength * static_cast<int>(pow(3, level - 1));
    int numSegments = 1 << (maxLevels - level);
    for (int i = 0; i < maxLevels - level; i++) cout << "  ";
    for (int s = 0; s < numSegments; s++) {
        for (int i = 0; i < segmentLength; i++) cout << "-";
        if (s < numSegments - 1) {
            for (int i = 0; i < segmentLength; i++) cout << " ";
        }
    }
    cout << endl;
    cantorSet(level - 1, maxLevels);
}

int main() {
    int levels ;
    cin >> levels;
    cout << "Cantor set construction for " << levels << " levels:" << endl;
    cantorSet(levels, levels);
    cout << "Construction completed." << endl;
    return 0;
}
