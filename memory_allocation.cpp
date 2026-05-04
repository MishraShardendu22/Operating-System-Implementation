#include <bits/stdc++.h>
using namespace std;

// FIRST FIT
void firstFit(vector<int> blockSize, vector<int> processSize) {
    int n = blockSize.size(), m = processSize.size();
    vector<int> allocation(m, -1);

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (blockSize[j] >= processSize[i]) {
                allocation[i] = j;
                blockSize[j] -= processSize[i]; // FIX: must reduce block after allocation
                break;
            }
        }
    }

    cout << "\nFirst Fit:\n";
    for (int i = 0; i < m; i++)
        cout << "Process " << i << " -> Block " << allocation[i] << "\n";
}


// BEST FIT
void bestFit(vector<int> blockSize, vector<int> processSize) {
    int n = blockSize.size(), m = processSize.size();
    vector<int> allocation(m, -1);

    for (int i = 0; i < m; i++) {
        int bestIdx = -1;

        for (int j = 0; j < n; j++) {
            if (blockSize[j] >= processSize[i]) {
                if (bestIdx == -1 || blockSize[j] < blockSize[bestIdx]) {
                    bestIdx = j;
                }
            }
        }

        if (bestIdx != -1) {
            allocation[i] = bestIdx;
            blockSize[bestIdx] -= processSize[i]; // FIX: update remaining size
        }
    }

    cout << "\nBest Fit:\n";
    for (int i = 0; i < m; i++)
        cout << "Process " << i << " -> Block " << allocation[i] << "\n";
}


// WORST FIT
void worstFit(vector<int> blockSize, vector<int> processSize) {
    int n = blockSize.size(), m = processSize.size();
    vector<int> allocation(m, -1);

    for (int i = 0; i < m; i++) {
        int worstIdx = -1;

        for (int j = 0; j < n; j++) {
            if (blockSize[j] >= processSize[i]) {
                if (worstIdx == -1 || blockSize[j] > blockSize[worstIdx]) {
                    worstIdx = j;
                }
            }
        }

        if (worstIdx != -1) {
            allocation[i] = worstIdx;
            blockSize[worstIdx] -= processSize[i]; // FIX: update remaining size
        }
    }

    cout << "\nWorst Fit:\n";
    for (int i = 0; i < m; i++)
        cout << "Process " << i << " -> Block " << allocation[i] << "\n";
}


// NEXT FIT
void nextFit(vector<int> blockSize, vector<int> processSize) {
    int n = blockSize.size(), m = processSize.size();
    vector<int> allocation(m, -1);

    int lastIdx = 0; // FIX: pointer to last allocated block

    for (int i = 0; i < m; i++) {
        int count = 0;
        int j = lastIdx;

        while (count < n) {
            if (blockSize[j] >= processSize[i]) {
                allocation[i] = j;
                blockSize[j] -= processSize[i]; // FIX: update block size

                lastIdx = j; // FIX: update pointer
                break;
            }

            j = (j + 1) % n; // circular traversal
            count++;
        }
    }

    cout << "\nNext Fit:\n";
    for (int i = 0; i < m; i++)
        cout << "Process " << i << " -> Block " << allocation[i] << "\n";
}


int main() {
    vector<int> blockSize = {100, 500, 200, 300, 600};
    vector<int> processSize = {212, 417, 112, 426};

    firstFit(blockSize, processSize);
    bestFit(blockSize, processSize);
    worstFit(blockSize, processSize);
    nextFit(blockSize, processSize);

    return 0;
}