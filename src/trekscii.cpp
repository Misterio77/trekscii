#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <cmath>
#include <assert.h>
#include <random>

using namespace std; // sorry bjarne

const int PADDING = 1;
const int HORIZ_PLACEMNET_PADDING = 4;
const int VERT_PLACEMENT_PADDING = 2;
const double VIGNETTE = 0.25;

const string ENDC = "\x1b[0m";


/*=====================================
    Star trek ship ASCII art
======================================*/
// 'a' encodes an actual empty space, as opposed to ' ' which denotes transparency.

const string BIRD_OF_PREY_1 = R"SHIP(   __
 /|
/a\
\aa\
}]::)==-{)
/aa/
\a/
 \|__)SHIP";

const string BIRD_OF_PREY_2 = R"SHIP(     _o_
 _,---O---,_
 `         ')SHIP";


const string BORG_CUBE = R"SHIP(    ___________
   /-/_"/-/_/-/|
  /"-/-_"/-_//||
 /__________/|/|
 |"|_'='-]:+|/||
 |-+-|.|_'-"||//
 |[".[:!+-'=|//
 |='!+|-:]|-|/
  ----------)SHIP";

const string TINY_SHIP = ".-=-.";

 const string ENTERPRISE_1 = R"SHIP(======o==o  ___---___
      \\|| ============
      __\\| /a/
      \_______/)SHIP";

const string ENTERPRISE_2 = R"SHIP(___________________          _-_
\__(==========/_=_/ ____.---'---`---.____
            \_a\    \----._________.----/
              \a\   /aa/    `-_-'
          __,--`.`-'..'-_
         /____aaaaaaaaaa||
              `--.____,-')SHIP";

const string ENTERPRISE_3 = R"SHIP(  _      _-_      _
_|_|.---'---`---.|_|_
\----._________.----/
    `.aa`]-['aa,'
      `.'a_a`.'
       |a(_)a|
        `___')SHIP";


const string SHUTTLE_1 = R"SHIP(   __________
  //a_||a_a|a`.
 //_/aa|[_]|aaa`.
/______|___|_____\
\______|___|___,-'
 [_][______][_>)SHIP";

const string SHUTTLE_2 = R"SHIP(     _____
    /aaaaa\
   /|aaaaa|\
  /_|_____|_\
 _\_|_____|_/_
<_>`-\___/-'<_>)SHIP";

const string GALAXY_CLASS = R"SHIP(               ___.----~~~----.___ 
,--------.-.,-'-------------------`
`--------"-'-.,---`~~~-----~~~'
 '---'-._____/)SHIP";

const string BOMBULBAN_BARBIRD = R"SHIP(   _...--'~~~'-.=========--.
,-'-,----,------\-,~~~~~[@`-\
`-.-`----`------|='======\_-|
   `---.______.-'          `|)SHIP";


const string ENTERPRISE_4 = R"SHIP(________________        _
\__(=======/_=_/____.--'-`--.___
          \a\   `,--,-.___.----'
        .--`\\--'../
       '---._____.|])SHIP";

const string VOYAGER = R"SHIP(              __,--=====-.__
 _________,--'_,--'/_-__-___`--._
{======>________,._.-------------'
       ``---._____/)SHIP";

const string NEBULA_CLASS = R"SHIP( _______
[_______].----~~~----.___
  /---/------------------`
.-------.-)~~-----~~~'
`-------"-')SHIP";

const string DEFIANT = R"SHIP(       _________________________
 __.--'--,.-'a---------'--'--'a/`-.__
|__--(--(a|aaaaNX-74205aa====a/-----.`--._
   `---.__\aa--========)>aaaaa|__|___)_>aa`-.
           \_________|________/aaaaaaaa`----')SHIP";




const vector<string> SHIPS = {SHUTTLE_1, ENTERPRISE_1, ENTERPRISE_2, ENTERPRISE_3, BORG_CUBE, BIRD_OF_PREY_1, BIRD_OF_PREY_2};

// const vector<string> SHIPS = {ENTERPRISE_2};


