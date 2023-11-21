#include <vector>
#include <cmath>
#include <cstdint>
#include <fstream>
#include <iostream>

std::vector<int16_t> getData();
bool writeFile(std::vector<int> data, char* fileName);
int getIndex(int16_t x, int16_t y, int16_t xDim = 6000);
bool pixelInMap(int16_t pixelX, int16_t pixelY);
bool inBoundary(int16_t centerX, int16_t centerY, int16_t considerX, int16_t considerY);