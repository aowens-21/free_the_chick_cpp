
#include "../include/Map.h"

void Map::update_grid_space_entity(int row, int column, char new_value)
{
    if (row > rows-1 || row < 0 || column > columns-1 || column < 0)
        throw std::logic_error("Row or column outside the bounds of the map!");

    char_grid[row][column].set_entity(new_value);
}

void Map::update_grid_space(int row, int column, const MapSpace &new_value)
{
    if (row > rows-1 || row < 0 || column > columns-1 || column < 0)
        throw std::logic_error("Row or column outside the bounds of the map!");

    char_grid[row][column] = new_value;
}

Map::Map(const std::vector<std::vector<MapSpace>> &grid)
{
    rows = grid.size();
    columns = grid[0].size();

    char_grid = grid;
}