#pragma once

template <typename T>
class Countable {
    inline static int instanceCount = 0;
public:
    Countable() { ++instanceCount; }
    Countable(const Countable&) { ++instanceCount; }
    ~Countable() { --instanceCount; }
    static int getCount() { return instanceCount; }
};