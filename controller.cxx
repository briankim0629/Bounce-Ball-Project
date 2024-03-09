// YOU DEFINITELY NEED TO MODIFY THIS FILE.

#include "controller.hxx"
#include "model.hxx"

// Data members that are references cannot be initialized by assignment
// in the constructor body and must be initialized in a member
// initializer list.
Controller::Controller(Model& model)
        : model(model),
          view(model, mixer())




{

}

///
/// CONTROLLER FUNCTIONS
///

// You can get a `Key` representing space with `ge211::Key::code(' ')`.
void
Controller::on_key(ge211::Key key)
{
    if (key == ge211::Key::code('q')) {
        quit();
    }
    else if (key == ge211::Key::code(' ')){
        model.launch();
    }
}

void
Controller::on_key_down(ge211::Key key){
    if(key == ge211::Key::right()){
        model.movright();
    }
    else if(key == ge211::Key::left()){
        model.movleft();
    }
}
void
Controller::on_key_up(ge211::Key key){
    if(key == ge211::Key::right()){
        model.modstop();
    }
    else if(key == ge211::Key::left()){
        model.modstop();
    }
}
void
Controller::on_frame(double dt)
{
    model.on_frame(dt);
    view.resume_music_if_ended();
    view.set_animating(view.successsound());
    view.set_animating2(view.finishsound());
    view.set_animating3(view.deadsound());
    model.setbouncefalse();
    model.setdeadfalse();
    model.setfinishfalse();
}

ge211::Dims<int>
Controller::initial_window_dimensions() const
{
    return view.initial_window_dimensions();
}

void
Controller::draw(ge211::Sprite_set& sprites)
{
    view.draw(sprites);
}



