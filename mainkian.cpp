#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>
#include <stdlib.h>
#include "NotAFunction.h"
#include "Effect.h"
#include "Effects.h"
#include "Projectile.h"
#include "Asteroid.h"
#include "Asteroids.h"
#include "Enemies.h"
#include "Fart.h"
#include "HitBox.h"
#include "Player.h"
#include "Background.h"

using namespace sf;
using namespace std;

int main() {

    // init window
    RenderWindow window(VideoMode(800, 1000), "SFML works!");
    window.setFramerateLimit(60);

    // init textures

    // init dmgFX
    Texture playerShapeDmg;
    playerShapeDmg.loadFromFile("textures/effects/spaceship_dmg.png");
    Texture enemyShapeDmg;
    enemyShapeDmg.loadFromFile("textures/effects/enemy_dmg.png");
    Texture asteroidShapeDmg;
    asteroidShapeDmg.loadFromFile("textures/effects/asteroid_1_dmg.png");

    // init player textures
    Texture playerTex;
    Texture playerTex1;
    Texture playerTex2;
    Texture playerTex3;
    playerTex.loadFromFile("textures/spaceship/spaceship1.png");
    playerTex1.loadFromFile("textures/spaceship/spaceship2.png");
    playerTex2.loadFromFile("textures/spaceship/spaceship3.png");
    playerTex3.loadFromFile("textures/spaceship/spaceship4.png");
    Texture playerFire;
    Texture playerFire1;
    playerFire.loadFromFile("textures/spaceship/spaceship_fire1.png");
    playerFire1.loadFromFile("textures/spaceship/spaceship_fire2.png");
    Texture playerDeath;
    Texture playerDeath1;
    playerDeath.loadFromFile("textures/spaceship/spaceship_death1.png");
    playerDeath1.loadFromFile("textures/spaceship/spaceship_death2.png");

    // init enemy textures
    Texture enemyTex;
    Texture enemyTex1;
    Texture enemyTex2;
    Texture enemyTex3;
    enemyTex.loadFromFile("textures/enemy/enemy1.png");
    enemyTex1.loadFromFile("textures/enemy/enemy2.png");
    enemyTex2.loadFromFile("textures/enemy/enemy3.png");
    enemyTex3.loadFromFile("textures/enemy/enemy4.png");
    Texture enemyFire;
    Texture enemyFire1;
    enemyFire.loadFromFile("textures/enemy/enemy_fire1.png");
    enemyFire1.loadFromFile("textures/enemy/enemy_fire2.png");
    Texture enemyDeath;
    Texture enemyDeath1;
    enemyDeath.loadFromFile("textures/enemy/enemy_explode1.png");
    enemyDeath1.loadFromFile("textures/enemy/enemy_explode2.png");

    // init asteroid textures
    Texture asteroidTex;
    asteroidTex.loadFromFile("textures/asteroids/asteroid_1.png");
    Texture asteroidDeath;
    Texture asteroidDeath1;
    asteroidDeath.loadFromFile("textures/asteroids/asteroid_1_explode1.png");
    asteroidDeath1.loadFromFile("textures/asteroids/asteroid_1_explode2.png");

    // init proj textures
    Texture playerbulletTex;
    playerbulletTex.loadFromFile("textures/projectiles/bullet.png");
    Texture enemybulletTex;
    enemybulletTex.loadFromFile("textures/projectiles/enemy_bullet.png");

    // init bulletFX textures
    Texture playerBulletFX;
    Texture playerBulletFX1;
    playerBulletFX.loadFromFile("textures/projectiles/bullet_impact1.png");
    playerBulletFX1.loadFromFile("textures/projectiles/bullet_impact2.png");
    Texture enemyBulletFX;
    Texture enemyBulletFX1;
    enemyBulletFX.loadFromFile("textures/projectiles/enemy_bullet_impact1.png");
    enemyBulletFX1.loadFromFile("textures/projectiles/enemy_bullet_impact2.png");

    // init background
    Texture spaceTex;
    spaceTex.loadFromFile("textures/background/space.png");
    Background space1(&spaceTex,Vector2f(0,0));
    Background space2(&spaceTex,Vector2f(0,-1000));
    Texture starTex;
    starTex.loadFromFile("textures/background/stars.png");
    Background stars(&starTex,Vector2f(0,0));

    // init menu
    // menustate - which button on the menu is selected
    int menuState = 0;
    bool startGame = false;
    Texture menuTex;
    Texture menuTex1;
    menuTex.loadFromFile("textures/background/menu1.png");
    menuTex1.loadFromFile("textures/background/menu2.png");
    Background menu(&menuTex,Vector2f(0,0));

    // init controls
    Texture controls;
    controls.loadFromFile("textures/background/controls.png");
    Background showControls(&controls,Vector2f(0,0));

    // init paused screen 
    // pausedstate - which button on the paused screen is selected
    bool paused = false;
    int pausedState = 0;
    Texture pausedTex;
    Texture pausedTex1;
    pausedTex.loadFromFile("textures/background/paused1.png");
    pausedTex1.loadFromFile("textures/background/paused2.png");
    Background pausedScreen(&pausedTex,Vector2f(0,0));

    // init gameover screen
    Texture overTex;
    Texture overTex1;
    overTex.loadFromFile("textures/background/game_over1.png");
    overTex1.loadFromFile("textures/background/game_over2.png");
    Background overScreen(&overTex,Vector2f(0,0));

    // init view
    // allows for window resizing without stretching
    View view;
    NotAFunction actuallyNot;
    view.setSize(800, 1000);
    view.setCenter(view.getSize().x / 2, view.getSize().y / 2);
    view = actuallyNot.a_function(view, 800, 1000);

    // init text and font
    Text scoreText;
    Font font;
    font.loadFromFile("textures/fonts/ka1.ttf");
    scoreText.setFont(font);
    scoreText.setCharacterSize(20);
    scoreText.setFillColor(Color::White);
    scoreText.setPosition(Vector2f(350,80));

    // game loop - menu
    while (window.isOpen()) {

        startGame = false;

        // check window events
        Event event;
        while (window.pollEvent(event)) {
            // close window
            if (event.type == Event::Closed) {
                window.close();
            }

            // allows user to select options
            if (Keyboard::isKeyPressed(Keyboard::W) && event.type == Event::KeyPressed && menuState != 0) {
                menuState = 0;
                menu.setTex(&menuTex);
            } else if (Keyboard::isKeyPressed(Keyboard::S) && event.type == Event::KeyPressed && menuState != 1) {
                menuState = 1;
                menu.setTex(&menuTex1);
            }
            if (Keyboard::isKeyPressed(Keyboard::Enter) && event.type == Event::KeyPressed && menuState == 0) {
                startGame = true;
            }

            // fullscreen
            if (event.type == Event::Resized) {
                view = actuallyNot.a_function(view, event.size.width, event.size.height);
            }
        }

        // move background
        space1.moveBackground();
        space2.moveBackground();

        // start game
        if (startGame == true) {

            // init player
            Player player(&playerTex,&playerShapeDmg,Vector2f(400,500),Vector2f(0,0));
            player.weaponCooldown = 10;
            player.firerate = 10;

            // init enemies
            Enemies enemies;

            // init asteroids
            Asteroids rocks;

            // init stats
            int baseProjSpeed = 30;

            // init effects
            Effects bulletFX;

            // init spawn timers
            int spawnTimer = 0;
            int asteroidSpawn = 0;

            // game over screen state
            int overState = 0;
            // game is not over
            bool gameOver = false;

            while (window.isOpen()) {                
                // window events
                Event event;
                while (window.pollEvent(event)) {
                    // close window
                    if (event.type == Event::Closed) {
                        window.close();
                    }

                    // fullscreen
                    if (event.type == Event::Resized) {
                        view = actuallyNot.a_function(view, event.size.width, event.size.height);
                    }
                }
                
                // pause
                if (Keyboard::isKeyPressed(Keyboard::Escape) && paused == false) {
                    paused = true;
                }
                if (paused == true && gameOver == false) {
                    // allows user to select button in pausedscreen
                    if (Keyboard::isKeyPressed(Keyboard::W) && pausedState != 0) {
                        pausedState = 0;
                        pausedScreen.setTex(&pausedTex);
                    } else if (Keyboard::isKeyPressed(Keyboard::S) && pausedState != 1) {
                        pausedState = 1;
                        pausedScreen.setTex(&pausedTex1);
                    }

                    // allows user to press button
                    if (Keyboard::isKeyPressed(Keyboard::Enter) && pausedState == 0) {
                        paused = false;
                    }
                    if (Keyboard::isKeyPressed(Keyboard::Enter) && pausedState == 1) {
                        paused = false;
                        pausedState = 0;
                        pausedScreen.setTex(&pausedTex);
                        break;
                    }
                }

                // not paused
                if (paused == false && gameOver == false) {
                    
                    // spawn enemies
                    spawnTimer++;
                    if (spawnTimer % 120 == true) {
                        int spawnX = rand() % 800 + 1;
                        enemies.addFart(Fart(&enemyTex,&enemyShapeDmg,Vector2f(spawnX,-200),Vector2f(0,0)));
                    }

                    // spawn asteroids
                    asteroidSpawn++;
                    if (asteroidSpawn % 120 == true) {
                        int spawnX = rand() % 900 - 100;
                        rocks.addAsteroid(Asteroid(&asteroidTex,&asteroidShapeDmg,Vector2f(spawnX,-200),Vector2f(12,11)));
                    }

                    // move background
                    space1.moveBackground();
                    space2.moveBackground();

                    // animate player
                    player.animateShip(&playerTex,&playerTex1,&playerTex2,&playerTex3);
                    // animate enemies
                    for (int i = 0;i < enemies.fartCount;i++) {
                        enemies.farts[i].animateShip(&enemyTex,&enemyTex1,&enemyTex2,&enemyTex3);
                    }

                    // animate bulletFX
                    bulletFX.animateEffects();

                    // move player
                    player.movement();
                    // move enemies
                    for (int i = 0;i < enemies.fartCount;i++) {
                        enemies.farts[i].movement(player.shape.getPosition());
                    }
                    // move asteroids
                    for (int i = 0;i < rocks.asteroidCount;i++) {
                        rocks.asteroids[i].movement();
                    }

                    // move player hitbox
                    player.hitbox.Follow(Vector2f(player.shape.getPosition().x+4*5,player.shape.getPosition().y+4*5));
                    // move enemies hitbox
                    for (int i = 0;i < enemies.fartCount;i++) {
                        enemies.farts[i].hitbox.Follow(Vector2f(enemies.farts[i].shape.getPosition().x+4*5,enemies.farts[i].shape.getPosition().y+4*6));
                    }
                    // move asteroids hitbox
                    for (int i = 0;i < rocks.asteroidCount;i++) {
                        rocks.asteroids[i].hitbox.Follow(Vector2f(rocks.asteroids[i].shape.getPosition().x-4*12+4*4,rocks.asteroids[i].shape.getPosition().y-4*11+4*3));
                    }

                    // player window collision
                    player.collisionWindow();
                    // enemies window collision
                    for (int i = 0;i < enemies.fartCount;i++) {
                        enemies.farts[i].collisionWindow();
                    }
                    // asteroids window collision
                    for (int i = 0;i < rocks.asteroidCount;i++) {
                        if (rocks.asteroids[i].collisionWindow() == true) {
                            rocks.rmAsteroid(i);
                        }
                    }

                    // player shoot
                    player.shooting(&playerbulletTex,&playerFire,&playerFire1,baseProjSpeed);
                    // enemies shoot
                    for (int i = 0;i < enemies.fartCount;i++) {
                        enemies.farts[i].shooting(&enemybulletTex,&enemyFire,&enemyFire1,10);
                    }

                    // projectile collision
                    // update player hitbox
                    player.hitbox.UpdateHitbox();
                    // update enemies hitbox
                    for (int i = 0;i < enemies.fartCount;i++) {
                        enemies.farts[i].hitbox.UpdateHitbox();
                    }
                    // update asteroids hitbox
                    for (int i = 0;i < rocks.asteroidCount;i++) {
                        rocks.asteroids[i].hitbox.UpdateHitbox();
                    }
                    // check if enemies is hit
                    for (int j = 0;j < enemies.fartCount;j++) {
                        for (size_t i = 0;i < player.projectiles.size();i++) {
                            if (enemies.farts[j].hitbox.CheckHit(player.projectiles[i].shape.getPosition()) == true) {
                                bulletFX.AddEffect(&playerBulletFX,&playerBulletFX1,Vector2f(player.projectiles[i].shape.getPosition().x-8,player.projectiles[i].shape.getPosition().y-8));
                                player.projectiles.erase(player.projectiles.begin() + i);
                                enemies.farts[j].takeDamage(player.projectiles[i].dmg);
                                enemies.farts[j].isDead();
                            }
                        }
                        // animate deaths
                        if (enemies.farts[j].animateDeath(&enemyDeath,&enemyDeath1) == true) {
                            player.addScore(enemies.farts[j].worth);
                            enemies.rmFart(j);
                        };
                    }
                    // check if asteroids is hit
                    for (int j = 0;j < rocks.asteroidCount;j++) {
                        for (size_t i = 0;i < player.projectiles.size();i++) {
                            if (rocks.asteroids[j].hitbox.CheckHit(player.projectiles[i].shape.getPosition()) == true) {
                                bulletFX.AddEffect(&playerBulletFX,&playerBulletFX1,Vector2f(player.projectiles[i].shape.getPosition().x-8,player.projectiles[i].shape.getPosition().y-8));
                                player.projectiles.erase(player.projectiles.begin() + i);
                                rocks.asteroids[j].takeDamage(player.projectiles[i].dmg);
                                rocks.asteroids[j].isDead();
                            }
                        }
                        // animate deaths
                        if (rocks.asteroids[j].animateDeath(&asteroidDeath,&asteroidDeath1) == true) {
                            rocks.rmAsteroid(j);
                        };
                    }
                    // check if player is hit
                    for (int j = 0;j < enemies.fartCount;j++) {
                        for (size_t i = 0;i < enemies.farts[j].projectiles.size();i++) {
                            if (player.hitbox.CheckHit(Vector2f(enemies.farts[j].projectiles[i].shape.getPosition().x+4,enemies.farts[j].projectiles[i].shape.getPosition().y+3*4)) == true) {
                                bulletFX.AddEffect(&enemyBulletFX,&enemyBulletFX1,enemies.farts[j].projectiles[i].shape.getPosition());
                                enemies.farts[j].projectiles.erase(enemies.farts[j].projectiles.begin() + i);
                                player.takeDamage(enemies.farts[j].projectiles[i].dmg);
                                player.isDead();
                            }
                        }
                    }
                    // animate death if dead
                    player.isDead();
                    if (player.animateDeath(&playerDeath,&playerDeath1) == true) {
                        gameOver = true;
                    }

                    // enemy collision
                    for (int i = 0;i < enemies.fartCount;i++) {
                        if (player.hitbox.CheckCollision(enemies.farts[i].hitbox.box) == true) {
                            player.bounce(enemies.farts[i].shape.getPosition());
                        }
                    }
                    // asteroid collision
                    for (int i = 0;i < rocks.asteroidCount;i++) {
                        if (player.hitbox.CheckCollision(rocks.asteroids[i].hitbox.box) == true) {
                            player.bounce(rocks.asteroids[i].shape.getPosition());
                        }
                    }

                    // update score
                    string scoreNumber = to_string(player.score);
                    // show hp
                    string healthText = to_string(player.hp);
                    scoreText.setString("Score: " + scoreNumber + "\nHP: " + healthText);

                } else if (paused == false && gameOver == true) { // if game over
                    // allows user to select button on gameover screen
                    if (Keyboard::isKeyPressed(Keyboard::W) && overState != 0) {
                        overState = 0;
                        overScreen.setTex(&overTex);
                    } else if (Keyboard::isKeyPressed(Keyboard::S) && overState != 1) {
                        overState = 1;
                        overScreen.setTex(&overTex1);
                    }
                    // allows user to press selected button
                    if (Keyboard::isKeyPressed(Keyboard::Enter) && overState == 0) {
                        gameOver = false;
                        overState = 0;
                        pausedScreen.setTex(&pausedTex);
                        break;
                    }
                    if (Keyboard::isKeyPressed(Keyboard::Enter) && overState == 1) {
                        window.close();
                    }
                }

                // window
                window.clear();

                // window resizing
                window.setView(view);

                // draw 
                // draw background
                window.draw(space1.shape);
                window.draw(space2.shape);
                window.draw(stars.shape);

                // draw player
                if (gameOver == false) {
                    window.draw(player.shape);
                    window.draw(scoreText);
                }
                // window.draw(player.hitbox.shape); //debug

                // draw enemies stuff
                for (int j = 0;j < enemies.fartCount;j++) {
                    // draw enemies shapes
                    window.draw(enemies.farts[j].shape);
                    // window.draw(enemies.farts[j].hitbox.shape); // for debug
                    
                    // draw enemy dmg animation
                    if (enemies.farts[j].animateDmg() == true) {
                        window.draw(enemies.farts[j].shapeDmg);
                    }

                    // draw all enemy projectiles
                    for (size_t i = 0;i < enemies.farts[j].projectiles.size();i++) {
                        window.draw(enemies.farts[j].projectiles[i].shape); 
                    }
                }

                // draw asteroids stuff
                for (int i = 0;i < rocks.asteroidCount;i++) {
                    // draw asteroid shape
                    window.draw(rocks.asteroids[i].shape);
                    //window.draw(rocks.asteroids[i].hitbox.shape);

                    // draw asteroid dmg animation
                    if (rocks.asteroids[i].animateDmg() == true) {
                        window.draw(rocks.asteroids[i].shapeDmg);
                    }
                }

                // draw player projectiles
                for (size_t i = 0;i < player.projectiles.size();i++) {
                    window.draw(player.projectiles[i].shape); 
                }

                // draw bulletFX
                for (size_t i = 0;i < bulletFX.effects.size();i++) {
                    window.draw(bulletFX.effects[i].shape);
                }

                // draw dmgFX
                if (player.animateDmg() == true) {
                    window.draw(player.shapeDmg);
                }

                // draw paused
                if (paused == true && gameOver == false) {
                    window.draw(pausedScreen.shape);
                }

                // draw game over screen
                if (gameOver) {
                    window.draw(overScreen.shape);
                    string scoreNumber = to_string(player.score);
                    scoreText.setString("Score: " + scoreNumber);
                    scoreText.setPosition(Vector2f(350,80));
                    window.draw(scoreText);
                }

                window.display();
            }
        }

        // quit game
        if (Keyboard::isKeyPressed(Keyboard::Enter) && menuState == 1) {
            window.close();
        }

        // draw background
        window.clear();

        // window resizing
        window.setView(view);

        window.draw(space1.shape);
        window.draw(space2.shape);
        window.draw(stars.shape);
        window.draw(menu.shape);
        window.draw(showControls.shape);
        
        // show frame 
        window.display();
    }

    return 0;
}