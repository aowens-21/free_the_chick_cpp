#include <iostream>
#include <vector>
#include "../include/Map.h"

using namespace std;

int main()
{
    sf::RenderWindow window{sf::VideoMode{600, 600}, "Free The Chick!"};
    window.setFramerateLimit(60);

    sf::Texture player_texture;
    player_texture.loadFromFile("player.png");

    sf::Texture chick_texture;
    chick_texture.loadFromFile("chick.jpg");

    sf::Texture block_texture;
    block_texture.loadFromFile("block.png");

    constexpr int map_pixel_offset = 50;
    constexpr int map_size = 500;
    constexpr int rows = 8;
    constexpr float line_width = 5.0;

    vector<int> grid_positions = Map::get_grid_positions(map_size, map_pixel_offset, rows);
    vector<sf::RectangleShape> grid_lines = Map::get_grid_lines(grid_positions, map_size, map_pixel_offset, line_width);

    // Our game map
    Map map{rows, rows};
    vector<vector<MapSpace>> grid;

    MapSpace player_space{'P'};
    player_space.set_sprite_texture(player_texture);
    map.update_grid_space(1, 1, player_space);

    MapSpace chick_space{'C'};
    chick_space.set_sprite_texture(chick_texture);
    map.update_grid_space(5, 5, chick_space);

    MapSpace block_space1{'B'};
    block_space1.set_sprite_texture(block_texture);
    map.update_grid_space(5, 6, block_space1);
    MapSpace block_space2{'B'};
    block_space2.set_sprite_texture(block_texture);
    map.update_grid_space(5, 4, block_space2);
    MapSpace block_space4{'B'};
    block_space4.set_sprite_texture(block_texture);
    map.update_grid_space(4, 5, block_space4);
    MapSpace block_space5{'B'};
    block_space5.set_sprite_texture(block_texture);
    map.update_grid_space(4, 6, block_space5);
    MapSpace block_space7{'B'};
    block_space7.set_sprite_texture(block_texture);
    map.update_grid_space(6, 5, block_space7);
    MapSpace block_space8{'B'};
    block_space8.set_sprite_texture(block_texture);
    map.update_grid_space(6, 6, block_space8);

    bool game_won = false;


    sf::Font font;
    font.loadFromFile("roboto.ttf");
    sf::Text win_text;
    win_text.setFont(font);
    win_text.setString("YOU WIN!");
    win_text.setCharacterSize(40);
    win_text.setFillColor(sf::Color::White);
    win_text.setPosition(220, 260);

    sf::Event current_event{};
    while (window.isOpen())
    {
        grid = map.get_char_grid();

        while (window.pollEvent(current_event))
        {
            if (current_event.type == sf::Event::Closed)
            {
                window.close();
            }
            else if (current_event.type == sf::Event::KeyPressed)
            {
                if (current_event.key.code == sf::Keyboard::Escape)
                {
                    window.close();
                }
                else
                {
                    if (current_event.key.code == sf::Keyboard::Left)
                    {
                        map.move_player(-1, 0, player_texture, block_texture);
                        game_won = map.compute_game_won();
                    }
                    else if (current_event.key.code == sf::Keyboard::Right)
                    {
                        map.move_player(1, 0, player_texture, block_texture);
                        game_won = map.compute_game_won();
                    }
                    else if (current_event.key.code == sf::Keyboard::Up)
                    {
                        map.move_player(0, -1, player_texture, block_texture);
                        game_won = map.compute_game_won();
                    }
                    else if (current_event.key.code == sf::Keyboard::Down)
                    {
                        map.move_player(0, 1, player_texture, block_texture);
                        game_won = map.compute_game_won();
                    }
                }
            }
        }

        if (!game_won)
        {
            window.clear(sf::Color::White);
            for (const auto &l : grid_lines)
            {
                window.draw(l);
            }

            map.draw_entities(window, grid_positions, line_width);
        }
        else
        {
            window.clear(sf::Color::Black);
            window.draw(win_text);
        }
        window.display();
    }

    return EXIT_SUCCESS;
}