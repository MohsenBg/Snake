#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <windows.h>
#include <ctime>
#include <vector>
using namespace std;
#define WIDTH 60
#define HEIGHT 25

struct coord
{
    int x;
    int y;
};

//! Snack_Class
class Snake
{
private:
    coord postions;
    int Lenght;
    vector<coord> body;
    int speed;
    char direction;
    /* dirction
    !  n    =>      none
    !  r    =>      Right
    !  l    =>      left
    !  u    =>      up
    !  d    =>      down
    */

public:
    //* Constractor
    Snake(coord pos, int sp)
    {
        //! postions ==> pos
        //! speed    ==> sp
        postions = pos;
        speed = sp;
        Lenght = 1;
        direction = 'n';
        body.push_back(pos);
    };

    //* Change_Direction_Of_Snake
    void ChangeDirection(char dir)
    {
        //! direction ==> dir
        if (direction == 'u' && dir == 'd')
            return;
        if (direction == 'd' && dir == 'u')
            return;
        if (direction == 'r' && dir == 'l')
            return;
        if (direction == 'l' && dir == 'r')
            return;

        direction = dir;
    };

    //* Handel_Movement_Of_sneack
    void MoveSnake()
    {
        switch (direction)
        {
        case 'l':
            postions.x -= speed;
            break;
        case 'r':
            postions.x += speed;
            break;
        case 'u':
            postions.y -= speed;
            break;
        case 'd':
            postions.y += speed;
            break;

        default:
            break;
        };
        body.push_back(postions);
        if (body.size() > Lenght)
        {
            body.erase(body.begin());
        }
    };

    //* Get_Postion_Of_Snake_head
    coord getPostion()
    {
        return postions;
    };

    //* handle_Eat_Food
    bool eat(coord Food_pos)
    {
        if (Food_pos.x == postions.x && Food_pos.y == postions.y)

            return true;

        else
            return false;
    }

    //* grow
    void grow() { Lenght++; };

    //* when_snack_hit_wall_and_self
    bool collided()
    {
        if (postions.x < 0 || postions.x >= WIDTH - 1 || postions.y < 1 || postions.y >= HEIGHT - 1)
            return true;
        else
        {

            for (int i = 0; i < body.size() - 1; i++)
            {
                if (body[i].x == postions.x && body[i].y == postions.y)
                    return true;
            }
            return false;
        }
    };

    //* Reset
    void Reset()
    {
        direction = 'n';
        postions.x = WIDTH / 2;
        postions.y = HEIGHT / 2;
        Lenght = 1;
        speed = 1;
        body.resize(1);
    };

    //* Get_Postion_Of_Snake_Body
    vector<coord> getPosBody()
    {
        return body;
    };
};

//! Food_Class
class Food
{
private:
    coord postions;

public:
    void makeFood()
    {

        int R_x = rand() % WIDTH + 1;
        if (R_x >= WIDTH - 2)
        {
            postions.x = WIDTH - 3;
        }
        else
        {
            postions.x = R_x;
        }

        int R_y = rand() % HEIGHT + 1;
        if (R_y >= HEIGHT - 1)
        {
            postions.y = HEIGHT - 2;
        }
        else
        {
            postions.y = R_y;
        }
    }
    coord getPostion()
    {
        return postions;
    }
};

Snake snack({WIDTH / 2, HEIGHT / 2}, 1);
Food food;
//! =>> MAKE BOARD GAME
void boradGame()
{
    //! Snack_Coordinates
    coord snack_pos = snack.getPostion();
    coord food_pos = food.getPostion();
    vector<coord> snake_body = snack.getPosBody();
    cout << endl;
    for (int h = 0; h < HEIGHT; h++)
    {

        cout << "\t\t";
        for (int w = 0; w < WIDTH; w++)
        {
            if (w == WIDTH - 1 || w == 0)
                cout
                    << "||";

            if (h == HEIGHT - 1 || h == 0)
            {
                //! one wall shouldn't print
                if (w != WIDTH - 1)
                    cout << "|";
            }
            //! snake
            else if (w == snack_pos.x && h == snack_pos.y)

                cout << "&";
            //! food
            else if (w == food_pos.x && h == food_pos.y)
                cout << "$";
            else
            {
                bool bodyExist = false;
                //! one for Head
                for (int i = 0; i < snake_body.size() - 1; i++)
                {
                    if (snake_body[i].x == w && snake_body[i].y == h)
                    {
                        cout << 'O';
                        bodyExist = true;
                        break;
                    }
                }
                if (!bodyExist)
                {
                    cout << " ";
                }
            }
        }
        cout << endl;
    }
    cout << endl;
}

int main()
{
start:
    srand(time(NULL));
    int score = 0;

    food.makeFood();
    bool gameOver = false;

    while (true)
    {
        cout << endl
             << "  score: " << score << endl;
        boradGame();
        if (kbhit())
        {

            switch (getch())
            {
            //! Left
            case 'a':
                snack.ChangeDirection('l');
                break;

            //? ---------------------
            //! UP
            case 'w':
                snack.ChangeDirection('u');
                break;

            //? ---------------------
            //! Right
            case 'd':
                snack.ChangeDirection('r');
                break;

            //? ---------------------
            //! Down
            case 's':
                snack.ChangeDirection('d');
                break;

            default:
                break;
            }
        }
        snack.MoveSnake();
        //! check food eaten
        if (snack.eat(food.getPostion()))
        {
            food.makeFood();
            snack.grow();
            score += 10;
        }
        //! check_snack_hit_walls
        if (snack.collided())
        {
            gameOver = true;
            while (true)
            {
                cout << " Press 'r' to play again" << endl;
                cout << " Press 'q' to exit" << endl;
                switch (getch())
                {
                case 'r':
                    snack.Reset();
                    system("cls");
                    goto start;
                    break;
                case 'q':
                    goto ending;
                    break;

                default:
                    break;
                };
            };
        };

        //! owerWrite
        if (!gameOver)
        {

            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {0, 0});
        }
    }
ending:
    cout << endl
         << "BYE";
    return 0;
}