# Mined-out

## Table of contents
* [Overview](#overview)
* [Technologies](#technologies)
* [Description](#description)

## Overview
This project was a final assignment, after 3rd semester of C++ computer programming. The main goal of the project was to create a game and take advantage of OOP paradigm. The project is a simplified version of 1983 game called Mined-out. 

## Technologies
* C++
* SFML 

## Description
### Gameplay
Aim of the game is to get to the other side of a minefield and obtain collectables if there are any. It has three levels: first - with no collectables, second and third - with two collectables each. 

### Classes
* Game - Class responsible for collecting inputs, game logic and level handling. By far the biggest of all classes. In here all of the drawables are called. Creates the window.
* Player - Class responsible for moving a player and storing variables of eg. player position. Also has methods that help to manage game logic.
* Entity - Class responsible for drawing rectangle shapes at apropriate positions.
* Bomb - Inherits form TextureInitializer and Entity class. Made to draw bombs with the texture and place it in the right spots when called.
* TextHandler - Class responsible for printing text to to the window eg. Number of bombs.
* TextureInitializer - Class responsible for operations on textures. Many classes inherit from it because it acts like a template for any texture operations.

### Preview
![1](https://user-images.githubusercontent.com/72463980/170593768-6f408745-072a-44ce-8d1f-a379d7504fa8.png)
![2](https://user-images.githubusercontent.com/72463980/170593771-2291845f-fc82-44fd-b23b-06294cdabf55.png)
![3](https://user-images.githubusercontent.com/72463980/170593775-b469dfce-c728-475d-a1da-d8bdb2359cc7.png)
![4](https://user-images.githubusercontent.com/72463980/170593781-306a1f86-5089-4d54-8c1d-4ed3269ebe58.png)
