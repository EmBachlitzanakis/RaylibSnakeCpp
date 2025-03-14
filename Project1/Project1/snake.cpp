#include "raylib.h"
#include <vector>
#include <cstdlib>
#include <ctime>

// Define some constants for the game
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int CELL_SIZE = 20;
const int GRID_WIDTH = SCREEN_WIDTH / CELL_SIZE;
const int GRID_HEIGHT = SCREEN_HEIGHT / CELL_SIZE;

// Structure to represent a point (used for snake and food positions)
struct Point {
    int x;
    int y;

    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }
};

// Function to generate a random point within the grid
Point GetRandomPoint() {
    return { std::rand() % GRID_WIDTH, std::rand() % GRID_HEIGHT };
}

int main() {
    // Initialize Raylib
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Simple Snake");
    SetTargetFPS(10); // Set the game's FPS

    // Seed the random number generator
    std::srand(std::time(nullptr));

    // Initialize game variables
    std::vector<Point> snake = { {GRID_WIDTH / 2, GRID_HEIGHT / 2} }; // Start with a single segment in the middle
    Point food = GetRandomPoint();
    Vector2 direction = { 1, 0 }; // Start moving right
    bool gameOver = false;
    float moveTimer = 0.0f;
    const float moveInterval = 0.2f; // Time between snake movements

    while (!WindowShouldClose()) {
        // Update game logic
        if (!gameOver) {
            moveTimer += GetFrameTime();

            // Handle input
            if (IsKeyPressed(KEY_UP) && direction.y != 1) direction = { 0, -1 };
            if (IsKeyPressed(KEY_DOWN) && direction.y != -1) direction = { 0, 1 };
            if (IsKeyPressed(KEY_LEFT) && direction.x != 1) direction = { -1, 0 };
            if (IsKeyPressed(KEY_RIGHT) && direction.x != -1) direction = { 1, 0 };

            // Move the snake
            if (moveTimer >= moveInterval) {
                moveTimer -= moveInterval;

                // Create a new head for the snake
                Point newHead = { snake[0].x + static_cast<int>(direction.x), snake[0].y + static_cast<int>(direction.y) };

                // Check for wall collision
                if (newHead.x < 0 || newHead.x >= GRID_WIDTH || newHead.y < 0 || newHead.y >= GRID_HEIGHT) {
                    gameOver = true;
                }

                // Check for self-collision
                for (size_t i = 0; i < snake.size(); ++i) {
                    if (newHead == snake[i]) {
                        gameOver = true;
                        break;
                    }
                }

                if (!gameOver) {
                    snake.insert(snake.begin(), newHead); // Add the new head

                    // Check if the snake ate the food
                    if (newHead == food) {
                        food = GetRandomPoint();
                        // Ensure the new food doesn't spawn on the snake
                        bool onSnake;
                        do {
                            onSnake = false;
                            for (const auto& segment : snake) {
                                if (food == segment) {
                                    food = GetRandomPoint();
                                    onSnake = true;
                                    break;
                                }
                            }
                        } while (onSnake);
                    }
                    else {
                        snake.pop_back(); // Remove the tail if no food was eaten
                    }
                }
            }
        }
        else {
            // Handle game over input (e.g., restart)
            if (IsKeyPressed(KEY_SPACE)) {
                snake = { {GRID_WIDTH / 2, GRID_HEIGHT / 2} };
                food = GetRandomPoint();
                direction = { 1, 0 };
                gameOver = false;
                moveTimer = 0.0f;
            }
        }

        // Draw everything
        BeginDrawing();
        ClearBackground(BLACK);
        DrawRectangle(food.x * CELL_SIZE, food.y * CELL_SIZE, CELL_SIZE, CELL_SIZE, RED);

        // Draw the snake
        for (const auto& segment : snake) {
            DrawRectangle(segment.x * CELL_SIZE, segment.y * CELL_SIZE, CELL_SIZE, CELL_SIZE, GREEN);
        }

        // Draw game over message
        if (gameOver) {
            const char* gameOverText = "Game Over!";
            int fontSize = 40;
            Vector2 textSize = MeasureTextEx(GetFontDefault(), gameOverText, fontSize, 0);
            DrawTextEx(GetFontDefault(), gameOverText, { (SCREEN_WIDTH - textSize.x) / 2, (SCREEN_HEIGHT - textSize.y) / 2 - fontSize }, fontSize, 0, WHITE);

            const char* restartText = "Press SPACE to restart";
            int restartFontSize = 20;
            Vector2 restartTextSize = MeasureTextEx(GetFontDefault(), restartText, restartFontSize, 0);
            DrawTextEx(GetFontDefault(), restartText, { (SCREEN_WIDTH - restartTextSize.x) / 2, (SCREEN_HEIGHT - textSize.y) / 2 + restartFontSize }, restartFontSize, 0, LIGHTGRAY);
        }
        else {
            // Display the score
            const char* scoreText = TextFormat("Score: %i", static_cast<int>(snake.size()));
            DrawText(scoreText, 10, 10, 20, WHITE);
        }

        EndDrawing();
    }

    // De-initialize Raylib
    CloseWindow();

    return 0;
}