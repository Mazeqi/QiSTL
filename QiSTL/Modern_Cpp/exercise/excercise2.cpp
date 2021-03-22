#include <iostream>
#include <map>
#include <string>
#include <functional>

template <typename Key, typename Value, typename F>
void update(F foo, std::map<Key, Value>& m) {
    for (auto&& [key, value] : m) value = foo(key);
}

//int main() {
//    std::map<std::string, long long int> m{
//        {"a", 1},
//        {"b", 2},
//        {"c", 3}
//    };
//    update([](std::string key) -> long long int {
//        return std::hash<std::string>{}(key);
//        }, m);
//    for (auto&& [key, value] : m)
//        std::cout << key << ":" << value << std::endl;
//}