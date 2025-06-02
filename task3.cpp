#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

// Structure to store prefix information
struct PrefixInfo {
    int total_count;    // Number of words starting with this prefix
    vector<int> indices; // Indices of words with this prefix
};

vector<string> linearCrossword(const vector<string>& words) {
    if (words.empty()) {
        return {}; // Cannot build a chain with no words
    }

    // 1. PREFIX INDEXING
    unordered_map<string, PrefixInfo> prefixMap;

    for (int idx = 0; idx < words.size(); idx++) {
        string word = words[idx]; // No case conversion for now
        int L = word.length();
        if (L < 2) {
            cout << "Skipping word '" << word << "' (too short)" << endl;
            continue;
        }

        // Generate all possible prefixes for the current word
        for (int k = 2; k <= L; k++) {
            string prefix = word.substr(0, k);
            prefixMap[prefix].total_count++;
            prefixMap[prefix].indices.push_back(idx);
            cout << "Added prefix '" << prefix << "' for word '" << word << "' (index " << idx << ")" << endl;
        }
    }

    // 2. CHAIN BUILDING
    vector<string> result;
    vector<bool> used(words.size(), false);
    vector<string> best_chain;

    // Try starting a chain with each word
    for (int start_idx = 0; start_idx < words.size(); start_idx++) {
        if (words[start_idx].length() < 2) continue;

        result.clear();
        result.push_back(words[start_idx]);
        used.assign(words.size(), false);
        used[start_idx] = true;

        cout << "\nTrying to build chain starting with '" << words[start_idx] << "'" << endl;

        // Build the chain
        while (true) {
            string last_word = result.back();
            int L = last_word.length();
            bool found = false;

            // Check all possible suffixes of the last word
            for (int k = 2; k <= L; k++) {
                string suffix = last_word.substr(L - k, k);
                cout << "Checking suffix '" << suffix << "' of word '" << last_word << "'" << endl;

                auto it = prefixMap.find(suffix);
                if (it != prefixMap.end()) {
                    // Check all words with the matching prefix
                    for (int idx : it->second.indices) {
                        if (!used[idx]) {
                            result.push_back(words[idx]);
                            used[idx] = true;
                            found = true;
                            cout << "Added word '" << words[idx] << "' to chain" << endl;
                            break;
                        }
                    }
                    if (found) break;
                }
            }
            if (!found) {
                cout << "No continuation found for word '" << last_word << "'" << endl;
                break;
            }
        }

        // Save the longest chain found
        if (result.size() >= 2 && result.size() > best_chain.size()) {
            best_chain = result;
        }
    }

    return best_chain; // Return the longest chain found
}

int main() {
    cout << "Enter words (empty line to finish):" << endl;

    vector<string> words;
    string input;

    // Input words from keyboard
    while (true) {
        getline(cin, input);
        if (input.empty()) break;
        words.push_back(input);
    }

    if (words.empty()) {
        cout << "No words entered" << endl;
        return 0;
    }

    // Find the chain
    vector<string> result = linearCrossword(words);

    // Output the result
    if (!result.empty()) {
        cout << "\nChain found: ";
        for (size_t i = 0; i < result.size(); i++) {
            cout << result[i];
            if (i < result.size() - 1) cout << " -> ";
        }
        cout << endl;
    } else {
        cout << "\nNo chain found" << endl;
    }

    return 0;
}
