#include "model.hxx"
#include <catch.hxx>

// We'll use this same game config throughout.
Game_config const config;


TEST_CASE("life loss") {
    //checks if life is lost due to falling off
    Model m(config);
    m.lifecounter = 2;
    m.stage_counter = 1;
    m.bricks.clear();


    m.ball.center.x = 500;
    m.ball.center.y = 500;
    m.ball.live = true;
    m.ball.velocity = {0, 50};
    Ball expected_ball(m.ball);

    double const dt = 0.125;
    auto check_frame = [&] {
        expected_ball = expected_ball.next(dt);
        m.on_frame(dt);
    };

    for (int i = 0; i<20; i++) {
        check_frame();
    }
    CHECK(m.stage_counter == 1);
    CHECK(m.lifecounter == 1);

}
TEST_CASE("life loss + stage change") {
    //goes from stage 4 to stage 1 if lifecounter hits 0. tests hitting
    // bottom and hitting the red danger block
    Model m(config);
    m.lifecounter = 1;
    m.stage_counter = 4;
    m.bricks.clear();


    m.ball.center.x = 500;
    m.ball.center.y = 500;
    m.ball.live = true;
    m.ball.velocity = {0, 50};
    Ball expected_ball(m.ball);

    double const dt = 0.125;
    auto check_frame = [&] {
        expected_ball = expected_ball.next(dt);
        m.on_frame(dt);
    };

    for (int i = 0; i<20; i++) {
        check_frame();
    }
    CHECK(m.stage_counter == 1);
    CHECK(m.lifecounter == 5);
    m.ball.live = false;
    m.lifecounter = 1;
    m.stage_counter = 4;
    m.bricks.clear();
    m.danger_bricks.clear();
    m.finish_bricks.clear();
    m.danger_bricks= std::vector<Block>();
    Block bric= {480,600,50,50};
    m.danger_bricks.push_back(bric);
    m.ball.center.x = 500;
    m.ball.center.y = 500;
    m.ball.live = true;
    m.ball.velocity = {0, 50};

    for (int i = 0; i<20; i++) {
        check_frame();
    }
    CHECK(m.stage_counter == 1);
    CHECK(m.lifecounter == 5);


}
TEST_CASE("resimulating stage 5 finish") {
    //tests that once the player hits the finish on stage 5, with more than 1
    // life left, goes back to stage 1 with all their lives back. Removes
    // error of having 1 life and resetting to stage 1 with full lives and
    // not clearing stage 5
    Model m(config);
    m.lifecounter = 2;
    m.stage_counter = 5;
    m.ball.center.x = 500;
    m.ball.center.y = 500;
    m.finish_bricks= std::vector<Block>();
    Block bric= {480,600,50,50};
    m.finish_bricks.push_back(bric);
    m.ball.live = true;
    m.ball.velocity = {0, 100};
    Ball expected_ball(m.ball);

    double const dt = 0.125;
    auto check_frame = [&] {
        expected_ball = expected_ball.next(dt);
        m.on_frame(dt);
    };
    for (int i = 0; i<20; i++) {
        check_frame();
    }
    CHECK(m.stage_counter == 1);
    CHECK(m.lifecounter == 5);

}
TEST_CASE("hitting red block") {
    //tests that hitting the red block will remove a life. Different from
    // falling off the platforms as this is also considered a platform, but
    // one that will take lives away and reset the ball
    Model m(config);
    m.lifecounter = 2;
    m.stage_counter = 2;
    m.ball.center.x = 500;
    m.ball.center.y = 500;
    m.danger_bricks= std::vector<Block>();
    Block bric= {480,600,50,50};
    m.danger_bricks.push_back(bric);
    m.ball.live = true;
    m.ball.velocity = {0, 100};
    Ball expected_ball(m.ball);

    double const dt = 0.125;
    auto check_frame = [&] {
        expected_ball = expected_ball.next(dt);
        m.on_frame(dt);
    };
    for (int i = 0; i<20; i++) {
        check_frame();
    }
    CHECK(m.stage_counter == 2);
    CHECK(m.lifecounter == 1);
}

TEST_CASE("game play through but instant finish every level") {
    //checks that the stage will change every time finish is hit and that on
    // stage 5, once finish is hit, stage will change to 1
    Model m(config);
    m.lifecounter = 5;
    m.stage_counter = 1;
    m.bricks.clear();
    m.finish_bricks.clear();
    m.danger_bricks.clear();
    m.ball.center.x = 500;
    m.ball.center.y = 500;
    m.finish_bricks= std::vector<Block>();
    Block bric= {480,600,50,50};
    m.finish_bricks.push_back(bric);
    m.ball.live = true;
    m.ball.velocity = {0, 100};
    Ball expected_ball(m.ball);

    double const dt = 0.125;
    auto check_frame = [&] {
        expected_ball = expected_ball.next(dt);
        m.on_frame(dt);
    };
    for (int i = 0; i<11; i++) {
        check_frame();
    }
    CHECK(m.stage_counter == 2);
    CHECK(m.lifecounter == 5);
    m.ball.live = false;

    m.ball.center.x = 500;
    m.ball.center.y = 500;
    m.bricks.clear();
    m.finish_bricks.clear();
    m.danger_bricks.clear();
    bric= {480,600,50,50};
    m.finish_bricks.push_back(bric);
    m.ball.live = true;
    m.ball.velocity = {0, 100};

    for (int i = 0; i<11; i++) {
        check_frame();
    }
    CHECK(m.stage_counter == 3);
    CHECK(m.lifecounter == 5);

    m.ball.live = false;

    m.ball.center.x = 500;
    m.ball.center.y = 500;
    m.bricks.clear();
    m.finish_bricks.clear();
    m.danger_bricks.clear();
    bric= {480,600,50,50};
    m.finish_bricks.push_back(bric);
    m.ball.live = true;
    m.ball.velocity = {0, 100};

    for (int i = 0; i<11; i++) {
        check_frame();
    }
    CHECK(m.stage_counter == 4);
    CHECK(m.lifecounter == 5);

    m.ball.live = false;

    m.ball.center.x = 500;
    m.ball.center.y = 500;
    m.bricks.clear();
    m.finish_bricks.clear();
    m.danger_bricks.clear();
    bric= {480,600,50,50};
    m.finish_bricks.push_back(bric);
    m.ball.live = true;
    m.ball.velocity = {0, 100};

    for (int i = 0; i<11; i++) {
        check_frame();
    }
    CHECK(m.stage_counter == 5);
    CHECK(m.lifecounter == 5);

    m.ball.live = false;

    m.ball.center.x = 500;
    m.ball.center.y = 500;
    m.bricks.clear();
    m.finish_bricks.clear();
    m.danger_bricks.clear();
    bric= {480,600,50,50};
    m.finish_bricks.push_back(bric);
    m.ball.live = true;
    m.ball.velocity = {0, 100};

    for (int i = 0; i<11; i++) {
        check_frame();
    }
    CHECK(m.stage_counter == 1);
    CHECK(m.lifecounter == 5);
}



//
// "WRITE MORE TESTS!!!" is never bad advice
//
