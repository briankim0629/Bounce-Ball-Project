// YOU DEFINITELY NEED TO MODIFY THIS FILE.

#include "view.hxx"
#include "model.hxx"

///
/// VIEW CONSTANTS
///

// Colors are red-green-blue(-alpha), each component
// from 0 to 255.
static ge211::Color const ball_color {255, 127, 127};
static ge211::Color const brick_color {100, 100, 100};
static ge211::Color const danger_color {255,0,0};
static ge211::Color const finish_color {255,255,0};
static std::string const bg_music_filename {"Bgmusic.mp3"};
static std::string const bounce_music_filename {"Bounce.mp3"};
static std::string const dead_music_filename {"Dead.mp3"};
static std::string const finish_music_filename {"Finish.mp3"};
///
/// VIEW CONSTRUCTOR
///

// Data members that are references cannot be initialized by assignment
// in the constructor body and must be initialized in a member
// initializer list.
View::View(Model const& m, ge211::Mixer& mixer)
        : model(m),
          ball_sprite(10, ball_color),
          brick_sprite({50,50}, brick_color),
          danger_sprite({50,50},danger_color),
          finish_sprite({50,50},finish_color),
          mixer_(mixer)


{
    if(mixer_.is_enabled()) {
        load_audio_();
    }
}


///
/// VIEW FUNCTIONS
///

// Use `Sprite_set::add_sprite(Sprite&, Position)` to add each sprite
// to `sprites`.


void
View::draw(ge211::Sprite_set& sprites)
{
    stage_number = {ge211::to_string(model.stage_counter), sans20};
    number_of_lives={ge211::to_string(model.lifecounter),sans20};
    sprites.add_sprite(ball_sprite,model.ball.top_left().into<int>());
    for(Block const& brick : model.bricks){
        sprites.add_sprite(brick_sprite,brick.top_left());
    }
    for(Block const& brick : model.danger_bricks){
        sprites.add_sprite(danger_sprite,brick.top_left());
    }
    for(Block const& brick : model.finish_bricks){
        sprites.add_sprite(finish_sprite,brick.top_left());
    }
    sprites.add_sprite(lives_left, {850,0});
    sprites.add_sprite(number_of_lives, {935,0});
    sprites.add_sprite(stage, {850, 30});
    sprites.add_sprite(stage_number, {925, 30});
    if(model.stage_counter == 5){
        sprites.add_sprite(win_screen, {120, 200});
        sprites.add_sprite(play_again, {140, 300});
    }



}

ge211::Dims<int>
View::initial_window_dimensions() const
{
    return model.config.scene_dims;
}


void
View::resume_music_if_ended() const
{
    if (mixer_.get_music_state() == ge211::Mixer::State::paused) {
        mixer_.resume_music();
    }
}
void
View::load_audio_()
{
    finish_sound_.try_load(finish_music_filename, mixer_);
    dead_sound_.try_load(dead_music_filename, mixer_);
    success_sound_.try_load(bounce_music_filename, mixer_);
    try {
        if (bg.try_load(bg_music_filename, mixer_)) {
            mixer_.play_music(bg);
        }
    } catch (ge211::Environment_error const& exn) {
        ge211::internal::logging::warn(exn.what())
                << "To enable background music, put a file named\n"
                << "Bgmusic.mp3" << " in the Resources/ directory.";
    }
}
void
View::set_animating(bool active)
{
    // If the sound effect should stop, reset the handle so that we
    // won't repeat the it again.
    if (!active) {
        success_handle_ = {};
    }

        // If the sound effect hasn't been started yet or has finished,
        // (re)start it.
    else if (success_handle_.empty() ||
             success_handle_.get_state() == ge211::Mixer::State::detached) {
        success_handle_ = mixer_.try_play_effect(success_sound_);
    }

        // If the sound effect is currently paused, resume it.
    else if (success_handle_.get_state() == ge211::Mixer::State::paused) {
        success_handle_.resume();
    }

    // Otherwise there is nothing to do.
}

void
View::set_animating2(bool active)
{
    // If the sound effect should stop, reset the handle so that we
    // won't repeat the it again.
    if (!active) {
        success_handle_ = {};
    }

        // If the sound effect hasn't been started yet or has finished,
        // (re)start it.
    else if (success_handle_.empty() ||
             success_handle_.get_state() == ge211::Mixer::State::detached) {
        success_handle_ = mixer_.try_play_effect(finish_sound_);
    }

        // If the sound effect is currently paused, resume it.
    else if (success_handle_.get_state() == ge211::Mixer::State::paused) {
        success_handle_.resume();
    }

    // Otherwise there is nothing to do.
}
void
View::set_animating3(bool active)
{
    // If the sound effect should stop, reset the handle so that we
    // won't repeat the it again.
    if (!active) {
        success_handle_ = {};
    }

        // If the sound effect hasn't been started yet or has finished,
        // (re)start it.
    else if (success_handle_.empty() ||
             success_handle_.get_state() == ge211::Mixer::State::detached) {
        success_handle_ = mixer_.try_play_effect(dead_sound_);
    }

        // If the sound effect is currently paused, resume it.
    else if (success_handle_.get_state() == ge211::Mixer::State::paused) {
        success_handle_.resume();
    }

    // Otherwise there is nothing to do.
}
bool
View::successsound(){
    return  model.bouncesound;
}
bool
View::finishsound(){
    return  model.finishsound;
}
bool
View::deadsound(){
    return  model.deadsound;
}
