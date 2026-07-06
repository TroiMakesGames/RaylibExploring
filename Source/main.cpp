#include "raylib.h"     //raylib framework/library
#include <vector>       //includes type dynamic arrays called vectors in c++
#include <iostream>     //console logging

class Player 
{
    // define class variables
    public:
        Vector2 pos = {100, 100};
        bool isDead = false;

    private:
        float size = 40.0f;
        float speed = 5.0f;

        int screenWidth;
        int screenHeight;


    // IMPORTANT NOTE: defining public/private functions follows the same principle as variables, but note that each decleration ("public:", "private:") continues until the end of the class
    //      meaning that if i were to remove the "public:" in the next line all the functions would be considered private due to the original variable acces declaration "private:" (for size and speed)
    public:
    // constructor with parameters
    Player(float x, float y, float size, float speed, int screenWidth, int screenHeight) {
        pos = {x, y};
        this->size = size;
        this->speed = speed;
        // NOTE: that the "this->" is only required when the variable names collide, therefore pos doesnt need it as the parameter arguments are seperated into x and y

        this->screenWidth = screenWidth;
        this->screenHeight = screenHeight;
    }

    // general functions
    void update() {
        if (IsKeyDown(KEY_W)) pos.y -= speed;
        if (IsKeyDown(KEY_S)) pos.y += speed;
        if (IsKeyDown(KEY_A)) pos.x -= speed;
        if (IsKeyDown(KEY_D)) pos.x += speed;

        //check if outside the screen, and set as dead
        if (pos.x > screenWidth || pos.x < 0 || pos.y > screenHeight || pos.y < 0)
        {isDead = true;}
    }

    void draw() {
        DrawRectangle(pos.x, pos.y, size, size, RED);
    }
};

int main() {
    //screen initialisation
    const int WIDTH = 800;
    const int HEIGHT = 600;
    InitWindow(WIDTH, HEIGHT, "raylib player example");
    SetTargetFPS(60);

    //variable initialisation
    std::vector<Player> players;    //a dynamic type array/vector (look at line 2 for extra info) of type Player

    Player player1(300, 400, 40, 5, WIDTH, HEIGHT);    //define 2 player objects
    Player player2(400, 400, 30, 4, WIDTH, HEIGHT);

    players.push_back(player1);         //append them to the players array
    players.push_back(player2);

    //while loop
    while (!WindowShouldClose()) {

        // update
        for (int i = 0; i < players.size(); i++)
        {
            players[i].update();
        }

        // draw
        BeginDrawing();
        ClearBackground(DARKGRAY);

        for (int i = 0; i < players.size(); i++)
        {
            players[i].draw();
        }

        EndDrawing();

        //safely delete dead objects
        // IMPORTANT NOTE: c++ doesnt have automatic garbage collection, so this kind of stuff has to be done safely
        //      in order to delete an object the erase() function can be used ... but note that erasing an object from an array at a specific index will move all further objects back by 1
        //          in order to deal with this in an easy way (to not skip an index) a backwards loop can be used
        for (int i = players.size() - 1; i >= 0; i--) 
        {
            if (players[i].isDead) {
                players.erase(players.begin() + i);     
                // NOTE: the erase() function doesnt use a standard python integer for an index at an array but it uses an iterator/pointer
                // thats why using players.begin() a new pointer is generated pointing at the first element and then incremented forward by i (+ operation) to reach the correct element
                
                //check if the manual garbage disposal works correctly
                std::cout << "Players: " << players.size() << std::endl;
            }
        }
    }

    CloseWindow();
    return 0;
}