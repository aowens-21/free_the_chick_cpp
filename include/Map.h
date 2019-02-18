/*
 * A class representing a map in the game, which exists as a 2D vector of
 * characters.
 */

#ifndef FREE_THE_CHICK_CPP_MAP_H
#define FREE_THE_CHICK_CPP_MAP_H

#include <vector>
#include <stdexcept>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics.hpp>
#include <unordered_map>

class MapSpace
{
private:
    char entity;
    sf::Sprite sprite;
public:
    explicit MapSpace(char e) : entity{e}
    {}

    explicit MapSpace(char e, const sf::Vector2f &pos) : entity{e}
    {
        sprite.setPosition(pos);
    }

    void set_sprite_texture(const sf::Texture &texture)
    { sprite.setTexture(texture); }

    void set_sprite_pos(const sf::Vector2f &pos)
    { sprite.setPosition(pos); }

    void set_entity(char e)
    { entity = e; }

    char get_entity() const noexcept
    { return entity; }

    sf::Sprite get_sprite() const noexcept
    { return sprite; }
};

struct Point
{
    int x;
    int y;
    Point(int x, int y): x{x}, y{y} {}
};

class Map
{
private:
    std::vector<std::vector<MapSpace>> char_grid;
    std::unordered_map<char, std::vector<Point>> position_table;
    size_t rows;
    size_t columns;

    void update_position_table(char entity, const Point &pos);
public:
    Map(size_t r, size_t c) :
            rows{r}, columns{c},
            char_grid{std::vector<std::vector<MapSpace>>(r, std::vector<MapSpace>(c, MapSpace('#')))}
    {};

    std::vector<std::vector<MapSpace>> get_char_grid() const noexcept
    { return char_grid; }

    size_t get_rows() const noexcept
    { return rows; }

    size_t get_columns() const noexcept
    { return columns; }

    MapSpace get_grid_space(int row, int column) const
    { return char_grid[row][columns]; }

    void update_grid_space(int row, int column, const MapSpace &new_value);

    void update_grid_space_entity(int row, int column, char new_value);

    void update_grid_space_pos(int row, int column, const sf::Vector2f &new_pos);

    static std::vector<int> get_grid_positions(int map_size, int offset, int rows);

    static std::vector<sf::RectangleShape>
    get_grid_lines(const std::vector<int> &positions, float map_size, int offset, float line_width);

    void draw_entities(sf::RenderWindow &window, const std::vector<int> &grid_positions, float line_width);
    void move_player(int dx, int dy, const sf::Texture &player_texture, const sf::Texture &block_texture);
    bool compute_game_won() const noexcept;
};

#endif //FREE_THE_CHICK_CPP_MAP_H
