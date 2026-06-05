#pragma once
#include <vector>
#include <functional>
#include <string>
#include <optional>
#include <algorithm>

template <typename T>
class Repository {
    std::vector<T> items;
public:
    void add(const T& item) { items.push_back(item); }

    void removeIf(std::function<bool(const T&)> pred) {
        items.erase(std::remove_if(items.begin(), items.end(), pred), items.end());
    }

    std::optional<T> findIf(std::function<bool(const T&)> pred) const {
        for (const auto& item : items)
            if (pred(item)) return item;
        return std::nullopt;
    }

    const std::vector<T>& getAll() const { return items; }
    std::vector<T>& getAll() { return items; }

    size_t size() const { return items.size(); }
    bool empty() const { return items.empty(); }
};

template <typename T>
std::optional<T> findByEmail(Repository<T>& repo, const std::string& email) {
    return repo.findIf([&email](const T& item) {
        return item->getEmail() == email;
    });
}