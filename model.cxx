// YOU DEFINITELY NEED TO MODIFY THIS FILE.

#include "model.hxx"


Model::Model(Game_config const& config)
        : config(config),
          paddle(Block::from_top_left(config.paddle_top_left_0(),
                                      config.paddle_dims)),
          ball(paddle, config)
{

    //stage 1
    int xpos = 0;
    int ypos = 650;
    for(int i =0; i<3;i++) {
        Block brix = {xpos, ypos, 50, 50};
        bricks.push_back(brix);
        xpos += 55;
    }
    xpos+= 55;
    for(int i =0; i<2;i++){
        Block brix = {xpos,ypos,50,50};
        bricks.push_back(brix);
        xpos += 55;
    }
    Block bric= {xpos +=55*3,ypos,50,50};
    bricks.push_back(bric);
    bric = {xpos += 55*2, ypos - 55*2,50,50};
    bricks.push_back(bric);
    bric = {xpos-= 55*2, ypos - 55*4,50,50};
    bricks.push_back(bric);
    bric = {xpos+= 55*2, ypos - 55*6,50,50};
    bricks.push_back(bric);
    int xpos_danger= 55*8;
    xpos_danger -=80;
    int ypos_danger = 650;
    //danger brick
    for(int i = 0; i < 2; i ++){
        Block danblock = {xpos_danger, ypos_danger, 50,50};
        danger_bricks.push_back(danblock);
        xpos_danger += 55;
    }
    //finish brick
    Block finblk = {920,650,50,50};
    finish_bricks.push_back(finblk);
}

// Freebie.
void
Model::launch()
{
    ball.live = true;
}

