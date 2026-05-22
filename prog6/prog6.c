#include <stdio.h>
#include <math.h>

#define WIDTH 60
#define HEIGHT 30

// Structure to act as our 2D screen buffer
typedef struct {
    int width;
    int height;
    char grid[HEIGHT][WIDTH];
} ScreenBuffer;

// 1. Initializes the buffer with blank spaces
void initBuffer(ScreenBuffer *buffer) {
    buffer->width = WIDTH;
    buffer->height = HEIGHT;
    
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            buffer->grid[y][x] = ' ';
        }
    }
}

// 2. Renders the circle into the buffer using coordinate geometry
void drawCircleToBuffer(ScreenBuffer *buffer, int centerX, int centerY, int radius) {
    // Corrects for terminal characters being taller than they are wide
    const float aspect_ratio = 0.5f; 

    for (int y = 0; y < buffer->height; y++) {
        for (int x = 0; x < buffer->width; x++) {
            // Calculate distance relative to the center, applying aspect correction to x
            float dx = (x - centerX) * aspect_ratio;
            float dy = (y - centerY);
            float distance = sqrtf(dx * dx + dy * dy);

            // A thickness tolerance of 0.5 keeps the line solid on a text grid
            if (fabsf(distance - radius) < 0.5f) {
                buffer->grid[y][x] = '*';
            }
        }
    }
}

// 3. Loops through the buffer and prints it to the screen
void displayBuffer(const ScreenBuffer *buffer) {
    for (int y = 0; y < buffer->height; y++) {
        for (int x = 0; x < buffer->width; x++) {
            putchar(buffer->grid[y][x]);
        }
        putchar('\n');
    }
}

// 4. Controller function to manage user input, configuration, and execution
void runCircleProgram() {
    ScreenBuffer myBuffer;
    int radius;
    int centerX = WIDTH / 2;
    int centerY = HEIGHT / 2;
    
    // Get customized radius from the user
    printf("Enter the radius of the circle (Recommended 5 to 14): ");
    if (scanf("%d", &radius) != 1) {
        printf("Invalid input. Exiting.\n");
        return;
    }
    
    // Quick safety check so the circle doesn't completely blow past the buffer boundaries
    if (radius <= 0) {
        printf("Radius must be greater than 0.\n");
        return;
    } else if (radius > HEIGHT / 2) {
        printf("Warning: A radius greater than %d might clip off the screen!\n\n", HEIGHT / 2);
    }
    
    // Step 1: Initialize the canvas
    initBuffer(&myBuffer);
    
    // Step 2: Draw and output
    drawCircleToBuffer(&myBuffer, centerX, centerY, radius);
    displayBuffer(&myBuffer);
}

int main() {
    runCircleProgram();
    return 0;
}