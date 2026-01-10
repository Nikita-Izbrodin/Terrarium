#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode({512, 512}), "Terrarium", sf::Style::Close | sf::Style::Titlebar);
    window.setVerticalSyncEnabled(true); // call it once after creating the window
    // run the program as long as the window is open

    sf::Texture texture;
    if (!texture.loadFromFile("red.png", false, sf::IntRect({0, 0}, {100, 100})))
    {
        // error...
        std::cout << "File did not load." << std::endl;
        return 1;
    }
    sf::Sprite sprite(texture);

    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        while (const std::optional event = window.pollEvent())
        {
            // "close requested" event: we close the window
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
       }

       if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::W)) {
            //std::cout << "Hello World!" << std::endl;
            sprite.move({0.f, -2.f});
       }
       if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::A)) {
            //std::cout << "Hello World!" << std::endl;
            sprite.move({-2.f, 0.f});
       }
       if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::S)) {
            //std::cout << "Hello World!" << std::endl;
            sprite.move({0.f, 2.f});
       }
       if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::D)) {
            //std::cout << "Hello World!" << std::endl;
            sprite.move({2.f, 0.f});
       }
       if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Escape)) {
            window.close();
       }

        window.clear(sf::Color::Black);

       
        window.draw(sprite);

        window.display();
    }

    return 0;
}
