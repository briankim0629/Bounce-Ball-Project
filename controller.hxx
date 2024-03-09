// IT MIGHT BE OKAY TO MODIFY THIS FILE, BUT YOU PROBABLY DON'T
// WANT TO.
//
// Defines the structure and resources of the user interface.
//

#pragma once

#include "view.hxx"

#include <ge211.hxx>

struct Controller : ge211::Abstract_game
{
    //
    // CONSTRUCTOR
    //

    /// Constructs a `Controller` given a reference to the model that
    /// stores the actual state of the game.
    ///
    /// The word `explicit` means that this constructor doesn't define
    /// an implicit conversion whereby you could pass a `Model` to a
    /// function that expects a `Controller` and have it work.
    explicit Controller(Model&);


    //
    // MEMBER FUNCTIONS
    //

    /// Defines how the game responds to key events. There are two keys
    /// recognized:
    ///
    ///  - On 'q', quits.
    ///
    ///  - On ' ', tells the model to launch the ball.
    void on_key(ge211::Key) override;

    void on_key_down(ge211::Key) override;

    void on_key_up(ge211::Key) override;

    void on_frame(double dt) override;

    ge211::Dims<int> initial_window_dimensions() const override;

    /// The GE211 framework calls this at regular intervals to ask the
    /// game what should appear on the screen. It’s given a reference to
    /// an empty set of sprites (corresponding to painting the scene
    /// from scratch), to which it adds sprites at various positions,
    /// which the framework then renders to the screen. The
    /// implementation in controller.cxx delegates to view.draw(), since
    /// visuals are the view’s job.
    void draw(ge211::Sprite_set&) override;

    //
    // MEMBER VARIABLES
    //

    /// This is a reference to the model. It means that the controller
    /// doesn't own the model but has access to it. Thus, the client of
    /// the controller (brick_out.cxx) must create a `Model` first and
    /// then pass that by reference to the `Controller` constructor.
    Model& model;

    /// This is the view, which contains the game’s data and code for
    /// displaying the state of the model to the screen.
    View view;


};
