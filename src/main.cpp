#include <SFML/Graphics.hpp>
#include <vector>
void initializeGrid(const std::vector < sf::RectangleShape > cells)
{

}
int main()
{
    sf::RenderWindow window(sf::VideoMode(1500, 400), "SFML works!");
    std::vector<sf::RectangleShape> gridCells = {};
    for (float i = 0; i < 400; i += 10)
    {
        for (float j = 0; j < 1200; j += 10)
        {
            auto shape = sf::RectangleShape(sf::Vector2f(10.f, 10.f));
            shape.setPosition(j, i);
            shape.setFillColor(sf::Color::Blue);
            gridCells.push_back(shape);
        }
    }
    std::vector< std::vector<sf::Vertex>> gridLines = {};
    for (float i = 1; i <= 401; i += 10)
    {
        gridLines.push_back({
            sf::Vertex(sf::Vector2f(0, i),sf::Color::White),
            sf::Vertex(sf::Vector2f(1200, i),sf::Color::White)
            });
    }
    for (float i = 1; i <= 1201; i += 10)
    {
        gridLines.push_back({
            sf::Vertex(sf::Vector2f(i, 0),sf::Color::White),
            sf::Vertex(sf::Vector2f(i, 400),sf::Color::White)
            });
    }
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
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
        window.display();
    }

    return 0;
}