/*==========================================
    Planet & moon & space element ASCII art
============================================*/

const string MOON_1 = R"MOON(   _..._   
 .::::.a`.
:::::::.aa:
::::::::aa:
`::::::'a.'
  `'::'-')MOON";

const string MOON_2 = R"MOON( ,-,-.
/.(a+.\
\a{.a*/
 `-`-')MOON";


const string MOON_3 = R"MOON( .-.
(a(
 `-')MOON";

const string PLANET_1 = R"PLANET(         _____
      .-'.aa':'-.
    .'':::a.:aaaa'.
   /aaa:::::'aaaaaa\
  ;.aaaa':'a`aaaaaaa;
  |aaaaaaa'..aaaaaaa|
  ;a'aaaaaa::::.aaaa;
   \aaaaaaa'::::aaa/
    '.aaaaaa:::aa.'
      '-.___'_.-')PLANET";

const string PLANET_2 = R"PLANET( .-.,="``"=. 
 '=/_aaaaaaa\  
  |aa'=._aaaa|
   \aaaaa`=./`,
    '=.__.='a`=')PLANET";

const string CONSTELLATION_1 = R"CONST(         '
    *          .
           *       '
      *                *)CONST";

const string CONSTELLATION_2 = R"CONST(   *   '*
           *
                *
                       *
               *
                     *)CONST";

const string CONSTELLATION_3 = R"CONST(   .       . 
 +  :      .
           :       _
       .   !   '  (_)
          ,|.' 
-  -- ---(-O-`--- --  -
         ,`|'`.
       ,   !    .
           :       :  " 
           .     --+--
 .:        .       !)CONST";


const string COMET_1 = R"COMET(                      .:'
         ....     _.::'
       .:-""-:.  (_.'
     .:/aaaaaa\:.
     :|aaaaaaaa|:
     ':\aaaaaa/:'
      '::-..-::'
        `''''`)COMET";


const vector<string> SPACE_ELEMENTS = {CONSTELLATION_1, CONSTELLATION_2, CONSTELLATION_3, PLANET_1, PLANET_2, COMET_1, MOON_1, MOON_2, MOON_3};
const vector<string> STARS = {".", "*", "'", "o", "O", "+", "0"};
const vector<string> COLORS = {"\x1b[31m", "\x1b[33m", "\x1b[32m", "\x1b[35m", "\x1b[37m", "\x1b[36m"};



vector<vector<char>> LiteralToMat(string literal) {
    std::stringstream ss(literal);
    std::string line;

    vector<vector<char>> mat;

    while (getline(ss, line, '\n'))
    {
        mat.push_back(vector<char>(line.begin(), line.end()));
    }

    return mat;
}


/**
 * Convert jagged matrix to square, get horiz dimension of mat
 */
int Squarify(vector<vector<char>>& mat)
{
    int maxLength = 0;

    for (vector<char> row : mat)
        if (row.size() > maxLength) maxLength = row.size();

    for (int i = 0; i < mat.size(); i++)
        while (mat[i].size() < maxLength)
            mat[i].push_back(' ');

    return maxLength;
}


// Reverse a 2d matrix & swap resversible chars
void Reverse(vector<vector<char>>& mat)
{
    for (int i = 0; i < mat.size(); i++)
        reverse(mat[i].begin(), mat[i].end());
    

    // eww
    for (int i = 0; i < mat.size(); i++) {
        for (int j = 0; j < mat[i].size(); j++) {
            switch (mat[i][j]) {
                case '/': {
                    mat[i][j] = '\\';
                    break;
                }
                case '\\': {
                    mat[i][j] = '/';
                    break;
                }
                case '(': {
                    mat[i][j] = ')';
                    break;
                }
                case ')': {
                    mat[i][j] = '(';
                    break;
                }
                case '[': {
                    mat[i][j] = ']';
                    break;
                }
                case ']': {
                    mat[i][j] = '[';
                    break;
                }
                case '{': {
                    mat[i][j] = '}';
                    break;
                }
                case '}': {
                    mat[i][j] = '{';
                    break;
                }
            }
        }
    }
}


