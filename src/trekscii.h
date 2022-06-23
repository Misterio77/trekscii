#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <random>
#include <algorithm>
#include <assert.h>



const extern std::vector<std::string> SHIP_ART;
const extern std::vector<std::string> SPACE_ART;
const extern std::vector<char> STAR_CHARS;
const extern std::vector<std::string> COLORSET;


struct RenderConfig
{
    const static int PADDING = 1;
    const static int HORIZ_PLACEMENT_PADDING = 4;
    const static int VERT_PLACEMENT_PADDING = 2;

    constexpr static double VIGNETTE = 0.25;

    constexpr static double CLUSTER_RATIO = 1.0 / 2000.0;

    const static std::string ENDC;
};


// Global util funcs
std::vector<std::vector<char>> LiteralToMat(std::string);
size_t Squarify(std::vector<std::vector<char>>&);
void Reverse(std::vector<std::vector<char>>&);
void Overlay(std::vector<std::vector<std::string>>& base, const std::vector<std::vector<char>>& overlay, int x, int y, std::string color = RenderConfig::ENDC);
size_t GetManhattanDist(size_t x1, size_t y1, size_t x2, size_t y2);

class Canvas
{
public:
    Canvas(size_t w, size_t h);

    void generate();
    void print();

private:
    std::vector<std::vector<char>> starfield;
    std::vector<std::vector<std::string>> render;

    std::vector<std::pair<size_t, size_t>> clusterCenters;

    void getClusterCenters();
    void spawnStars();
    void renderStars();
    void overlayArt();

    size_t w, h, area;
};