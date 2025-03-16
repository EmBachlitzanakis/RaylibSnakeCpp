# Simple Snake Game (Raylib)

This is a simple implementation of the classic Snake game, created using the Raylib library in C++.

## Features

* Classic Snake gameplay: Control a snake to eat food and grow longer.
* Wall collision detection: The game ends if the snake hits the screen boundaries.
* Self-collision detection: The game ends if the snake hits its own body.
* Score tracking: Displays the current score based on the snake's length.
* Game over screen with restart option.

## Prerequisites

Before you can build and run this game, you need to have the following installed:

* **A C++ compiler:** Such as g++ or clang++.
* **Raylib library:** You need to have the Raylib library installed and linked correctly in your development environment. You can find instructions on how to install Raylib on the official Raylib website: [https://www.raylib.com/](https://www.raylib.com/)

## Build Instructions

1.  Save the provided C++ code (from the previous example) into a file named `snake.cpp`.

2.  Open your terminal or command prompt.

3.  Navigate to the directory where you saved the `snake.cpp` file.

4.  Compile the code using a C++ compiler and link it with the Raylib library. The exact command might vary depending on your system and how you installed Raylib. Here are a couple of common examples:

    * **Using g++ (assuming Raylib is installed system-wide):**
        ```bash
        g++ snake.cpp -o snake -lraylib -lm -lpthread
        ```

    * **Using g++ with specific include and library paths for Raylib (replace `/path/to/raylib/include` and `/path/to/raylib/lib` with your actual paths):**
        ```bash
        g++ snake.cpp -o snake -I/path/to/raylib/include -L/path/to/raylib/lib -lraylib -lm -lpthread
        ```

    * **Using CMake (if you prefer a build system):**

        You would need a `CMakeLists.txt` file like this:

        ```cmake
        cmake_minimum_required(VERSION 3.10)
        project(SnakeGame)

        find_package(raylib REQUIRED)

        add_executable(snake snake.cpp)
        target_link_libraries(snake PRIVATE raylib)
        ```

        Then, you would build using CMake:

        ```bash
        mkdir build
        cd build
        cmake ..
        make # or cmake --build . --config Release
        ```

## Run Instructions

1.  After successfully building the game, you will find an executable file (e.g., `snake` on Linux/macOS or `snake.exe` on Windows) in the same directory or in a `build` subdirectory if you used CMake.

2.  To run the game, simply execute the executable file in your terminal:

    ```bash
    ./snake   # On Linux/macOS
    snake.exe # On Windows
    ```

## Controls

* **Up Arrow Key:** Move the snake up.
* **Down Arrow Key:** Move the snake down.
* **Left Arrow Key:** Move the snake left.
* **Right Arrow Key:** Move the snake right.
* **Spacebar:** Press the spacebar on the "Game Over" screen to restart the game.

## How to Play

The goal of the game is to control the green snake to eat the red food. Each time the snake eats food, it grows longer, and your score increases. Be careful not to hit the walls or the snake's own body, as this will end the game.

## Future Enhancements (Optional)

Here are some ideas for future improvements to the game:

* Implement different difficulty levels (e.g., by changing the snake's speed or the size of the grid).
* Add sound effects for eating food and game over.
* Create a more visually appealing game with different colors or sprites.
* Implement a scoring system with high scores.
* Add different types of food with varying point values or effects.

## License

This project is open-source and available for free use. Feel free to modify and distribute it as you wish. (You can add a specific license like MIT or Apache 2.0 if you have one).
