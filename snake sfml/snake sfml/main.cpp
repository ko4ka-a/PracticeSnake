#include <SFML/Graphics.hpp>

using namespace sf;

int L = 30;//�����
int S = 20;//������
int kl = 30;//������� 1 ��������
bool game = true;//���� �����������
int direction = 3;//�������� ������

int length = 3;// ����� ����
//������
struct Warm
{
    int x;
    int y;
}w;
//������
struct Snake
{
    int x;
    int y;
}snake1[600];
//������������ ������ � �� ��������
void MoveSnake()
{
    //��������� ����������
    for (int i = length; i > 0; i--)
    {
        snake1[i].x = snake1[i - 1].x;
        snake1[i].y = snake1[i - 1].y;
    }
    //��������
    if (direction == 0)//����
    {
        snake1[0].y = snake1[0].y + 1;
    }
    if (direction == 1)//�����
    {
        snake1[0].y = snake1[0].y - 1;
    }
    if (direction == 2)//�����
    {
        snake1[0].x = snake1[0].x - 1;
    }
    if (direction == 3)//������
    {
        snake1[0].x = snake1[0].x + 1;
    }
    if (snake1[0].x > L)
    {
        snake1[0].x = 0;
    }
    // ��������� ������, ����� ������� �� �������
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
    //�������� �������
    if ((snake1[0].x == w.x) && (snake1[0].y == w.y))
    {
        length++;
        w.x = rand() % L;
        w.y = rand() % S;
    }
    //���� ���� ���� �����, ���� ���������������
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
    RenderWindow window(VideoMode(L * kl, S * kl), L"������");
    //������ �������� ����
    Texture back;
    back.loadFromFile("graphics/field.jpg");
    Sprite backG(back);
    //������ ������ ����������
    Image Icon;
    Icon.loadFromFile("graphics/snake.png");
    window.setIcon(32, 32, Icon.getPixelsPtr());
    //������ �������� ������
    Texture sn;
    sn.loadFromFile("graphics/block.png");
    Sprite snake(sn);
    //�������� �������
    Texture warmm;
    warmm.loadFromFile("graphics/food.png");
    Sprite warm(warmm);

    Clock clock;
    float tim = 0;

    float mov = 0.15;//�������� ������
    //��������� ���������� �����
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

        // ����� ������ ����� ���������
        if ((tim > mov) && game)
        {
            tim = 0;
            MoveSnake();
        }
        window.clear();

        //���������� ����
        window.draw(backG);
        //���������� ������
        for (int i = 0; i < length; i++)
        {
            if (i != 0)
            {
                snake.setTextureRect(IntRect(0, 0, kl, kl));// ����
            }
            else
            {
                snake.setTextureRect(IntRect(0, 0, kl, kl));// ������
            }
            if ((!game) && i == 1)
            {
                snake.setTextureRect(IntRect(direction * kl, kl * 2, kl, kl));
            }
            snake.setPosition(snake1[i].x * kl, snake1[i].y * kl);
            window.draw(snake);
        }
        //���������� �������
        warm.setPosition(w.x * kl, w.y * kl);
        window.draw(warm);
      

        window.display();
    }


    return 0;
}