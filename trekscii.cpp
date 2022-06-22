#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>

using namespace std; // sorry bjarne

const int PADDING = 3;
const int HORIZ_PLACEMNET_PADDING = 4;
const int VERT_PLACEMENT_PADDING = 2;
const string ENDC = "\x1b[0m";


/*=====================================
    Star trek ship ASCII art
======================================*/

const string BIRD_OF_PREY_1 = R"SHIP(   __
 /|
/ \
\  \
}]::)==-{)
/  /
\ /
 \|__)SHIP";

const string BIRD_OF_PREY_2 = R"SHIP(     _o_
 _,---O---,_
 `         ')SHIP";

 const string ENTERPRISE_1 = R"SHIP(  ___---___  o==o====== 
============ ||//
        \ \ |//__
        \_______/)SHIP";

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

const string ENTERPRISE_2 = R"SHIP(___________________          _-_         
\__(==========/_=_/ ____.---'---`---.____
            \_ \    \----._________.----/
              \ \   /  /    `-_-'        
          __,--`.`-'..'-_                
         /____          ||               
              `--.____,-')SHIP";

const string SHUTTLE_1 = R"SHIP(   __________         
  // _|| _ | `.       
 //_/  |[_]|   `.     
/______|___|_____\    
\______|___|___,-'    
 [_][______][_>       )SHIP";

/* |                 _____
// |                /     \ 
// |               /|     |\
// |              /_|_____|_\
// |             _\_|_____|_/_
// |            <_>`-\___/-'<_>
*/

const string ENTERPRISE_3 = R"SHIP(  _      _-_      _
_|_|.---'---`---.|_|_
\----._________.----/
    `.  `]-['  ,'
      `.' _ `.'
       | (_) |
        `___')SHIP";

const vector<string> SHIPS = {SHUTTLE_1, ENTERPRISE_1, ENTERPRISE_2, ENTERPRISE_3, BORG_CUBE, BIRD_OF_PREY_1, BIRD_OF_PREY_2};


/*==========================================
    Planet & moon & space element ASCII art
============================================*/

const string MOON_1 = R"MOON(   _..._   
 .::::. `. 
:::::::.  :
::::::::  :  
`::::::' .'
  `'::'-')MOON";

const string MOON_2 = R"MOON( ,-,-.
/.( +.\
\ {. */
 `-`-')MOON";



const string PLANET_1 = R"PLANET(         _____
      .-'.  ':'-.
    .''::: .:    '.
   /   :::::'      \
  ;.    ':' `       ;
  |       '..       |
  ; '      ::::.    ;
   \       '::::   /
    '.      :::  .'
      '-.___'_.-')PLANET";

const string PLANET_2 = R"PLANET( .-.,="``"=. 
 '=/_       \  
  |  '=._    |
   \     `=./`,
    '=.__.=' `=')PLANET";

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
const string COMET_1 = R"COMET(                      .:'
         ....     _.::'
       .:-""-:.  (_.'
     .:/      \:.
     :|        |:
     ':\      /:'
      '::-..-::'
        `''''`)COMET";

const vector<string> SPACE_ELEMENTS = {MOON_1, MOON_2, PLANET_1, PLANET_2, CONSTELLATION_1, CONSTELLATION_2, COMET_1};



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
void Overlay(vector<vector<string>>& base, const vector<vector<char>>& overlay, int x, int y)
{
    for (int i = 0; i < overlay.size(); i++)
    {
        for (int j = 0; j < overlay[i].size(); j++)
        {
            if (overlay[i][j] != ' ') base[y + i][x + j] = overlay[i][j];
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
    
    // randomly generated starfield
    vector<vector<string>>  field(stoi(argv[1]) - 2, vector<string>(stoi(argv[2])));
    
    // ascii-rendered starfield
    vector<vector<string>> render(stoi(argv[1]) - 2, vector<string>(stoi(argv[2])));


    vector<string> stars = {".", "*", "'", "o", "O", "+", "0", "`"};
    vector<string> colors = {"\x1b[31m", "\x1b[33m", "\x1b[35m", "\x1b[37m", "\x1b[36m"};


    // initialize empty field
    for (int i = 0; i < field.size(); i++)
        for (int j = 0; j < field[i].size(); j++)
            field[i][j] = " ";


    for (int i = 0 ; i < field.size(); i++) {
        for (int j = PADDING; j < field[i].size() - PADDING; j++) {

            // Find prob of placing a star based on the distance to the center of frame in order to create a cluster
            // (many of these numbers are arbitrary, just because they look good!)
            int distanceToCenterHoriz = abs((int)(((field[i].size() - (PADDING * 2)) / 2) - (j - PADDING)));
            int horizProbability = ((distanceToCenterHoriz * 1.2) + 1);
            int probability = (int) (horizProbability * (1.0 + (abs((int)((field.size() / 2) - i)) + 1) / 2.0));


            if (rand() % probability == 0) {
                // Check for overcrowding of stars

                bool crowded = false;
                for (int x = 1; x <= HORIZ_PLACEMNET_PADDING; x++)
                    if (field[i][max(0, j - x)] != " " || field[i][min((int)field[i].size() - 1, j + x)] != " ")
                        crowded = true;
                for (int x = 1; x <= VERT_PLACEMENT_PADDING; x++)
                    if (field[(max(0, i - x))][j] != " " || field[(min((int)field.size() - 1, i + x))][j] != " ")
                        crowded = true;
                
                if (!crowded) {field[i][j] = stars[rand() % stars.size()];}
            }
        }
    }


    // Add vertical padding to render canvas for special stars
    vector<string> row(stoi(argv[2]));
    for (int i = 0; i < row.size(); i++) row[i] = " ";
    render.insert(render.begin(), row);
    render.push_back(row);


    for (int i = 0; i < field.size(); i++) {
        for (int j = 0; j < field[i].size(); j++) {
            string color = colors[rand() % colors.size()];

            // Add surrounding flare to special stars
            if (field[i][j] == "O" || field[i][j] == "0") {
                render[i+1][j-1] = color + "-" + ENDC;
                render[i+1][j+1] = color + "-" + ENDC;
            }
            if (field[i][j] == "0") {
                render[i][j] = color + "|" + ENDC;
                render[i+2][j] = color + "|" + ENDC;
            }


            // Place color and primary star char on canvas, but avoid overwriting existing chars
            // (can't do direct string comparison to check because colors are embedded in the strings)
            if (render[i+1][j].find('-') == string::npos && render[i+1][j].find('|') == string::npos) {
                render[i+1][j] = color + field[i][j] + ENDC;
            }
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
        }
    }


    vector<vector<char>> ship = LiteralToMat(SHIPS[rand() % SHIPS.size()]);
    int shipLength = Squarify(ship);
    int shipHeight = ship.size();

    int x = rand() % (render[0].size() - shipLength);
    int y = rand() % (render.size() - shipHeight);

    if (x < (render[0].size() / 2))
        Reverse(ship);
    
    Overlay(render, ship, x, y);


    //     bool reverse = rand() % 1;
    // if (reverse) 

    

    // Print out canvas
    for (vector<string> x : render) {
        for (string str : x) cout << str;
        cout << endl;
    }
}