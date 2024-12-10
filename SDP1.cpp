#include <iostream>
#include <conio.h>
#include <windows.h>
#include <cmath>
#include <fstream>

using namespace std;

const int width = 20;
const int height = 20;

int planeX, planeY;
int missile1X, missile1Y;
int missile2X, missile2Y;
int score = 0;
bool gameOver = false;
float missileSpeed = 1.2f;
int gameSpeed = 150;
bool hardMode = false;

void Setup();
void Draw();
void Input();
void Logic();
void Menu();
void SaveScore(int score);

void Setup() {
    planeX = width / 2;
    planeY = height / 2;
    missile1X = rand() % width;
    missile1Y = rand() % height;

    if (hardMode) {
        missile2X = rand() % width;
        missile2Y = rand() % height;
    }

    score = 0;
    gameOver = false;
}

void Draw() {
    system("cls");

    for (int i = 0; i < width + 2; ++i) {
        cout << "#";
    }
    cout << endl;

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width + 2; ++x) {
            if (x == 0 || x == width + 1) {
                cout << "#";
            } else if (x - 1 == planeX && y == planeY) {
                cout << "P";
            } else if (x - 1 == missile1X && y == missile1Y) {
                cout << "M";
            } else if (hardMode && x - 1 == missile2X && y == missile2Y) {
                cout << "M";
            } else {
                cout << " ";
            }
        }
        cout << endl;
    }

    for (int i = 0; i < width + 2; ++i) {
        cout << "#";
    }
    cout << endl;

    cout << "Score: " << score << endl;
}

void Input() {
    if (_kbhit()) {
        switch (_getch()) {
            case 'w': planeY--; break;
            case 's': planeY++; break;
            case 'a': planeX--; break;
            case 'd': planeX++; break;
        }
    }
}

void MoveMissile(int& missileX, int& missileY) {
    int dx = planeX - missileX;
    int dy = planeY - missileY;
    float dist = sqrt(dx * dx + dy * dy);

    missileX += (int)(missileSpeed * (dx / dist));
    missileY += (int)(missileSpeed * (dy / dist));
}

void Logic() {
    MoveMissile(missile1X, missile1Y);

    if (hardMode) {
        MoveMissile(missile2X, missile2Y);
    }

    if ((missile1X == planeX && missile1Y == planeY) ||
        (hardMode && missile2X == planeX && missile2Y == planeY)) {
        gameOver = true;
    }

    if (planeX < 0 || planeX >= width || planeY < 0 || planeY >= height) {
        gameOver = true;
    }

    score++;
}

void SaveScore(int score) {
    ofstream outFile("highscore.txt", ios::app);
    if (outFile.is_open()) {
        outFile << "Score: " << score << endl;
        outFile.close();
        cout << "Score saved successfully!" << endl;
    } else {
        cout << "Error saving score." << endl;
    }
    system("pause");
}

void Menu() {
    int choice;
    bool running = true;

    while (running) {
        system("cls");
        cout << "==== Plane and Missile Game ====\n";
        cout << "1. Start Game (Easy)\n";
        cout << "2. Start Game (Hard)\n";
        cout << "3. Save Score\n";
        cout << "4. Exit\n";
        cout << "Select an option: ";
        cin >> choice;

        switch (choice) {
            case 1:
                hardMode = false;
                Setup();
                while (!gameOver) {
                    Draw();
                    Input();
                    Logic();
                    Sleep(gameSpeed);
                }
                cout << "Game Over! Final Score: " << score << endl;
                system("pause");
                break;

            case 2:
                hardMode = true;
                Setup();
                while (!gameOver) {
                    Draw();
                    Input();
                    Logic();
                    Sleep(gameSpeed);
                }
                cout << "Game Over! Final Score: " << score << endl;
                system("pause");
                break;

            case 3:
                SaveScore(score);
                break;

            case 4:
                running = false;
                break;

            default:
                cout << "Invalid option. Please try again.\n";
                system("pause");
        }
    }
}

int main() {
    Menu();
    return 0;
}
