#include "trekscii.h"

Canvas::Canvas(size_t w, size_t h) : w(w), h(h)
{
    // initialize mats
    starfield = std::vector<std::vector<char>>(h - 2, std::vector<char>(w));
    render = std::vector<std::vector<std::string>>(h - 2, std::vector<std::string>(w));
    
    // fill starfield with empty space
    for (int i = 0; i < starfield.size(); i++)
    {
        for (int j = 0; j < starfield[i].size(); j++)
        {
            starfield[i][j] = ' ';
        }
    }

    area = w * h;
}


void Canvas::getClusterCenters()
{
    size_t clusterCount = std::max(1, (int)(area * RenderConfig::CLUSTER_RATIO));
    clusterCenters = std::vector<std::pair<size_t, size_t>>(clusterCount);

    for (int i = 0; i < clusterCount; i++)
    {
        clusterCenters[i] = std::pair<int, int>
        {
            round((rand() % (int)round(h - (2 * (h * RenderConfig::VIGNETTE)))) + (h * RenderConfig::VIGNETTE)),
            round((rand() % (int)round(w - (2 * (w * RenderConfig::VIGNETTE)))) + (w * RenderConfig::VIGNETTE)),
        };
    }
}


void Canvas::spawnStars()
{
    for (int i = 0; i < starfield.size(); i++) {
        for (int j = RenderConfig::PADDING; j < starfield[i].size() - RenderConfig::PADDING; j++) {
            int minDist = GetManhattanDist(i, j, clusterCenters[0].first, clusterCenters[0].second);
            int clusterIndex = 0;

            for (int c = 1; c < clusterCenters.size(); c++) {
                int dist = GetManhattanDist(i, j, clusterCenters[c].first, clusterCenters[c].second);
                if (dist < minDist) {
                    minDist = dist;
                    clusterIndex = c;
                }
            }

            minDist /= 2;
            minDist += 1;

            // if (minManhattanDistance < 100) {
            if (rand() % minDist == 0) {
                // Check for overcrowding of stars

                bool crowded = false;
                for (int x = 1; x <= RenderConfig::HORIZ_PLACEMENT_PADDING; x++)
                    if (starfield[i][std::max(0, j - x)] != ' ' || starfield[i][std::min((int)starfield[i].size() - 1, j + x)] != ' ')
                        crowded = true;
                for (int x = 1; x <= RenderConfig::VERT_PLACEMENT_PADDING; x++)
                    if (starfield[std::max(0, i - x)][j] != ' ' || starfield[std::min((int)starfield.size() - 1, i + x)][j] != ' ')
                        crowded = true;

                if (!crowded)
                    starfield[i][j] = STAR_CHARS[rand() % STAR_CHARS.size()];
            }
        }
    }
}


void Canvas::renderStars()
{
    // Add vertical padding to render canvas for special stars
    std::vector<std::string> row(w);
    for (int i = 0; i < row.size(); i++) row[i] = " ";
    render.insert(render.begin(), row);
    render.push_back(row);

    // TODO: better organize this stuff
    std::vector<char> skipChars = {'-', '|', '/', '\\'};

    std::vector<std::vector<std::string>> colorBands = {{"\x1b[31m", "\x1b[33m"}, {"\x1b[34m", "\x1b[35m"}, {"\x1b[36m", "\x1b[32m"}};
    // std::vector<std::vector<std::string>> colorBands = {{COLORS[0], COLORS[1]}, {COLORS[2], COLORS[3]}, {COLORS[4], COLORS[5]}};
    // std::vector<std::vector<std::string>> colorBands = {{COLORS[0]}, {COLORS[1]}, {COLORS[2]}, {COLORS[3]}, {COLORS[4]}, {COLORS[5]}};
    int bandCount = colorBands.size();

    std::random_shuffle(colorBands.begin(), colorBands.end());

    for (int i = 0; i < starfield.size(); i++) {
        for (int j = 0; j < starfield[i].size(); j++) {
            
            std::string color;
            
            // if we're in the right band, have a 50% chance of picking that band's color
            // bands are calculated radially using manhattan distance

            size_t curDist = GetManhattanDist(i, j, h / 2, w / 2);
            size_t maxDist  = GetManhattanDist(0, 0, h / 2, w / 2) + bandCount;
            int band = curDist / (maxDist / bandCount);

            assert(band < colorBands.size());

            // bias it towards using the band color but allow randomness too
            if (rand() % 10 < 4)
                color = colorBands[band][rand() % colorBands[band].size()];
            else
                color = COLORSET[rand() % COLORSET.size()];

            // get random number for the star decorations
            int randDec = rand() % 20;

            // Add surrounding flare to special stars
            if ((starfield[i][j] == 'O' || starfield[i][j] == '0') && randDec < 15) {
                render[i+1][j-1] = color + "-" + RenderConfig::ENDC;
                render[i+1][j+1] = color + "-" + RenderConfig::ENDC;
            }
            if (starfield[i][j] == '0' && randDec < 10) {
                render[i][j] = color + "|" + RenderConfig::ENDC;
                render[i+2][j] = color + "|" + RenderConfig::ENDC;
            }
            if (starfield[i][j] == '0' && randDec < 1) {
                render[i+2][j-1] = color + "/" + RenderConfig::ENDC;
                render[i+2][j+1] = color + "\\" + RenderConfig::ENDC;
                render[i][j-1] = color + "\\" + RenderConfig::ENDC;
                render[i][j+1] = color + "/" + RenderConfig::ENDC;
            }


            // Place color and primary star char on canvas, but avoid overwriting existing chars
            // (can't do direct std::string comparison to check because colors are embedded in the std::strings)
            bool overWrite = true;

            for (char ch : skipChars)
                if (render[i+1][j].find(ch) != std::string::npos)
                    overWrite = false;
            
            if (overWrite)
                render[i+1][j] = color + starfield[i][j] + RenderConfig::ENDC;
        }
    }
}


void Canvas::overlayArt()
{
    // Add ship to rendered starfield
    for (std::string el : SPACE_ART) {
        if (rand() % 8 == 0) {
            std::vector<std::vector<char>> elMat = LiteralToMat(el);
            int length = Squarify(elMat);
            int height = elMat.size();

            int x = rand() % (render[0].size() - length);
            int y = rand() % (render.size() - height);

            if (rand() % 2 == 0) Reverse(elMat);
            Overlay(render, elMat, x, y);
            // Overlay(render, elMat, x, y, COLORS[rand() % COLORS.size()]);
        }
    }
    

    int maxShipCount = std::max(1, (int)(area * RenderConfig::CLUSTER_RATIO));
    int probability = 1;


    for (int i = 0; i < maxShipCount; i++)
    {
        if (rand() % probability == 0)
        {
            std::vector<std::vector<char>> ship = LiteralToMat(SHIP_ART[rand() % SHIP_ART.size()]);
            
            int shipLength = Squarify(ship);
            int shipHeight = ship.size();

            int x = rand() % (render[0].size() - shipLength);
            int y = rand() % (render.size() - shipHeight);

            if (x + (shipLength / 2) > (w / 2))
                Reverse(ship);
            
            Overlay(render, ship, x, y);
            probability *= 4;
        }
    }
}


void Canvas::generate()
{
    getClusterCenters();
    spawnStars();
    renderStars();
    overlayArt();
}


void Canvas::print()
{
    for (std::vector<std::string> x : render)
    {
        for (std::string str : x) std::cout << str;
        std::cout << std::endl;
    }
}