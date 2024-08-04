#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <cstdlib>
#include <time.h>
#include <vector>
using namespace std;

// Snake game -- ThatMatthewFellow

enum eDirection{
    STOP = 0,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

class cGameManager{
    public:
        cGameManager(int w, int h) {
            width = w;
            height = h;
            gameOver = false;
            dir = STOP;
            x = width / 2;
            y = height / 2;
            score = 0;
            nTail = 0;
            tailX.resize(100);
            tailY.resize(100);
            fruitPlacement();
            timer = clock();  // Initialize startTime here
        }

        void fruitPlacement(){
            srand(time(NULL));
            fruitX = rand() % width;
            fruitY = rand() % height;
            if(fruitX <= 0){
                fruitX = 1;
            }
            if(fruitY <= 0){
                fruitY = 1;
            }
            if(fruitX >= width-1){
                fruitX = width-2;
            }
            if(fruitY >= height-1){
                fruitY = height-2;
            }
        }

        void Input(){
            if(_kbhit()){
                switch(_getch()){
                    case 'a':
                        dir = LEFT;
                        break;
                    case 'd':
                        dir = RIGHT;
                        break;
                    case 'w':
                        dir = UP;
                        break;
                    case 's':
                        dir = DOWN;
                        break;
                    case 'q':
                        gameOver = true;
                        break;
                    default:
                        break;
                }
            }
        }

        void Draw(){
            system("cls");
            // Top wall
            for(int i = 0; i < width; i++){
                cout << "\xB2";
            }
            cout << endl;
            // Print the map
            for(int i = 0; i < height; i++){
                for(int j = 0; j < width; j++){
                    // Left wall
                    if(j == 0)
                        cout << "\xB2";
                    // The head of the snake
                    else if(i == y && j == x)
                        cout << "O";
                    // Fruit
                    else if(i == fruitY && j == fruitX)
                        cout << "\xDF";
                    // Right wall
                    else if(j == width-1)
                        cout << "\xB2";
                   // Tail
                   else{
                        print = false;
                        for(int k = 0; k < nTail; k++){
                            if(tailX[k] == j && tailY[k] == i){
                                cout << "o";
                                print = true;
                                break;
                            }
                        }
                        if(!print)
                            cout << " ";
                    }
                }
                cout << endl; // Print a newline character after each row of the game field
            }
            // Bottom wall
            for(int i = 0; i < width; i++){
                cout << "\xB2";
            }
            cout << endl; // Add this line to print the bottom wall correctly
            // Score
            cout << "Score: " << score << endl;
            // Calculate and display elapsed time
            float elapsedTime = (float)(clock() - timer) / CLOCKS_PER_SEC;
            cout << "Time played: " << elapsedTime << " seconds" << endl;
            
        }

        void Logic(){
            // Update tail segments
            if (nTail > 0){
                int prevTX = tailX[0];
                int prevTY = tailY[0];
                int prev2X;
                int prev2Y;
                for (int i = 1; i < nTail; i++) {
                    prev2X = tailX[i];
                    prev2Y = tailY[i];
                    tailX[i] = prevTX;
                    tailY[i] = prevTY;
                    prevTX = prev2X;
                    prevTY = prev2Y;
                }
                // Update the position of the last tail segment
                tailX[0] = x;
                tailY[0] = y;
            }
            // Direction switching
            switch(dir){
                case LEFT:
                    x--;
                    break;
                case RIGHT:
                    x++;
                    break;
                case UP:
                    y--;
                    break;
                case DOWN:
                    y++;
                    break;
                default:
                    break;
            }
            // Game over stuff
            if(x > width || x < 0 || y > height || y < 0)
                gameOver = true;
            // If you hit a tail segment, end game
            for(int i = 0; i < nTail; i++){
                if(tailX[i] == x && tailY[i] == y)
                    gameOver = true;
            }
            // Fruit 
            if(x == fruitX && y == fruitY){
                score += 10;
                nTail++;
                fruitPlacement();
            }
        }

        void Run(){
            while(!gameOver){
                Draw();
                Input();
                Logic();
                Sleep(95);
            }
            system("pause");
        }

    private:
        bool gameOver;
        int width;
        int height;
        int x;
        int y;
        int fruitX;
        int fruitY;
        int score;
        eDirection dir;
        vector<int> tailX;
        vector<int> tailY;
        int nTail;
        bool print;
        clock_t timer;
};  