#include <SFML/Graphics.hpp>

using namespace sf;

int L = 30;//длина
int S = 20;//ширина
int kl = 30;//площадь 1 клеточки
bool game = true;//игра запустилась
int direction = 3;//движение вправо

int length = 3;// длина змеи
//Червяк
struct Warm
{
    int x;
    int y;
}w;
//Змейка
struct Snake
{
    int x;
    int y;
}snake1[600];
//расположение змейки и ее движения
void MoveSnake()
{
    //начальные координаты
    for (int i = length; i > 0; i--)
    {
        snake1[i].x = snake1[i - 1].x;
        snake1[i].y = snake1[i - 1].y;
    }
    //Движение
    if (direction == 0)//вниз
    {
        snake1[0].y = snake1[0].y + 1;
    }
    if (direction == 1)//вверх
    {
        snake1[0].y = snake1[0].y - 1;
    }
    if (direction == 2)//влево
    {
        snake1[0].x = snake1[0].x - 1;
    }
    if (direction == 3)//вправо
    {
        snake1[0].x = snake1[0].x + 1;
    }
    if (snake1[0].x > L)
    {
        snake1[0].x = 0;
    }
    // Поведение змейки, когда выходит за пределы
    if (snake1[0].x < 0) 
    {
        snake1[0].x = L;
    }   
    if (snake1[0].y > S)
    {
        snake1[0].y = 0;
    }
    if (snake1[0].y < 0)
    {
        snake1[0].y = S;
    }
    //Поедание червяка
    if ((snake1[0].x == w.x) && (snake1[0].y == w.y))
    {
        length++;
        w.x = rand() % L;
        w.y = rand() % S;
    }
    //Если сама себя съела, игра останавливается
    for (int i = 1; i < length; i++)
    {
        if ((snake1[0].x == snake1[i].x) && (snake1[0].y == snake1[i].y))
        {
            game = false;
        }
    }
}

int main()
{
    RenderWindow window(VideoMode(L * kl, S * kl), L"Змейка");
    //Ставим картинку поля
    Texture back;
    back.loadFromFile("graphics/field.jpg");
    Sprite backG(back);
    //Ставим иконку приложения
    Image Icon;
    Icon.loadFromFile("graphics/snake.png");
    window.setIcon(32, 32, Icon.getPixelsPtr());
    //Ставим картинку змейки
    Texture sn;
    sn.loadFromFile("graphics/block.png");
    Sprite snake(sn);
    //Картинка червяка
    Texture warmm;
    warmm.loadFromFile("graphics/food.png");
    Sprite warm(warmm);

    Clock clock;
    float tim = 0;

    float mov = 0.15;//движение змейки
    //начальные координаты червя
    w.x = 10;
    w.y = 15;


    while (window.isOpen())
    {

        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        tim += time;

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }
        if (Keyboard::isKeyPressed(Keyboard::Down) && direction != 1)
        {
            direction = 0;
        }
        if (Keyboard::isKeyPressed(Keyboard::Up) && direction != 0)
        {
            direction = 1;
        }
        if (Keyboard::isKeyPressed(Keyboard::Left) && direction != 3)
        {
            direction = 2;
        }
        if (Keyboard::isKeyPressed(Keyboard::Right) && direction != 2)
        {
            direction = 3;
        }

        // чтобы змейка могла двигаться
        if ((tim > mov) && game)
        {
            tim = 0;
            MoveSnake();
        }
        window.clear();

        //прорисовка поля
        window.draw(backG);
        //прорисовка змейки
        for (int i = 0; i < length; i++)
        {
            if (i != 0)
            {
                snake.setTextureRect(IntRect(0, 0, kl, kl));// тело
            }
            else
            {
                snake.setTextureRect(IntRect(0, 0, kl, kl));// голова
            }
            if ((!game) && i == 1)
            {
                snake.setTextureRect(IntRect(direction * kl, kl * 2, kl, kl));
            }
            snake.setPosition(snake1[i].x * kl, snake1[i].y * kl);
            window.draw(snake);
        }
        //Прорисовка червяка
        warm.setPosition(w.x * kl, w.y * kl);
        window.draw(warm);
      

        window.display();
    }


    return 0;
}