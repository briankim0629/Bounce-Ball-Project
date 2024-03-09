// YOU DEFINITELY NEED TO MODIFY THIS FILE.

#include "ball.hxx"
#include "game_config.hxx"

// Computes where the ball should be when it's stuck to the paddle:
// centered above it, 1 pixel up.
static Position
above_block(
        Block const& block,
        Game_config const& config)
{
    Position blck = block.top_left().into<float>();
    int recthalf = block.width * 0.5;
    blck = blck.right_by(recthalf);
    blck = blck.up_by(1 + config.ball_radius);
    return blck;
}

// It won't compile without this, so you get it for free.

Ball::Ball(Block const& paddle, Game_config const& config)
        : radius(config.ball_radius),
          center(above_block(paddle, config)),
          velocity(Velocity(config.ball_velocity_0)),
          live(false)
{ }

Position
Ball::top_left() const
{
    Position ballpos = {center.x-radius, center.y-radius};
    return ballpos;
}


bool
Ball::hits_bottom(Game_config const& config) const
{
    float ballheight = center.y + radius;
    if(ballheight > config.scene_dims.height){
        return true;
    }
    return false;
}

// The ball hits the top when the y coordinate of its top is less than
// 0. (Note that the parameter isn't used.)
bool
Ball::hits_top(Game_config const&) const
{
    float ballheight = center.y - radius;
    if(ballheight < 0){
        return true;
    }
    return false;
}

// The ball hits a side when the x coordinate of its left side is
// less than 0 or the x coordinate of its right side is greater
// than the width of the scene.

// Recall that `this` is a `const Ball*`, and you can create a copy of a ball
// with the copy constructor. So to get a new `Ball` to return, you can write
//
//     Ball result(*this);
//
Ball
Ball::next(double dt) const
{
    Ball result(*this);
    result.center = result.center + (dt * result.velocity);
    return result;
}

bool
Ball::hits_side(Game_config const& config) const
{
    float ballx_right = center.x+radius;
    float ballx_left = center.x-radius;
    if(ballx_right >config.scene_dims.width||ballx_left < 0){
        return true;
    }
    return false;
}

bool
Ball::hits_leftblock(Block const& block) const
{
    float ballpos_xright = center.x+radius;
    float ballpos_xleft = center.x-radius;
    float ballpos_yup= center.y-radius;
    float ballpos_ydown= center.y+radius;
    return (ballpos_xright >=block.x && ballpos_xleft <= block.x &&
    ballpos_yup >= block.y && ballpos_ydown <= block.y+block.width);

}

bool
Ball::hits_rightblock(Block const& block) const
{
    float ballpos_xright = center.x+radius;
    float ballpos_xleft = center.x-radius;
    float ballpos_yup= center.y-radius;
    float ballpos_ydown= center.y+radius;
    return (ballpos_xright <=block.x+block.width && ballpos_xleft >= block.x
    && ballpos_yup >= block.y && ballpos_ydown <= block.y+block.width);
}
/*
bool
Ball::hits_downblock(Block const& block) const
{
    float ballpos_yup= center.y-radius;
    float ballpos_ydown= center.y+radius;
    float ballpos_xright = center.x+radius;
    float ballpos_xleft = center.x-radius;
    return(ballpos_yup <= block.y+block.height && ballpos_ydown >= block.y+block
    .height && ballpos_xleft >= block.x && ballpos_xright <= block.x+block
    .width);
}*/



bool
Ball::hits_block(Block const& block) const
{
    float ballpos_yup= center.y-radius;
    float ballpos_ydown= center.y+radius;
    float ballpos_xright = center.x+radius;
    float ballpos_xleft = center.x-radius;
    if(ballpos_xright < block.x){
        return false;
    }
    if(ballpos_xleft > (block.x+block.width)){
        return false;
    }
    if(ballpos_yup > (block.y+block.height)){
        return false;
    }
    if(ballpos_ydown < block.y){
        return false;
    }
    return true;
}

void
Ball::reflect_vertical()
{
    velocity.height *= -1;
}

void
Ball::reflect_horizontal()
{
    velocity.width *= -1;
}

void
Ball::moveright()
{
    velocity.width=300;
}
void
Ball::balstop()
{
    velocity.width=0;
    /*
    while(velocity.width>0){
        velocity.width -=30;
    }
    while(velocity.width <0){
        velocity.width += 30;
    }*/
}
void
Ball::moveleft()
{
    velocity.width =-300;
}
bool
Ball::hit_brick(std::vector<Block>& bricks) const
{

    for (Block& x: bricks){
        if(hits_block(x)){
            return true;
        }
    }
    return false;
}

bool
Ball::hit_leftbrick(std::vector<Block>& bricks)const
{
    for (Block& x: bricks){
        if(hits_leftblock(x)){
            return true;
        }
    }
    return false;
}

bool
Ball::hit_rightbrick(std::vector<Block>& bricks)const
{
    for (Block& x: bricks){
        if(hits_rightblock(x)){
            return true;
        }
    }
    return false;
}
/*
bool
Ball::hit_downbrick(std::vector<Block>& bricks) const
{
    for (Block& x: bricks){
        if(hits_downblock(x)){
            return true;
        }
    }
    return false;
}*/
/*
bool
Ball::hit_upbrick(std::vector<Block>& bricks) const
{
    for (Block& x: bricks){
        if(hits_upblock(x)){
            return true;
        }
    }
    return false;
}*/

bool
operator==(Ball const& a, Ball const& b)
{

    if(a.center==b.center && a.radius == b.radius && a.live == b.live && a
                                                                                 .velocity == b.velocity){
        return true;
    }
    return false;
}

bool
operator!=(Ball const& a, Ball const& b)
{
    return !(a == b);
}

std::ostream&
operator<<(std::ostream& o, Ball const& ball)
{
    // You may have seen this message when running your tests. It
    // would be more helpful if it showed the contents of each ball,
    // right? So you can make that happen by making this print the
    // contents of the ball (however you like).
    o << "Ball{";
    o << "vertical velocity == " << ball.velocity.height << "\n";
    o << "horizontal velocity == " << ball.velocity.width << "\n";
    return o << "}";
}

//hits sides, wall block,