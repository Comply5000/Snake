#include "Snake.h"

int main()
{
    srand(time(NULL));
    Snake snake;
    while (snake.running())
    {
        snake.update();
        snake.render();
    }

    return 0;
}