void
Model::on_frame(double dt)
{
    if(ball.live){

        Ball next_ball = ball.next(dt);
        //diagonal cases
        if(next_ball.hits_bottom(config)){
            ball.live = false;
            ball.center.x = paddle.top_left().x;
            ball.center.y = paddle.top_left().y;
            ball.velocity.height = 0;
            ball.velocity.width = 0;
            deadsound = true;
            if(lifecounter >1){
                lifecounter-=1;
            }
            else if(lifecounter == 1){
                stage_counter = 1;
                ball.velocity.height = 0;
                ball.velocity.width = 0;
                paddle.x =50;
                paddle.y = 450;
                ball.center.x = paddle.x;
                ball.center.y = paddle.y;
                bricks = std::vector<Block>();
                finish_bricks= std::vector<Block>();
                danger_bricks = std::vector<Block>();
                int xpos = 0;
                int ypos = 650;
                for(int i =0; i<3;i++) {
                    Block brix = {xpos, ypos, 50, 50};
                    bricks.push_back(brix);
                    xpos += 55;
                }
                xpos+= 55;
                for(int i =0; i<2;i++){
                    Block brix = {xpos,ypos,50,50};
                    bricks.push_back(brix);
                    xpos += 55;
                }
                Block bric= {xpos +=55*3,ypos,50,50};
                bricks.push_back(bric);
                bric = {xpos += 55*2, ypos - 55*2,50,50};
                bricks.push_back(bric);
                bric = {xpos-= 55*2, ypos - 55*4,50,50};
                bricks.push_back(bric);
                bric = {xpos+= 55*2, ypos - 55*6,50,50};
                bricks.push_back(bric);
                int xpos_danger= 55*8;
                xpos_danger -=80;
                int ypos_danger = 650;
                //danger brick
                for(int i = 0; i < 2; i ++){
                    Block danblock = {xpos_danger, ypos_danger, 50,50};
                    danger_bricks.push_back(danblock);
                    xpos_danger += 55;
                }
                //finish brick
                Block finblk = {920,650,50,50};
                finish_bricks.push_back(finblk);
                lifecounter = 5;
            }
            return;
        }
        if(next_ball.hits_top(config) && next_ball.hits_side(config)){
            ball.reflect_vertical();
            ball.reflect_horizontal();
        }
        else if(next_ball.hits_bottom(config) && next_ball.hits_side(config)){
            ball.reflect_vertical();
            ball.reflect_horizontal();

        }
        else if(next_ball.hit_leftbrick(bricks) && next_ball.hit_brick(bricks)){
            //ball.reflect_horizontal();
            ball.velocity.width = -300;
        }
        else if(next_ball.hit_rightbrick(bricks) && next_ball.hit_brick(bricks)){
            //ball.reflect_horizontal();
            ball.velocity.width = 300;
        }/*
        else if(next_ball.hit_downbrick(bricks) && next_ball.hit_brick(bricks)){
            //ball.reflect_vertical();
            ball.velocity.height = 800;
        }*/
        else if(next_ball.hit_brick(bricks)){
            ball.velocity.height = -800;
            bouncesound = true;
        }
        else if(next_ball.hit_brick(danger_bricks)){
            ball.live =false;
            ball.center.x = paddle.top_left().x;
            ball.center.y = paddle.top_left().y;
            ball.velocity.height = 0;
            ball.velocity.width = 0;
            deadsound = true;
            if(lifecounter >1){
                lifecounter-=1;
            }
            else if(lifecounter == 1){
                stage_counter = 1;
                ball.velocity.height = 0;
                ball.velocity.width = 0;
                paddle.x =50;
                paddle.y = 450;
                ball.center.x = paddle.x;
                ball.center.y = paddle.y;
                bricks = std::vector<Block>();
                finish_bricks= std::vector<Block>();
                danger_bricks = std::vector<Block>();
                int xpos = 0;
                int ypos = 650;
                for(int i =0; i<3;i++) {
                    Block brix = {xpos, ypos, 50, 50};
                    bricks.push_back(brix);
                    xpos += 55;
                }
                xpos+= 55;
                for(int i =0; i<2;i++){
                    Block brix = {xpos,ypos,50,50};
                    bricks.push_back(brix);
                    xpos += 55;
                }
                Block bric= {xpos +=55*3,ypos,50,50};
                bricks.push_back(bric);
                bric = {xpos += 55*2, ypos - 55*2,50,50};
                bricks.push_back(bric);
                bric = {xpos-= 55*2, ypos - 55*4,50,50};
                bricks.push_back(bric);
                bric = {xpos+= 55*2, ypos - 55*6,50,50};
                bricks.push_back(bric);
                int xpos_danger= 55*8;
                xpos_danger -=80;
                int ypos_danger = 650;
                //danger brick
                for(int i = 0; i < 2; i ++){
                    Block danblock = {xpos_danger, ypos_danger, 50,50};
                    danger_bricks.push_back(danblock);
                    xpos_danger += 55;
                }
                //finish brick
                Block finblk = {920,650,50,50};
                finish_bricks.push_back(finblk);
                lifecounter =5;
            }
        }
        else if(next_ball.hit_brick(finish_bricks)){
            finishsound = true;
            if (stage_counter <5){
                stage_counter++;
            }
            else{
                stage_counter =1;
                lifecounter = 5;
            }
            ball.live = false;
            if(stage_counter ==1){

                ball.velocity.height = 0;
                ball.velocity.width = 0;
                paddle.x =50;
                paddle.y = 450;
                ball.center.x = paddle.x;
                ball.center.y = paddle.y;
                bricks = std::vector<Block>();
                finish_bricks= std::vector<Block>();
                danger_bricks = std::vector<Block>();
                int xpos = 0;
                int ypos = 650;
                for(int i =0; i<3;i++) {
                    Block brix = {xpos, ypos, 50, 50};
                    bricks.push_back(brix);
                    xpos += 55;
                }
                xpos+= 55;
                for(int i =0; i<2;i++){
                    Block brix = {xpos,ypos,50,50};
                    bricks.push_back(brix);
                    xpos += 55;
                }
                Block bric= {xpos +=55*3,ypos,50,50};
                bricks.push_back(bric);
                bric = {xpos += 55*2, ypos - 55*2,50,50};
                bricks.push_back(bric);
                bric = {xpos-= 55*2, ypos - 55*4,50,50};
                bricks.push_back(bric);
                bric = {xpos+= 55*2, ypos - 55*6,50,50};
                bricks.push_back(bric);
                int xpos_danger= 55*8;
                xpos_danger -=80;
                int ypos_danger = 650;
                //danger brick
                for(int i = 0; i < 2; i ++){
                    Block danblock = {xpos_danger, ypos_danger, 50,50};
                    danger_bricks.push_back(danblock);
                    xpos_danger += 55;
                }
                //finish brick
                Block finblk = {920,650,50,50};
                finish_bricks.push_back(finblk);
            }
            if(stage_counter ==2){
                ball.velocity.height = 0;
                ball.velocity.width = 0;
               bricks = std::vector<Block>();
               finish_bricks= std::vector<Block>();
               danger_bricks = std::vector<Block>();
               Block bric= {100 ,300,50,50};
               //determines which blocks are on the board. Push backs into
               // vectors listed above.
                bricks.push_back(bric);
                bric = {200 ,600,50,50};
                bricks.push_back(bric);
                for(int x = 1; x < 8; x++) {
                    bric = {200 + (55*x) ,600,50,50};
                    bricks.push_back(bric);
                }
                bric = {200 + (55*1) ,545,50,50};
                danger_bricks.push_back(bric);
                bric = {200 + (55*3) ,545,50,50};
                danger_bricks.push_back(bric);
                bric = {200 + (55*5) ,545,50,50};
                danger_bricks.push_back(bric);
                for (int i = 4; i < 10; i++) {
                    bric = {200 + (55*1) ,600 - (55*i),50,50};
                    danger_bricks.push_back(bric);
                }
                bric = {200 + (55*10) ,545,50,50};
                finish_bricks.push_back(bric);
                //spawn point
                paddle.x= 125;
                paddle.y= 260;
                ball.center.x = paddle.x;
                ball.center.y =paddle.y;
            }
            if (stage_counter == 3) {
                ball.velocity.height = 0;
                ball.velocity.width = 0;
                bricks = std::vector<Block>();
                finish_bricks= std::vector<Block>();
                danger_bricks = std::vector<Block>();
                Block bric= {100 ,700,50,50};
                bricks.push_back(bric);
                bric= {100 ,450,50,50};
                bricks.push_back(bric);
                bric= {100 ,200,50,50};
                bricks.push_back(bric);
                bric= {250 ,700,50,50};
                bricks.push_back(bric);
                bric= {375 ,575,50,50};
                bricks.push_back(bric);
                bric= {275 ,450,50,50};
                bricks.push_back(bric);
                bric= {400 ,325,50,50};
                bricks.push_back(bric);
                bric= {550 ,325,50,50};
                bricks.push_back(bric);
                bric= {700 ,325,50,50};
                bricks.push_back(bric);
                bric= {700 ,700,50,50};
                bricks.push_back(bric);
                bric= {850 ,575,50,50};
                finish_bricks.push_back(bric);

                for (int i = 0; i<9; i++) {
                    bric= {155 ,450 - (55*i),50,50};
                    danger_bricks.push_back(bric);
                }
                for (int i =1; i<4; i++) {
                    bric= {800 + (50*i) ,520,50,50};
                    danger_bricks.push_back(bric);
                }

                paddle.x= 125;
                paddle.y= 100;
                ball.center.x = paddle.x;
                ball.center.y =paddle.y;
            }
            if (stage_counter == 4) {
                ball.velocity.height = 0;
                ball.velocity.width = 0;
                ball.live = false;
                paddle.x= 125;
                paddle.y= 100;
                bricks = std::vector<Block>();
                finish_bricks= std::vector<Block>();
                danger_bricks = std::vector<Block>();
                Block bric= {850 ,200,50,50};
                bricks.push_back(bric);
                for (int i = 0; i < 5; i ++) {
                    bric= {700 - (150*i) ,200,50,50};
                    bricks.push_back(bric);
                }
                for (int i = 0; i < 6; i++) {
                    bric= {775 - (150*i) ,150,50,50};
                    danger_bricks.push_back(bric);
                    bric= {775 - (150*i) ,-20,50,50};
                    danger_bricks.push_back(bric);
                }
                bric= {850 ,700,50,50};
                bricks.push_back(bric);
                for (int i = 0; i < 4; i ++) {
                    bric= {700 - (150*i) ,700,50,50};
                    bricks.push_back(bric);
                }
                bric= {700 - (150*4) ,700,50,50};
                finish_bricks.push_back(bric);
                for (int i = 0; i < 6; i++) {
                    bric= {775 - (150*i) ,650,50,50};
                    danger_bricks.push_back(bric);
                    bric= {775 - (150*i) ,480,50,50};
                    danger_bricks.push_back(bric);
                }
                ball.center.x = paddle.x;
                ball.center.y =paddle.y;
            }
            if (stage_counter == 5) {
                ball.velocity.width=0;
                ball.velocity.height = 1000;
                bricks = std::vector<Block>();
                finish_bricks= std::vector<Block>();
                danger_bricks = std::vector<Block>();
                paddle.x= 500;
                paddle.y= 500;
                ball.center.x = paddle.x;
                ball.center.y =paddle.y;
                Block bric= {480,600,50,50};
                finish_bricks.push_back(bric);
            }
        }

        else if (next_ball.hits_top(config)){
            ball.reflect_vertical();
        }
        else if(next_ball.hits_side(config)){
            ball.reflect_horizontal();
        }
        if(ball.velocity.height <1200){
            ball.velocity.height += 40;
        }
        ball = ball.next(dt);
    }
}


void
Model::movright()
{
    ball.moveright();
}
void
Model::movleft()
{
    ball.moveleft();
}

void
Model::modstop(){
    ball.balstop();
}

void
Model::setbouncefalse()
{
    bouncesound= false;
}
void
Model::setfinishfalse()
{
    finishsound= false;
}
void
Model::setdeadfalse()
{
    deadsound= false;
}