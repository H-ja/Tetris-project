#include <iostream>
#include <ctime>
#include <cstdlib>
#include <conio.h>
#include <windows.h>
#include <chrono>
#include <vector>
using namespace std;

int HEIGHT = 20 , WIDTH = 10;
long Score = 0;
int Lines = 0;
bool Game = true;
vector<long> TOPscores;

string red(const string& s) {
return "\033[91m" + s + "\033[0m";
}
string blue(const string& s) {
    return "\033[94m" + s + "\033[0m";
}
string magenta(const string& s) {
    return "\033[35m" + s + "\033[0m";
}
string yellow(const string& s) {
    return "\033[33m" + s + "\033[0m";
}
string green(const string& s) {
    return "\033[32m" + s + "\033[0m";
}
string ghost() {
    return "\033[90m#\033[0m";
}

struct Tetromino {
string shape[5][5];
int x , y;
string letter;
};
Tetromino T = {
{{"#","#","#",".","."},{".","#",".",".","."},{".",".",".",".","."},{".",".",".",".","."},{".",".",".",".","."}},
WIDTH/2 - 2 , 0,
"T"
};
Tetromino I = {
{{"#","#","#","#","."},{".",".",".",".","."},{".",".",".",".","."},{".",".",".",".","."},{".",".",".",".","."}},
WIDTH/2 - 2 , 0,
"I"
};
Tetromino O = {
{{"#","#",".","."},{"#","#",".","."},{".",".",".","."},{".",".",".","."}},
WIDTH/2 - 2 , 0,
"O"
};
Tetromino Z = {
{{"#","#",".",".","."},{".","#","#",".","."},{".",".",".",".","."},{".",".",".",".","."},{".",".",".",".","."}},
WIDTH/2 - 2 , 0,
"Z"
};
Tetromino L = {
{{"#",".",".",".","."},{"#","#","#",".","."},{".",".",".",".","."},{".",".",".",".","."},{".",".",".",".","."}},
WIDTH/2 - 2 , 0,
"L"
};

vector<Tetromino> t = {T , I , O , Z , L};

Tetromino ActivePiece = t[4];
Tetromino R = t[2];
Tetromino Hold_Piece;
bool Hold_flag = false;

string State = "PLAYING";
vector<vector<string>> Game_Board(HEIGHT, vector<string>(WIDTH, "."));

void Game_Menu();
void Clear_Screen();
void Render();
Tetromino Set_ActivePiece();
void Input(char k);
void Gravity();
void Lock_Tetromino();
bool NOspace();
bool Collision(int X , int Y , string test[5][5]);
void Rotate();
void Clear_Lines();
void MAIN();
void enter();
bool Hold_Valid();
void Hold();
void show_scores();

int main() {
enter();
while (Game)
Game_Menu();
return 0;}

