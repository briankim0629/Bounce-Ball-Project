

#pragma once

#include "game_config.hxx"

#include <ge211.hxx>

#include <iostream>

using Position = ge211::Posn<float>;

using Velocity = ge211::Dims<float>;

using Block = ge211::Rect<int>;

struct Ball
{

    Ball(Block const& paddle, Game_config const&);

    Position top_left() const;

    Ball next(double dt) const;

    bool hits_top(Game_config const&) const;

    bool hits_bottom(Game_config const&) const;

    bool hits_side(Game_config const&) const;

    bool hits_leftblock(Block const&) const;

    bool hits_rightblock(Block const&) const;

    //bool hits_downblock(Block const&) const;

    bool hits_upblock(Block const&) const;

    bool hits_block(Block const&) const;

    bool hit_brick(std::vector<Block>& bricks) const;

    bool hit_leftbrick(std::vector<Block>& bricks) const;

    bool hit_rightbrick(std::vector<Block>& bricks) const;

    //bool hit_downbrick(std::vector<Block>& bricks) const;

    bool hit_upbrick(std::vector<Block>& bricks) const;

    void reflect_vertical();

    void reflect_horizontal();

    void moveright();
    void moveleft();
    void balstop();
    //
    // MEMBER VARIABLES
    //

    /// The radius of the ball.
    int radius;

    /// The position of the center of the ball.
    Position center;

    /// The velocity of the ball in pixels per tick.
    Velocity velocity;

    /// Whether the ball is moving freely (true) or stuck to the top of
    /// the paddle (false).
    bool live;
};

/// Compares two `Ball`s for equality. This may be useful for testing.
///
/// Two `Ball`s are equal if all their member variables are pairwise
/// equal.
bool
operator==(Ball const&, Ball const&);

/// Inequality for `Ball`s.
bool
operator!=(Ball const&, Ball const&);

/// Stream insertion (printing) for `Ball`. This can make your test
/// results easier to read.
std::ostream&
operator<<(std::ostream&, Ball const&);
