/*
 * A class representing a map in the game, which exists as a 2D vector of
 * characters.
 */

#ifndef FREE_THE_CHICK_CPP_MAP_H
#define FREE_THE_CHICK_CPP_MAP_H

#include <vector>
#include <stdexcept>

class Map {
private:
    std::vector<std::vector<char>> char_grid;
    size_t rows;
    size_t columns;
public:
    Map(size_t r, size_t c) :
        rows{r}, columns{c}, char_grid{std::vector<std::vector<char>>(r, std::vector<char>(c, '#'))} {};

    explicit Map(const std::vector<std::vector<char>> &grid);

    size_t get_rows() const noexcept { return rows; }
    size_t get_columns() const noexcept { return columns; }

    char get_grid_space(int row, int column) const noexcept { return char_grid[row][columns]; }

    void update_grid_space(int row, int column, char new_value);
};

#endif //FREE_THE_CHICK_CPP_MAP_H
