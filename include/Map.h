/*
 * A class representing a map in the game, which exists as a 2D vector of
 * characters.
 */

#ifndef FREE_THE_CHICK_CPP_MAP_H
#define FREE_THE_CHICK_CPP_MAP_H

#include <vector>
#include <stdexcept>
#include <SFML/Graphics/Sprite.hpp>

class MapSpace {
private:
    char entity;
    sf::Sprite sprite;
public:
    explicit MapSpace(char e) : entity{e} {}
    explicit MapSpace(char e, const sf::Vector2f &pos) : entity{e}
    {
        sprite.setPosition(pos);
    }

    void set_sprite_texture(const sf::Texture &texture) { sprite.setTexture(texture); }
    void set_sprite_pos(const sf::Vector2f &pos) { sprite.setPosition(pos); }
    void set_entity(char e) { entity = e; }

    char get_entity() { return entity; }
    sf::Sprite get_sprite() { return sprite; }
};

class Map {
private:
    std::vector<std::vector<MapSpace>> char_grid;
    size_t rows;
    size_t columns;
public:
    Map(size_t r, size_t c) :
        rows{r}, columns{c}, char_grid{std::vector<std::vector<MapSpace>>(r, std::vector<MapSpace>(c, MapSpace('#')))} {};

    explicit Map(const std::vector<std::vector<MapSpace>> &grid);

    std::vector<std::vector<MapSpace>> get_char_grid() const noexcept { return char_grid; }

    size_t get_rows() const noexcept { return rows; }
    size_t get_columns() const noexcept { return columns; }

    // TODO: This needs bounds checking and an exception
    MapSpace get_grid_space(int row, int column) const { return char_grid[row][columns]; }

    void update_grid_space(int row, int column, const MapSpace &new_value);
    void update_grid_space_entity(int row, int column, char new_value);
};

#endif //FREE_THE_CHICK_CPP_MAP_H
