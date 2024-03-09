#pragma once

#include "ball.hxx"
#include "game_config.hxx"
#include <vector>

// The logical state of the game.
struct Model
{
    explicit Model(Game_config const& config = Game_config());
    void launch();
    void on_frame(double dt);
    void movright();
    void movleft();
    void modstop();
    bool bouncesound = false;
    bool finishsound = false;
    bool deadsound = false;
    int stage_counter=1;
    int lifecounter = 5;
    void setbouncefalse();
    void setfinishfalse();
    void setdeadfalse();

    Game_config const config;

    std::vector<Block> bricks;
    std::vector<Block> danger_bricks;
    std::vector<Block> finish_bricks;

    Block paddle;

    Ball ball;

};

