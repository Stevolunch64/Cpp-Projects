// Pong.cpp : Defines the entry point for the console application.

#include "Bat.h"
#include "Ball.h"
#include <sstream>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <string>

int main()
{
    // Create a video mode object
    VideoMode vm(1680, 1050);

    // Create and open a window for the game
    RenderWindow window(vm, "Pong", Style::Fullscreen);

    // Create score, lives, and time counting variable
    int score = 0;
    int lives = 1;  // Start with 1 life (ball)
    float totalTime = 0;
    double totalScore = 0;

    // Create variable to check if the game is running
    //Will be true before the game starts or if a game over occurs (lives = 0)
    bool paused = true;

    //Enable and disable arrow input when necessary
    //Will be true while game is being played
    bool acceptInput = false;


    // Create a bat (the bat the player controls)
    Bat bat(1680 / 2, 1050 - 20, Color::White);


    //Create the doubleBat
    //This will double the bat's width when a ball hits it
    //(set the position to negative values so it doesn't appear on the screen initially)
    Bat doubleBat(-100, -300, Color::Green);

    //boolean that will become true to activate the doubleBat bat
    bool makeDouble = false;


    //Create the speed slash bat, which will half the ball's speed that hits it
    Bat slashBat(-200, -400, Color::Magenta);

    //boolean that will activate the slashBat if true
    bool makeSlash = false;


    //Create the height restart bat, which will bring the bat back down the screen
    Bat heightBat(-200, -400, Color::Blue);

    //boolean that will activate the heightBat if true
    bool makeHeight = false;


    // Create a green ball, that can activate the doubleBat powerup
    Ball ball1(1680 / 2, 50, 600, Color::Green);

    //Create a magenta ball, that can activate the slashBat powerup
    Ball ball2(100, 50, 0, Color::Magenta);

    //Create a blue ball, that can activate the heightBat powerup
    Ball ball3(150, 50, 0, Color::Blue);



    //boolean that will become true to spawn the second ball in
    bool makeBall2 = false;

    //boolean that will become true to spawn the third ball in
    bool makeBall3 = false;


    // Create a Text object called HUD
    Text hud;

    // A cool retro-style font
    Font font;
    font.loadFromFile("fonts/DS-DIGI.ttf");

    // Set the font to our retro-style
    hud.setFont(font);

    // Make it nice and big
    hud.setCharacterSize(50);

    // Choose a color
    hud.setFillColor(Color::White);

    hud.setPosition(20, 20);

    // Create a Text object for messages
    sf::Text messageText;
    messageText.setFont(font);
    messageText.setCharacterSize(50);
    messageText.setFillColor(Color::White);
    messageText.setString("Press Enter to Start!\nGreen bat doubles your width\nMagenta bat slows down balls\nBlue bat resets height\nGet the power up by hitting it with the matching ball");
    messageText.setPosition(1680 / 2 - 300, 1050 / 2 - 100); // Center the message

    // Here is our clock for timing everything
    Clock clock;

    while (window.isOpen())
    {
        /*
        Handle the player input
        *********************************************************************
        *********************************************************************
        *********************************************************************
        */

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                // Quit the game when the window is closed
                window.close();
        }

        // Handle the player quitting
        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            window.close();
        }

        // Start or restart the game
        if (Keyboard::isKeyPressed(Keyboard::Return))
        {
            if (paused)
            {
                paused = false; //Unpause the game
                acceptInput = true; //Begin accepting input
                totalTime = 0; //Reset the timer
                score = 0;     // Reset score
                lives = 1;     // Reset lives

                bat.setPosition(1680 / 2, 1050 - 20); // Reset bat position
                bat.changeSize(100, 5);//Reset the bat size

                //Reset the power up bats' positions
                doubleBat.setPosition(-200, -400);
                slashBat.setPosition(-200, -400);
                heightBat.setPosition(-200, -400);

                ball1.setSpeed(1000);//Restart the ball speed
                ball1.setPosition(1680 / 2, 50); // Reset ball position 
                ball1.reboundBatOrTop();//Send the ball moving down

                ball2.setSpeed(0);//Restart the second ball speed
                ball2.setPosition(1680 / 2, 50); // Reset second ball position 

                ball3.setSpeed(0);//Reset the third ball speed
                ball3.setPosition(1680 / 2, 50); // Reset third ball position
                
                clock.restart();//Reset the clock
                makeDouble = false; //Reset the doubleBat creation boolean
                makeSlash = false; //Reset the makeSlash creation boolean
                makeHeight = false; //Reset the makeHeight creation boolean
                makeBall2 = false; //Reset the makeBall2 boolean
                makeBall3 = false; //Reset the makeBall2 boolean
            }
        }

        // Handle the pressing and releasing of the arrow keys
        if (acceptInput)
        {
            if (Keyboard::isKeyPressed(Keyboard::Left))
            {
                bat.moveLeft();
            }
            else
            {
                bat.stopLeft();
            }

            if (Keyboard::isKeyPressed(Keyboard::Right))
            {
                bat.moveRight();
            }
            else
            {
                bat.stopRight();
            }
        }

        if (!paused)
        {
            /*
            Update the bat, the ball and the HUD
            *********************************************************************
            *********************************************************************
            *********************************************************************
            */
            // Update the delta time
            Time dt = clock.restart();
            totalTime += dt.asSeconds();
            bat.update(dt);
            ball1.update(dt);
            

            // Update the HUD text
            std::stringstream ss;
            ss << "Score:" << score << "    Lives:" << lives << "    Time:" << static_cast<int>(totalTime);
            hud.setString(ss.str());

            // Handle ball hitting the bottom
            if (ball1.getPosition().top > window.getSize().y)
            {
                // Reverse the ball direction
                ball1.reboundBottom();

                // Remove a life
                lives--;

                // Check for zero lives
                if (lives < 1)
                {
                    totalScore = score * totalTime;
                    paused = true;
                    acceptInput = false;
                    messageText.setPosition(500, 450);
                    messageText.setString("Game Over! Press Enter to Restart. \n Total Score: " + std::to_string(totalScore));
                }
            }

            // Handle ball hitting top
            if ((ball1.getPosition().top < 0) && (ball1.getPosition().top > -10))
            {
                ball1.reboundBatOrTop();

                // Add a point to the players score
                score++;
            }

            // Handle ball hitting sides
            if (ball1.getPosition().left < 0 || ball1.getPosition().left + 10 > window.getSize().x)
            {
                ball1.reboundSides();
            }

            // Has the ball hit the bat?
            if (ball1.getPosition().intersects(bat.getPosition()))
            {
                // Hit detected so reverse the ball and score a point
                ball1.reboundBatOrTop();


                //Increase the speed of the ball if the speed is less than 3000
                if (ball1.getSpeed() < 3000)
                {
                    // Increase the speed of the ball to increase difficulty
                    ball1.changeSpeed(1.05);
                }
            }



            // Has the green ball hit the doubling bat?
            if (ball1.getPosition().intersects(doubleBat.getPosition()))
            {
                // Hit detected so reverse the ball
                ball1.reboundBatOrTop();

                // Switch off the doubleBat
                makeDouble = false;

                //Move the bat off the screen
                doubleBat.setPosition(-100, -300);

                bat.changeSize(200, 5);
            }


            // Has the magenta ball hit the slashing bat?
            if (ball2.getPosition().intersects(slashBat.getPosition()))
            {
                // Hit detected so reverse the ball
                ball2.reboundBatOrTop();

                //Switch off the SlashBat
                makeSlash = false;

                //Move the bat off the screen
                slashBat.setPosition(-100, -300);

                //Decrease the speed of each ball on the screen
                ball2.changeSpeed(0.7);
                ball1.changeSpeed(0.8);
                ball3.changeSpeed(0.6);

            }


            // Has the blue ball hit the heightReset bat?
            if (ball3.getPosition().intersects(heightBat.getPosition()))
            {
                // Hit detected so reverse the ball
                ball3.reboundBatOrTop();

                //Switch off the heightBat
                makeHeight = false;

                //Move the bat off the screen
                slashBat.setPosition(-100, -300);

                //Move the player's bat back to the bottom of the screen
                bat.setPosition(1680 / 2, 1050 - 20);
            }





            // Change the height of the bat as the time increases
            if (totalTime >= 10 && totalTime < 10 + dt.asSeconds())
            {
                bat.changeHeight(50);

            }
            else if (totalTime >= 20 && totalTime < 20 + dt.asSeconds())
            {

                //Activate the doubler bat after 20 seconds has passed
                makeDouble = true;

                //Activate the magenta ball and increase ball count
                makeBall2 = true; 
                lives++; //increment lives count by 1
                ball2.setSpeed(1200); 
                ball2.setPosition(100, 15);
                ball2.reboundBatOrTop();
            }
            else if (totalTime >= 30 && totalTime < 30 + dt.asSeconds())
            {
                bat.changeHeight(50);

                //Activate the slash bat
                makeSlash = true;
            }
            else if (totalTime >= 40 && totalTime < 40 + dt.asSeconds())
            {
             

                //Activate the blue ball and increase ball count
                makeBall3 = true;
                lives++; //increment the lives count, as a new ball has appeared
                ball3.setSpeed(1500);
                ball3.setPosition(150, 500);
                ball3.reboundBatOrTop();
            }
            else if (totalTime >= 50 && totalTime < 50 + dt.asSeconds())
            {
                bat.changeHeight(50);
            }
            else if (totalTime >= 60 && totalTime < 60 + dt.asSeconds())
            {
                //Activate the height reset bat
                makeHeight = true;
            }
            
            /*
            Draw the bat, the ball and the HUD
            *********************************************************************
            *********************************************************************
            *********************************************************************
            */
            window.clear();
            window.draw(hud);
            window.draw(bat.getShape());
            window.draw(ball1.getShape());


            // If the double bat has been created, it will draw on the screen
            if (makeDouble)
            {
                //Create another bat that will double the bat's height when a ball intersects it
                doubleBat.setPosition(500, 300);
                doubleBat.changeSize(100, 50);

                window.draw(doubleBat.getShape());
            }

            // If the slash bat has been created, it will draw on the screen
            if (makeSlash)
            {
                //Create another bat that will reduce the ball's speed when a ball intersects it
                slashBat.setPosition(1200, 500);
                slashBat.changeSize(100, 50);

                window.draw(slashBat.getShape());
            }

            // If the height bat has been created, it will draw on the screen
            if (makeHeight)
            {
                //Create another bat that will reset the bat's height when a ball intersects it
                heightBat.setPosition(800, 100);
                heightBat.changeSize(100, 50);

                window.draw(heightBat.getShape());
            }

            //If the second ball has been created, it will draw onto the screen
            if (makeBall2)
            {
               //move the ball with the update function
                ball2.update(dt);
                

                // Handle ball2 hitting the bottom
                if (ball2.getPosition().top > window.getSize().y)
                {
                    // Reverse the ball direction
                    ball2.reboundBottom();

                    // Remove a life
                    lives--;

                    // Check for zero lives
                    if (lives < 1)
                    {
                        totalScore = score * totalTime;
                        paused = true;
                        acceptInput = false;
                        messageText.setPosition(500, 450);
                        messageText.setString("Game Over! Press Enter to Restart. \n Total Score: " + std::to_string(totalScore));
                    }
                }

                // Handle ball2 hitting top
                if ((ball2.getPosition().top < 0) && (ball2.getPosition().top > -10))
                {
                    ball2.reboundBatOrTop();

                    // Add a point to the players score
                    score++;
                }

                // Handle ball2 hitting sides
                if (ball2.getPosition().left < 0 || ball2.getPosition().left + 10 > window.getSize().x)
                {
                    ball2.reboundSides();
                }

                // Has the ball hit the bat?
                if (ball2.getPosition().intersects(bat.getPosition()))
                {
                    // Hit detected so reverse the ball
                    ball2.reboundBatOrTop();

                    if (ball2.getSpeed() < 3000)
                    {
                        // Increase the speed of the ball to increase difficulty
                        ball2.changeSpeed(1.05);
                    }
                }

                window.draw(ball2.getShape());
            }




            //If the third ball has been created, it will draw onto the screen
            if (makeBall3)
            {
                //Move the blue ball
                ball3.update(dt);
                


                // Handle ball3 hitting the bottom
                if (ball3.getPosition().top > window.getSize().y)
                {
                    // Reverse the ball direction
                    ball3.reboundBottom();

                    // Remove a life
                    lives--;

                    // Check for zero lives
                    if (lives < 1)
                    {
                        totalScore = score * totalTime;
                        paused = true;
                        acceptInput = false;
                        messageText.setPosition(500, 450);
                        messageText.setString("Game Over! Press Enter to Restart. \n Total Score: " + std::to_string(totalScore));
                    }
                }

                // Handle ball3 hitting top
                if ((ball3.getPosition().top < 0) && (ball3.getPosition().top > -10))
                {
                    ball3.reboundBatOrTop();

                    // Add a point to the players score
                    score++;
                }

                // Handle ball3 hitting sides
                if (ball3.getPosition().left < 0 || ball3.getPosition().left + 10 > window.getSize().x)
                {
                    ball3.reboundSides();
                }

                // Has the ball hit the bat?
                if (ball3.getPosition().intersects(bat.getPosition()))
                {
                    // Hit detected so reverse the ball
                    ball3.reboundBatOrTop();

                    if (ball3.getSpeed() < 3000)
                    {
                        // Increase the speed of the ball to increase difficulty
                        ball3.changeSpeed(1.05);
                    }
                }

                window.draw(ball3.getShape());
            }




            window.display();
        }
        else
        {
            window.clear();
            window.draw(messageText);
            window.display();
        }
    }

    return 0;
}
