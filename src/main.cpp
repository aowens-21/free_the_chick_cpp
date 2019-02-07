#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "../include/Map.h"

using namespace std;

vector<int> get_grid_positions(int map_size, int offset, int rows) {
    vector<int> positions;

    int i;
    for (i = offset; i < map_size; i += map_size / rows)
        positions.push_back(i);

    positions.push_back(i);
    return positions;
}

vector<sf::RectangleShape> get_grid_lines(const vector<int> &positions, float map_size, int offset) {
    vector<sf::RectangleShape> grid_lines;

    for (const auto &p : positions) {
        // row line
        sf::RectangleShape row_line{sf::Vector2f{map_size, 5}};
        row_line.setPosition(offset, p);
        row_line.setFillColor(sf::Color::Black);
        // column line
        sf::RectangleShape column_line{sf::Vector2f{5, map_size}};
        column_line.setPosition(p, offset);
        column_line.setFillColor(sf::Color::Black);

        grid_lines.push_back(row_line);
        grid_lines.push_back(column_line);
    }

    return grid_lines;
}

int main() {
    sf::RenderWindow window{sf::VideoMode(600, 600), "Free The Chick!"};
    sf::Texture player_texture;
    player_texture.loadFromFile("player.png");
    sf::Sprite player_sprite{player_texture};

    constexpr int map_pixel_offset = 50;
    constexpr int map_size = 500;
    constexpr int rows = 8;

    vector<int> grid_positions = get_grid_positions(map_size, map_pixel_offset, rows);
    vector<sf::RectangleShape> grid_lines = get_grid_lines(grid_positions, map_size, map_pixel_offset);

    // Our game map
    Map map{rows, rows};

    sf::Event current_event;
    while (window.isOpen()) {
        while (window.pollEvent(current_event)) {
            if (current_event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::White);
        for (const auto &l : grid_lines)
        {
            window.draw(l);
        }
        window.draw(player_sprite);
        window.display();
    }

    return EXIT_SUCCESS;
}