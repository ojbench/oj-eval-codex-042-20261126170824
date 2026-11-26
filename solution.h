#ifndef SPEEDCIRCULARLIST_H
#define SPEEDCIRCULARLIST_H

#include <iostream>
#include <algorithm>
#include <map>
#include <string>
#include <vector>

constexpr int s_prime = 31;

inline int log2(int x) {
    int ans = 0;
    while (x > 1) {
        x /= 2;
        ++ans;
    }
    return ans;
}

template<typename T, int b_prime>
class SpeedCircularLinkedList {
public:
    struct Node {
        std::map<std::string, T> kv_map;
        int bound = 0;
        Node* next = nullptr;
        Node** fast_search_list = nullptr;
        std::vector<std::pair<int, Node*>> search_index;

        Node(int bound, int fast_search_list_size) : bound(bound) {
            fast_search_list = new Node*[fast_search_list_size]();
        }

        ~Node() { delete[] fast_search_list; }
    };

private:
    Node* head = nullptr;
    int fast_search_list_size = 0;
    int list_size = 0;

    static int GetHashCode(std::string str) {
        long long ans = 0;
        for (auto& ch : str) {
            ans = (ans * s_prime + ch) % b_prime;
        }
        return static_cast<int>((ans + b_prime) % b_prime);
    }

    void BuildFastSearchList() {
        if (head) {
            head->search_index.reserve(list_size);
            Node* cur = head;
            for (int i = 0; i < list_size; ++i, cur = cur->next)
                head->search_index.emplace_back(cur->bound, cur);
        }
        for (int level = 0; level < fast_search_list_size; ++level) {
            Node* cur = head;
            for (int i = 0; i < list_size; ++i, cur = cur->next) {
                cur->fast_search_list[level] = level == 0 ? cur->next :
                    cur->fast_search_list[level - 1]->fast_search_list[level - 1];
            }
        }
    }

    Node* FindNode(int code) const {
        if (!head || code <= head->bound) return head;
        const auto& index = head->search_index;
        auto it = std::lower_bound(index.begin(), index.end(), code,
            [](const std::pair<int, Node*>& entry, int target) {
                return entry.first < target;
            });
        return it->second;
    }

public:
    explicit SpeedCircularLinkedList(std::vector<int> node_bounds) {
        list_size = static_cast<int>(node_bounds.size());
        fast_search_list_size = log2(list_size);
        Node* tail = nullptr;
        try {
            for (int bound : node_bounds) {
                Node* node = new Node(bound, fast_search_list_size);
                if (tail) tail->next = node;
                else head = node;
                tail = node;
            }
        } catch (...) {
            while (head) {
                Node* next = head->next;
                delete head;
                head = next;
            }
            throw;
        }
        if (tail) tail->next = head;
        BuildFastSearchList();
    }

    ~SpeedCircularLinkedList() {
        for (int i = 0; i < list_size; ++i) {
            Node* next = head->next;
            delete head;
            head = next;
        }
    }

    void put(std::string str, T value) {
        int code = GetHashCode(str);
        Node* node = FindNode(code);
        if (node) node->kv_map[str] = value;
    }

    T get(std::string str) {
        int code = GetHashCode(str);
        Node* node = FindNode(code);
        if (!node) return T();
        auto it = node->kv_map.find(str);
        return it == node->kv_map.end() ? T() : it->second;
    }

    void print() {
        Node* cur = head;
        for (int i = 0; i < list_size; ++i, cur = cur->next) {
            std::cout << "[Node] Bound = " << cur->bound
                      << ", kv_map_size = " << cur->kv_map.size() << '\n';
        }
    }

    int size() const { return list_size; }
};

#endif
