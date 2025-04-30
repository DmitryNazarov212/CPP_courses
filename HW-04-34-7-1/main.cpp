#include <concepts>
#include <iostream>
template<typename T>
concept ComplexConcept = requires(T t) {
    { t.hash() } -> std::convertible_to<long>;
    { t.toString() } -> std::same_as<std::string>;
    requires !std::has_virtual_destructor_v<T>;
};