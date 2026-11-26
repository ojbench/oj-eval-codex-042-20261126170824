#include <algorithm>
#include <cassert>
#include <iostream>
#include <map>
#include <random>
#include <string>
#include <vector>
#define private public
#include "../solution.h"
#undef private

int main() {
    std::mt19937 rng(42);
    constexpr int prime = 1000000007;
    using Ring = SpeedCircularLinkedList<int, prime>;
    for (int n : {1, 2, 3, 4, 5, 7, 8, 9, 31, 32, 33, 1000, 50000}) {
        std::vector<int> bounds;
        for (int i = 1; i <= n; ++i)
            bounds.push_back(static_cast<long long>(prime) * i / n);
        Ring ring(bounds);
        assert(ring.size() == n);
        std::vector<Ring::Node*> nodes;
        auto cur = ring.head;
        for (int i = 0; i < n; ++i, cur = cur->next) nodes.push_back(cur);
        assert(cur == ring.head);
        for (int i = 0; i < n; ++i) {
            assert(nodes[i]->bound == bounds[i]);
            for (int k = 0; k < ring.fast_search_list_size; ++k)
                assert(nodes[i]->fast_search_list[k] == nodes[(i + (1 << k)) % n]);
            for (int code : {bounds[i] - 1, bounds[i], bounds[i] + 1}) {
                if (code >= prime) continue;
                int index = std::lower_bound(bounds.begin(), bounds.end(), code) - bounds.begin();
                assert(ring.FindNode(code) == nodes[index]);
            }
        }
        std::map<std::string, int> expected;
        const int count = n == 50000 ? 200000 : 4000;
        for (int i = 0; i < count; ++i) {
            std::string key = std::to_string(rng() % 10000);
            if (rng() % 2) {
                int value = rng() % 1000000;
                ring.put(key, value);
                expected[key] = value;
            } else {
                auto it = expected.find(key);
                assert(ring.get(key) == (it == expected.end() ? 0 : it->second));
            }
        }
        std::size_t total = 0;
        for (auto node : nodes) total += node->kv_map.size();
        assert(total == expected.size());
    }
    SpeedCircularLinkedList<std::string, 97> strings({97});
    assert(strings.get("missing").empty());
    strings.put("", "empty key");
    assert(strings.get("") == "empty key");
    std::cout << "All tests passed\n";
}
