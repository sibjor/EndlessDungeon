#include <ctime>
#include <random>

int random(int min, int max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(min, max);
    return dis(gen);
}

bool randomBool() {
    return random(0, 1);
}