// Overlay one matrix onto another
void Overlay(vector<vector<string>>& base, const vector<vector<char>>& overlay, int x, int y, string color = ENDC)
{
    for (int i = 0; i < overlay.size(); i++)
    {
        for (int j = 0; j < overlay[i].size(); j++)
        {
            if (overlay[i][j] == 'a') base[y + i][x + j] = ' ';
            else if (overlay[i][j] != ' ') base[y + i][x + j] = color +"\x1b[1m" + string(1, overlay[i][j]) + "\x1b[0m";
        }
    }
}



int main(int argc, char** argv) {

    // random seeding copied from stackoverflow :)
    uint32_t seed=0;
    FILE *devrnd = fopen("/dev/random","r");
    fread(&seed, 4, 1, devrnd);
    fclose(devrnd);
    srand(seed);
    

    int dimY = stoi(argv[1]);
    int dimX = stoi(argv[2]);

    // randomly generated starfield
    vector<vector<string>>  field(dimY - 2, vector<string>(dimX));
    
    // ascii-rendered starfield
    vector<vector<string>> render(dimY - 2, vector<string>(dimX));

    // initialize empty field
    for (int i = 0; i < field.size(); i++)
        for (int j = 0; j < field[i].size(); j++)
            field[i][j] = " ";

    int area = dimX * dimY;
    int clusterCount = round(max(1, area / 2000));

    vector<pair<int, int>> clusterCenters(clusterCount);

    for (int i = 0; i < clusterCount; i++)
    {
        clusterCenters[i] = pair<int, int>
        {
            round((rand() % (int)round(dimY - (2 * (dimY * VIGNETTE)))) + (dimY * VIGNETTE)),
            round((rand() % (int)round(dimX - (2 * (dimX * VIGNETTE)))) + (dimX * VIGNETTE)),
        };
    }


    for (int i = 0 ; i < field.size(); i++) {
        for (int j = PADDING; j < field[i].size() - PADDING; j++) {
            int minManhattanDistance = abs(i - clusterCenters[0].first) + abs(j - clusterCenters[0].second);
            int clusterIndex = 0;

            for (int c = 1; c < clusterCenters.size(); c++) {
                int manhattanDistance = abs(i - clusterCenters[c].first) + abs(j - clusterCenters[c].second);
                if (manhattanDistance < minManhattanDistance) {
                    minManhattanDistance = manhattanDistance;
                    clusterIndex = c;
                }
            }

            minManhattanDistance += 1;
            // minManhattanDistance *= 10;
            // minManhattanDistance -= 9;
            
            // cout << clusterIndex << ", " << minManhattanDistance << endl;

            // Find prob of placing a star based on the distance to the center of frame in order to create a cluster
            // (many of these numbers are arbitrary, just because they look good!)
            // int distanceToCenterHoriz = abs((int)(((field[i].size() - (PADDING * 2)) / 2) - (j - PADDING)));
            // int horizProbability = ((distanceToCenterHoriz * 1.2) + 1);
            // int probability = (int) (horizProbability * (1.0 + (abs((int)((field.size() / 2) - i)) + 1) / 2.0));


            // if (minManhattanDistance < 100) {
            if (rand() % max(1, (minManhattanDistance / 2)) == 0) {
                // Check for overcrowding of stars

                bool crowded = false;
                for (int x = 1; x <= HORIZ_PLACEMNET_PADDING; x++)
                    if (field[i][max(0, j - x)] != " " || field[i][min((int)field[i].size() - 1, j + x)] != " ")
                        crowded = true;
                for (int x = 1; x <= VERT_PLACEMENT_PADDING; x++)
                    if (field[(max(0, i - x))][j] != " " || field[(min((int)field.size() - 1, i + x))][j] != " ")
                        crowded = true;
                
                if (!crowded)
                    field[i][j] = STARS[rand() % STARS.size()];
            }
        }
    }


    // Add vertical padding to render canvas for special stars
    vector<string> row(dimX);
    for (int i = 0; i < row.size(); i++) row[i] = " ";
    render.insert(render.begin(), row);
    render.push_back(row);
    vector<char> skipChars = {'-', '|', '/', '\\'};

    vector<vector<string>> colorBands = {{"\x1b[31m", "\x1b[33m"}, {"\x1b[34m", "\x1b[35m"}, {"\x1b[36m", "\x1b[32m"}};
    // vector<vector<string>> colorBands = {{COLORS[0], COLORS[1]}, {COLORS[2], COLORS[3]}, {COLORS[4], COLORS[5]}};
    // vector<vector<string>> colorBands = {{COLORS[0]}, {COLORS[1]}, {COLORS[2]}, {COLORS[3]}, {COLORS[4]}, {COLORS[5]}};
    int bandCount = colorBands.size();
    std::random_shuffle(colorBands.begin(), colorBands.end());


    for (int i = 0; i < field.size(); i++) {
        for (int j = 0; j < field[i].size(); j++) {
            
            string color;
            
            // if we're in the right band, have a 50% chance of picking that band's color
            // bands are calculated radially using manhattan distance

            int band = (abs(i - (dimY / 2)) + abs(j - (dimX / 2))) / ((((dimX + dimY) + 2) / 2) / bandCount);
            assert(band < colorBands.size());

            // bias it towards using the band color but allow randomness too
            if (rand() % 10 < 4)
                color = colorBands[band][rand() % colorBands[band].size()];
            else
                color = COLORS[rand() % COLORS.size()];

            // get random number for the star decorations
            int randDec = rand() % 20;

            // Add surrounding flare to special stars
            if ((field[i][j] == "O" || field[i][j] == "0") && randDec < 15) {
                render[i+1][j-1] = color + "-" + ENDC;
                render[i+1][j+1] = color + "-" + ENDC;
            }
            if (field[i][j] == "0" && randDec < 10) {
                render[i][j] = color + "|" + ENDC;
                render[i+2][j] = color + "|" + ENDC;
            }
            if (field[i][j] == "0" && randDec < 1) {
                render[i+2][j-1] = color + "/" + ENDC;
                render[i+2][j+1] = color + "\\" + ENDC;
                render[i][j-1] = color + "\\" + ENDC;
                render[i][j+1] = color + "/" + ENDC;
            }


            // Place color and primary star char on canvas, but avoid overwriting existing chars
            // (can't do direct string comparison to check because colors are embedded in the strings)
            bool overWrite = true;

            for (char ch : skipChars)
                if (render[i+1][j].find(ch) != string::npos)
                    overWrite = false;
            
            if (overWrite)
                render[i+1][j] = color + field[i][j] + ENDC;
        }
    }

    
    // Add ship to rendered starfield

    for (string el : SPACE_ELEMENTS) {
        if (rand() % 5 == 0) {
            vector<vector<char>> elMat = LiteralToMat(el);
            int length = Squarify(elMat);
            int height = elMat.size();

            int x = rand() % (render[0].size() - length);
            int y = rand() % (render.size() - height);

            if (rand() % 2 == 0) Reverse(elMat);
            Overlay(render, elMat, x, y);
            // Overlay(render, elMat, x, y, COLORS[rand() % COLORS.size()]);
        }
    }

    
    int maxShipCount = max(1, clusterCount);
    int probability = 1;
    cout << maxShipCount << endl;

    for (int i = 0; i < maxShipCount; i++)
    {
        if (rand() % probability == 0)
        {
            vector<vector<char>> ship = LiteralToMat(SHIPS[rand() % SHIPS.size()]);
            int shipLength = Squarify(ship);
            int shipHeight = ship.size();

            int x = rand() % (render[0].size() - shipLength);
            int y = rand() % (render.size() - shipHeight);

            if (x + (shipLength / 2) > (dimX / 2))
                Reverse(ship);
            
            Overlay(render, ship, x, y);
            probability *= 4;
        }
    }

        // bool reverse = rand() % 1;
    // if (reverse) 

    

    // Print out canvas
    for (vector<string> x : render) {
        for (string str : x) cout << str;
        cout << endl;
    }
}