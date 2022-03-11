#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>

using namespace std; // Bad practice, but works for now

int hit_count = 0;

struct LRUsolver {
    static void bubble(int i, vector<char> &cache) {
        for (int k = i; k + 1 < 4; ++k) {
            swap(cache[k], cache[k + 1]);
        }
    }

    static void solve(string &type, string &s) {
        vector<char> cache(4, 0);
        for (int i = 0; i < s.size(); i += 2) {
            int hit_cache_idx = -1;
            for (int j = 0; j < 4; ++j) {
                if (cache[j] == s[i]) {
                    hit_cache_idx = j;
                    break;
                }
            }
            if (hit_cache_idx != -1) {
                // Cache hit, bubble the hit cache block to the front
                // without changing relative order of other blocks
                bubble(hit_cache_idx, cache);
                ++hit_count;
            } else {
                // Cache miss
                if (type == "LRU") {
                    // If LRU: drop cache[0], insert s[i] as new cache[0]
                    // and bubble cache[0] to the front
                    cache[0] = s[i];
                    bubble(0, cache);
                } else {
                    // If MRU: drop cache[3]. Insert s[i] as new cache[3]
                    // if there are garbage values (0). bubble 0 to cache[3]
                    // as the most recently used (waiting to be replaced)
                    for (int j = 0; j < 4; ++j) {
                        if (cache[j] == 0) {
                            bubble(j, cache);
                            break;
                        }
                    }
                    cache[3] = s[i];
                }
            }
        }
    };
};

struct LFUsolver {
    static void solve(string &s) {
        vector<int> freq;
        vector<char> LFU;
        for (int i = 0; i < s.size(); i += 2) {
            freq.assign(128, 0);
            LFU.assign(4, 0);
            // Detect Cache Hit
            int cache_hit_idx = -1;
            for (int j = 0; j < 4; ++j) {
                if (LFU[j] == s[i]) {
                    cache_hit_idx = j;
                    break;
                }
            }
            if (cache_hit_idx != -1) {
                // Cache hit
                ++freq[s[i]];
                hit_count++;
            } else {
                // Cache miss
                // Replace least frequently used item with s[i]
                // If there are multiple, replace the item with the smallest index
                int least_freq_idx = 0;
                for (int j = 0; j < 4; ++j) {
                    if (freq[LFU[j]] < freq[LFU[least_freq_idx]]) {
                        least_freq_idx = j;
                    }
                }
                LFU[least_freq_idx] = s[i];
                freq[s[i]] = 1;
            }
        }
    }
};

struct FIFOsolver {
    static void solve(string &s) {
        deque<char> queue;
        for (int i = 0; i < s.size(); i += 2) {
            if (find(queue.begin(), queue.end(), s[i]) != queue.end()) {
                hit_count++;
                continue;
            }
            // For LIFO simply change pop_front to pop_back()
            if (queue.size() == 4) { queue.pop_front(); }
            queue.push_back(s[i]);
        }
    }
};


int main() {
    string type, s;
    cin >> type >> s;

    // Input Format

    if (type == "LRU" or type == "MRU") {
        LRUsolver::solve(type, s);
    } else if (type == "LFU") {
        LFUsolver::solve(s);
    } else if (type == "FIFO") {
        FIFOsolver::solve(s);
    } else {
        cout << "Invalid type (or other invalid arguments)";
        return -1;
    }

    cout << "Number of hits: " << hit_count << '\n';
    cout << "Number of misses: " << (s.size() + 1) / 2 - hit_count << '\n';
}