void Game_Menu(){

cout << endl << endl << yellow("Choose an option below (then press Enter) :") << endl;
cout << yellow("1") << ". New game" << endl << yellow("2") << ". Setting" << endl << yellow("3") << ". Help" << endl << yellow("4") << ". Exit(hint: Exit the game to remove all the Tetrominos you made)" << endl << endl;
string option;      cin >> option;
if (!(option=="1" || option=="2" || option=="3" || option=="4")) { cout << "Invalid! Please try again." << endl << endl;
    Game_Menu();
}
if (option=="1") {system("cls"); State = "PLAYING" ; MAIN();}
else if (option=="2") {
cout << yellow("Choose an option below (then enter) :") << endl;
cout << "1. Change screen size" << endl << "2. Add new Tetromino" << endl << "3. Back" << endl;
int choice;
do {cin >> choice;} while(!(choice == 1 || choice == 2 || choice ==3));
if (choice == 1) {
int new_HEIGHT;
int new_WIDTH;
cout << yellow("Enter new HEIGHT") << "(Can be 10 or more): ";
do {cin >> new_HEIGHT;}
while (new_HEIGHT < 10);
cout << yellow("Enter new WIDTH") << "(Can be 20 or more): ";
do {cin >> new_WIDTH;}
while (new_WIDTH < 20);
HEIGHT = new_HEIGHT;
WIDTH = new_WIDTH;
Game_Board.assign(HEIGHT,vector<string>(WIDTH,"."));
T.x = WIDTH/2 - 2;
O.x = WIDTH/2 - 2;
L.x = WIDTH/2 - 2;
Z.x = WIDTH/2 - 2;
I.x = WIDTH/2 - 2;
ActivePiece.x = WIDTH/2 - 2;
R.x = WIDTH/2 - 2;
Game_Menu();}
else if (choice == 2) {
Tetromino x;
cout << yellow("Enter new piece shape") << ": " << endl;
cout << red("Note: After finishing each line press enter") << endl;
cout << red("New shape size should be a 5*5 Matrix") << endl;
cout << red("shape should only consist of (#) and (.) with a space between each one and cannot be empty") << endl;
cout << "example :# # # # #" << endl << "         . . # . ." << endl << "         . . # . ." <<
endl << "         . . # . ." << endl << "         . . # . ." << endl;

bool flag = true;
do {
for (int i = 0 ; i < 5 ; i++) {
    for (int j = 0 ; j < 5 ; j++) {
        string temp;
        do {cin >> temp;} while(!(temp == "#" || temp == "."));
        x.shape[i][j] = temp;
        if (temp == "#") flag = false;
    }
}
} while (flag);

int X = WIDTH/2 - 2;
int Y = 0;
x.x = X;
x.y = Y;
cout << yellow("Enter new piece name") << ": " << endl;
string Name;
cin.ignore();
getline(cin,Name);
x.letter = Name;

t.push_back(x);
Game_Menu();
}
}

else if (option=="3") {
    cout << red("           _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _") << endl;
    cout << red("           |                                                         |") << endl;
    cout << red("           |              ###  ###  ###  ###   #    ###              |") << endl;
    cout << red("           |               #    ##   #   # #   #    #                |") << endl;
    cout << red("           |               #   ###   #   #  #  #  ###                |") << endl;
    cout << red("           |                                                         |") << endl;
    cout << red("           |  ^ Press 1(then enter) to start a new game              |") << endl;
    cout << red("           |  ^ Press 2(then enter) to change game setting           |") << endl;
    cout << red("           |  ^ Press 4(then enter) to exit the game                 |") << endl;
    cout << red("           |                                                         |") << endl;
    cout << red("           |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _|") << endl << endl;
}
else if (option=="4") {
    cout << red("Are you sure you want to exit the game?") << "(Y/N)" << endl;
    string choice;      cin >> choice;
    while (! (choice == "Y" || choice == "y" || choice == "n" || choice == "N" || choice == "Yes" || choice == "yes" || choice == "YES" ||
    choice == "No" || choice == "no" || choice == "NO") )   cin >> choice;
    if (choice == "Y" || choice == "y" || choice == "Yes" || choice == "YES" || choice == "yes") {Game = false;}
}
}
void Clear_Screen(){ 
cout << "\033[H\033[J";
}
void Render() {

string Buffer{};
Clear_Screen();
Buffer += "Score: " + to_string(Score) + "      " + "Lines: " + to_string(Lines) + "        " +
"State: " + State + "\n";

for (int i = 0 ; i < t.size() ; i++) {
if (R.letter == t[i].letter) {
Buffer += yellow("Next Piece is") + " : " + green(R.letter) + "     ";
break;
}
}

if (Lines <= 6) {Buffer += yellow("Level") + " : " + green("1") + "     ";}
else if (Lines > 6 && Lines <= 12) {Buffer += yellow("Level") + " : " + green("2") + "     ";}
else if (Lines > 12) {Buffer += yellow("Level") + " : " + green("3") + "     ";}

Buffer += yellow("Hold Piece") + " : " + green(Hold_Piece.letter);
Buffer += "\n";

vector<vector<string>> frame(HEIGHT , vector<string>(WIDTH,"."));
for (int i = 0 ; i < HEIGHT ; i++) {
for (int j = 0 ; j < WIDTH ; j++) {
if (Game_Board[i][j] == "#")  frame[i][j] = blue("#");
}
}

for (int i = 0 ; i < 5 ; i++) {
    for (int j = 0 ; j < 5 ; j++) {
        if (ActivePiece.shape[i][j] == "#"){
        int y = i + ActivePiece.y;
        int x = j + ActivePiece.x;
        if (y >= 0 && y < HEIGHT && x >= 0 && x < WIDTH)
        frame[y][x] = magenta("#");
    }
}
}
int Min = HEIGHT;
for (int i = 0 ; i < 5 ; i++) {
    for (int j = 0 ; j < 5 ; j++) {
        if (ActivePiece.shape[i][j] == "#") {
            int Y = ActivePiece.y + i;
            int X = ActivePiece.x + j;
            int d = 0;
            while (Y+d+1 < HEIGHT && X >= 0 && X < WIDTH && Game_Board[Y+d+1][X] == ".") d++;
            if (d<Min) Min = d;
        }
    }
}

for (int i = 0 ; i < 5 ; i++) {
    for (int j = 0 ; j < 5 ; j++) {
        if (ActivePiece.shape[i][j] == "#") {
        int Y = ActivePiece.y + i + Min;
        int X = ActivePiece.x + j;
        if (Y >=0 && Y < HEIGHT && X >= 0 && X < WIDTH)
        frame[ActivePiece.y+i+Min][ActivePiece.x+j] = ghost();
    }
}
}

for (int i = 0 ; i < HEIGHT ; i++) {
    Buffer += red("|");
    for (int j = 0 ; j < WIDTH ; j++) {
        Buffer += frame[i][j] + " ";
    }
    Buffer += red("|");
    Buffer += "\n";
}
Buffer += red("+");
for (int k = 0 ; k < 2*WIDTH ; k++) Buffer += red("-");
Buffer += red("+");
Buffer += "\n";
Buffer += "Controls: " + green("w") + "=" + yellow("Rotate") + ", " + green("s") + "=" + yellow("SoftDrop") + ", " +
green("a") + "=" + yellow("Left") + ", " + green("d") + "=" + yellow("Right") + ", " + green("Space") + "=" + 
yellow("HardDrop") + ", " + green("h") + "=" + yellow("Hold") + ", " + green("q") + "=" + yellow("Quit") + ", " + green("p") + "=" + yellow("Pause") ;
cout << Buffer;
}
Tetromino Set_ActivePiece() {
int index;
index = rand() % t.size();
R = t[index];
return R;
}
void Input(char k){
if ((int)k >= 65 && (int)k <= 90) k += 32;

switch(k) {
    case 'h' :
    Hold();
    break;
    case ' ' :
    while (!Collision(ActivePiece.x , ActivePiece.y+1 , ActivePiece.shape)) {
    ActivePiece.y ++;
    }
    Lock_Tetromino();
    Clear_Lines();
    ActivePiece = R;
    R = Set_ActivePiece();
    break;
    case 'a' :
    if (!Collision(ActivePiece.x-1 , ActivePiece.y , ActivePiece.shape)) ActivePiece.x --;
    break;
    case 'd' :
    if (!Collision(ActivePiece.x+1 , ActivePiece.y , ActivePiece.shape)) ActivePiece.x ++;
    break;
    case 'w' :
    Rotate();
    break;
    case 's' :
    if (!Collision(ActivePiece.x , ActivePiece.y+1 , ActivePiece.shape)) Gravity();
    break;
    case 'q' :
    State = "GAME OVER";
    Beep(400,500);
    break;
    case 'p' :
    State = "PAUSED";
    cout << endl <<  "Continue Playing ? (y/n)\n";
    break;
    case 'y' :
    State = "PLAYING";
    break;
    case 'n' :
    State = "GAME OVER";
    Beep(400,500);
    break;
    default :
    break;
}}
void Gravity(){
ActivePiece.y ++;
}
void Lock_Tetromino(){
for (int i = 0 ; i < 5 ; i++) {
    for (int j = 0 ; j < 5 ; j++) {
        if (ActivePiece.shape[i][j] == "#") {
        int x = ActivePiece.x + j;
        int y = ActivePiece.y + i;
        if (y >= 0 && y < HEIGHT && x >= 0 && x < WIDTH)
        Game_Board[y][x] = "#";
        }
    }
}
Hold_flag = false;
R.x = WIDTH/2 - 2;
R.y = 0;
}
bool Collision(int X , int Y , string test[5][5]){
for (int i = 0 ; i < 5 ; i++) {
    for (int j = 0 ; j < 5 ; j++) {
        if (test[i][j] == "#") {
        int x = X + j;
        int y = Y + i;
        if (x < 0 || x >= WIDTH || y >= HEIGHT) return true;
        if (y >= 0) 
        if (Game_Board[y][x] == "#") return true;
        }
    }
}
return false;
}
bool NOspace(){
for (int j = 0 ; j < WIDTH ; j++) if (Game_Board[0][j]!=".") {State = "GAME OVER" ; Beep(400,500); return true;}
return false;
}
void Rotate(){

string temp[5][5];
for (int i = 0 ; i < 5 ; i++) {
    for (int j = 0 ; j < 5 ; j++) {
    temp[i][j] = ".";
    }
}

for (int i = 0 ; i < 5 ; i++) {
    for (int j = 0 ; j < 5 ; j++) {
        temp[j][4-i] = ActivePiece.shape[i][j];
    }
}
int offsets[5][2] = {{0,0},{-1,0},{1,0},{0,-1},{-2,0}};

for (int k = 0 ; k < 5 ; k++) {
    int X = ActivePiece.x + offsets[k][0];
    int Y = ActivePiece.y + offsets[k][1];
    if (!Collision(X,Y,temp)) {
    ActivePiece.x = X;
    ActivePiece.y = Y;

    for (int i = 0 ; i < 5 ; i++) {
    for (int j = 0 ; j < 5 ; j++) {
    ActivePiece.shape[i][j] = temp[i][j];
    }}
    Beep(600,50);
    break;
  }
 }
}
void Clear_Lines(){

unsigned temp_Lines = 0;

for (int i = HEIGHT - 1 ; i >= 0 ; i--) {
    bool flag = true;
    for (int j = 0 ; j < WIDTH ; j++) {
        if (Game_Board[i][j] != "#") {
        if (temp_Lines == 1)    Score += 100;
        else if (temp_Lines == 2)    Score += 300;
        else if (temp_Lines == 3)    Score += 500;
        else if (temp_Lines == 4)    Score += 800;
        else if (temp_Lines  > 4)    Score += 1000;
        temp_Lines = 0;
        flag = false; break;}
    }
    if (flag) {
        Lines ++;
        temp_Lines ++;
        for (int k = i ; k > 0 ; k--) {
            for (int h = 0 ; h < WIDTH ; h++) {
                Game_Board[k][h] = Game_Board[k-1][h];
            }
        }
        
        for (int h = 0 ; h < WIDTH ; h++)
        Game_Board[0][h] = ".";

        i++;
    }
}
Beep(1000,100);
}
void MAIN(){
srand(time(0));
auto Last_fall = chrono::steady_clock::now();
while (State != "GAME OVER") {
if (_kbhit()) {
char key = _getch();
Input(key);
}
if (NOspace()) {Render(); continue;}
if (State == "PAUSED") continue;
auto now = chrono::steady_clock::now();
int time = 600;
if (Lines <= 6)  time = 600;
else if (Lines > 6 && Lines <= 12)  time = 400;
else if (Lines > 12)  time = 200;
if (chrono::duration_cast<chrono::milliseconds>(now-Last_fall).count() > time) {

if (!Collision(ActivePiece.x , ActivePiece.y+1 , ActivePiece.shape)) Gravity();
else {Lock_Tetromino();
Clear_Lines();
ActivePiece = R;
R = Set_ActivePiece();
}

Last_fall = now;
}

Render();
Sleep(10);
}

cout << endl << "Final Score: " << Score << endl;
TOPscores.push_back(Score);
cout << yellow("TOP Scores") + " : ";
show_scores();

for (int i = 0 ; i < HEIGHT ; i++) {
    for (int j = 0 ; j < WIDTH ; j++) {
        Game_Board[i][j] = ".";
    }
}
Score = 0;
Lines = 0;
Hold_Piece.letter = " ";
}
void enter(){
cout<<blue("  _________________")<<endl;
cout<<blue(" | .-------------. |")<<endl;
cout<<blue(" | |             | |")<<endl;
cout<<blue(" | | ") << yellow("T E T R I S") << blue(" | | ")<<endl;
cout<<blue(" | |             | | ")<<endl;
cout<<blue(" | '-------------' |")<<endl;
cout<<blue("   `)___ ________(`|")<<endl;
cout<<blue("   [====  - - o   ]--.")<<endl;
cout<<blue(" __'- - - - - - - '___\\")<<endl;
cout<<blue("[:::::::::::::::  :::] )")<<endl;
}
bool Hold_Valid(){
for (int i = 0 ; i < 5 ; i++) {
    for (int j = 0 ; j < 5 ; j++) {
        if (Hold_Piece.shape[i][j] == "#") return true;
    }
}
return false;
}
void Hold(){
Hold_Piece.letter = ActivePiece.letter;
if (Hold_Valid()){
if (!Hold_flag) {

Tetromino temp = ActivePiece;
ActivePiece = Hold_Piece;
Hold_Piece = temp;
ActivePiece.x = WIDTH/2 - 2;
ActivePiece.y = 0;
Hold_flag = true;
}}

else {
Hold_Piece = ActivePiece;
ActivePiece = R;
R = Set_ActivePiece();
ActivePiece.x = WIDTH/2 - 2;
ActivePiece.y = 0;
}
}
void show_scores(){
long _1 = 0 , _2 = 0 , _3 = 0;
int d = TOPscores.size();
for (int i = 0 ; i < d - 1 ; i++) {
    for (int j = 0 ; j < d - 1 ; j++) {
        if (TOPscores[j] > TOPscores[j+1]) {
            long temp = TOPscores[j];
            TOPscores[j] = TOPscores[j+1];
            TOPscores[j+1] = temp;
        }
    }
}
if (d > 0) _1 = TOPscores[d-1];
if (d > 1) _2 = TOPscores[d-2];
if (d > 2) _3 = TOPscores[d-3];

if (_1 != 0) cout << "1. " << red(to_string(_1)) << "     ";
if (_2 != 0) cout << "2. " << red(to_string(_2)) << "     ";
if (_3 != 0) cout << "3. " << red(to_string(_3)) << "     ";
}