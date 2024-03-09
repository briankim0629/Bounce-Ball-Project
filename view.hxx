// IT MIGHT BE OKAY TO MODIFY THIS FILE, BUT YOU PROBABLY DON'T
// WANT TO.
//
// Defines the structure and resources of the user interface.
//

#pragma once

#include <ge211.hxx>


// Forward declaration of our model struct. This lets us use references
// to Model in this file even though the definition isn’t visible. (Just
// like in C.)
struct Model;

struct View
{
    explicit View(Model const&, ge211::Mixer&);

    ge211::Dims<int> initial_window_dimensions() const;
    void draw(ge211::Sprite_set&);
    void load_audio_();
    void resume_music_if_ended() const;
    void set_animating(bool);
    void set_animating2(bool);
    void set_animating3(bool);
    bool successsound();
    bool finishsound();
    bool deadsound();
    Model const& model;
    //int life_counter;
    ge211::Circle_sprite const ball_sprite;
    ge211::Rectangle_sprite const brick_sprite;
    ge211::Rectangle_sprite const danger_sprite;
    ge211::Rectangle_sprite const finish_sprite;
    ge211::Font const sans20{"sans.ttf", 20};
    ge211::Font const sans70{"sans.ttf", 70};
    ge211::Font const sans50{"sans.ttf", 50};
    ge211::Text_sprite lives_left {"lives left: ", sans20};
    ge211::Text_sprite number_of_lives;
    ge211::Text_sprite win_screen {"CONGRATS! YOU WON!", sans70};
    ge211::Text_sprite stage {"Stage #", sans20};
    ge211::Text_sprite play_again {"PRESS SPACE TO PLAY AGAIN!", sans50};
    ge211::Text_sprite stage_number;
    ge211::Mixer& mixer_;

    ge211::Sound_effect finish_sound_;
    ge211::Sound_effect dead_sound_;
    ge211::Sound_effect success_sound_;
    ge211::Music_track bg;
    ge211::Sound_effect_handle success_handle_;

};
