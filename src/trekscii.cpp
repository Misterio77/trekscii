#include <iostream>
#include "trekscii.h"



int main(int argc, char** argv) {

    // random seeding copied from stackoverflow :)
    uint32_t seed=0;
    FILE *devrnd = fopen("/dev/random","r");
    fread(&seed, 4, 1, devrnd);
    fclose(devrnd);
    srand(seed);
    

    int dimY = std::stoi(argv[1]);
    int dimX = std::stoi(argv[2]);

    Canvas canvas = Canvas(dimX, dimY - 2);
    canvas.generate();
    canvas.print();
}