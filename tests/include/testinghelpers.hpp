#ifndef TEST_BODIES_H
#define TEST_BODIES_H

#include <chrono>
#include <raylib.h>
#include <thread>

inline int Vector2Equals2Vector(Vector2 vector_a, Vector2 vector_b){
    if (vector_a.x != vector_b.x){
        return 1;
    }
    if (vector_a.y != vector_b.y){
        return 1;
    }
    return 0;
}

inline void delayms(int time) {
    std::this_thread::sleep_for(std::chrono::milliseconds(time));
}

#endif
