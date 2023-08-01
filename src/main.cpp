#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#define GRID_WIDTH 1300
#define GRID_HEIGHT 300
#define GRID_CELL_SIZE 20
    
std::vector<sf::RectangleShape> gridCells = {};

void loadGridFromString()
{
    std::vector<std::string> vec = {
        "                                                                X",
        "                                                                X",
        "                                                                X",
        "                                                                X",
        "                                                    XXXXXXXXXXXXX",
        "                     XXXXXX                XXXXXXXXXXXXX       XX",
        "                    X      X      XXXXXXXXX                     X",
        "              XX XXXXXXXXXXXXX XX XXXXXXXXX                     X",
        "        XXXXX XX               XX XXXXXXXXX                     X",
        "       XXXXXX XX               XX XXXXXXXXX                     X",
        "    X XXXXXXX XXXXXXXXXXXXXXXXXXX XXXXXXXXX                     X",
        "    X XXXXXXX XX               XX XXXXXXXXX                     X",
        "  XXX XXXXXXX XX               XX XXXXXXXXX                     X",
        " XXXX XXXXXXX XX               XX XXXXXXXXX                     X",
        "XXXXX XXXXXXX XX               XX XXXXXXXXX                     X"
    };
    for(int i = 0; i < vec.size(); i++)
    {
        for(int j = 0; j < vec[i].size(); j++)
        {
            if(vec[i][j] == 'X')
            {
                gridCells[i * (GRID_WIDTH / GRID_CELL_SIZE) + j].setFillColor(sf::Color::Red);
            }
        }
    }
}
int main()
{
    char current = 'X';

    sf::Font font;
    if(!font.loadFromFile("Roboto-Regular.ttf"))
    {
        std::cout<<"Error loading font"<<std::endl;
        return 0;
    }
    sf::Text coinText;
    coinText.setFont(font);
    coinText.setString("COINS");
    coinText.setCharacterSize(24);
    coinText.setFillColor(sf::Color::White);
    coinText.setPosition(GRID_WIDTH, 0);

    sf::Text enemyText;
    enemyText.setFont(font);
    enemyText.setString("ENEMY");
    enemyText.setCharacterSize(24);
    enemyText.setFillColor(sf::Color::White);
    enemyText.setPosition(GRID_WIDTH, 24);

    sf::Text enemyBlockText;
    enemyBlockText.setFont(font);
    enemyBlockText.setString("ENEMY_BLOCK");
    enemyBlockText.setCharacterSize(24);
    enemyBlockText.setFillColor(sf::Color::White);
    enemyBlockText.setPosition(GRID_WIDTH, 48);

    sf::Text currentText;
    currentText.setFont(font);
    currentText.setString("CURRENT: ");
    currentText.setCharacterSize(16);
    currentText.setFillColor(sf::Color::White);
    currentText.setPosition(GRID_WIDTH, 72);
    sf::RenderWindow window(sf::VideoMode(1500, 500), "SFML works!");
    for (float i = 0; i < GRID_HEIGHT; i += GRID_CELL_SIZE)
    {
        for (float j = 0; j < GRID_WIDTH; j += GRID_CELL_SIZE)
        {
            auto shape = sf::RectangleShape(sf::Vector2f(GRID_CELL_SIZE, GRID_CELL_SIZE));
            shape.setPosition(j, i);
            shape.setFillColor(sf::Color::Blue);
            gridCells.push_back(shape);
        }
    }
    std::vector< std::vector<sf::Vertex>> gridLines = {};
    for (float i = 1; i <= GRID_HEIGHT+1; i += GRID_CELL_SIZE)
    {
        gridLines.push_back({
            sf::Vertex(sf::Vector2f(0, i),sf::Color::White),
            sf::Vertex(sf::Vector2f(GRID_WIDTH, i),sf::Color::White)
            });
    }
    for (float i = 1; i <= GRID_WIDTH + 1; i += GRID_CELL_SIZE)
    {
        gridLines.push_back({
            sf::Vertex(sf::Vector2f(i, 0),sf::Color::White),
            sf::Vertex(sf::Vector2f(i, GRID_HEIGHT),sf::Color::White)
            });
    }
    loadGridFromString();
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if(event.type == sf::Event::KeyPressed)
            {
                if(event.key.code == sf::Keyboard::Space)
                {
                    for(auto& x : gridCells)
                    {
                        if(x.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
                        {
                            x.setFillColor(sf::Color::Red);
                        }
                    }
                }

            }
            if(event.type==sf::Event::MouseButtonReleased)
            {
                if(enemyBlockText.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
                {
                    current = 'B';
                    currentText.setString("CURRENT: B");
                }
                if(coinText.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
                {
                    current = 'C';
                    currentText.setString("CURRENT: C");
                }
                if(enemyText.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
                {
                    current = 'E';
                    currentText.setString("CURRENT: E");
                }
                for(auto& x : gridCells)
                {
                    if(x.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
                    {
                        if(current == 'B')
                        {
                            x.setFillColor(sf::Color::White);
                        }
                        else if(current == 'C')
                        {
                            x.setFillColor(sf::Color::Yellow);
                        }
                        else if(current == 'E')
                        {
                            x.setFillColor(sf::Color::Magenta);
                        }
                        else
                        {
                            x.setFillColor(sf::Color::Red);
                        }
                    }
                }
            }
            if(event.type == sf::Event::KeyReleased)
            {
                if(event.key.code == sf::Keyboard::S)
                {
                    std::cout<<"####PRINTING MAP####"<<std::endl;
                    for (float i = 0; i < GRID_HEIGHT; i += GRID_CELL_SIZE)
                    {
                         auto& printString = std::string("'");
                        for (float j = 0; j < GRID_WIDTH; j += GRID_CELL_SIZE)
                        {
                            const auto& shape = gridCells[(i / GRID_CELL_SIZE) * (GRID_WIDTH / GRID_CELL_SIZE) + (j / GRID_CELL_SIZE)]; 
                            if(shape.getFillColor() == sf::Color::Red)
                            {
                                printString.append("X");
                            }
                            else
                            {
                                printString.append(" ");
                            }
                        }
                        std::cout << printString <<"'," << std::endl;
                    }
                }
            }
        }

        window.clear();
        for (const auto& x : gridCells)
        {
            window.draw(x);
        }
        for (const auto& x : gridLines)
        {
            window.draw(x.data(), 2, sf::Lines);
        }
        window.draw(coinText);
        window.draw(enemyText);
        window.draw(enemyBlockText);
        window.draw(currentText);
        window.display();
    }

    return 0;
}