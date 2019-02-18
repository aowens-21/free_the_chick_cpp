
#include "../include/Map.h"

void Map::update_grid_space_entity(int row, int column, char new_value)
{
    if (row > rows - 1 || row < 0 || column > columns - 1 || column < 0)
        throw std::logic_error("Row or column outside the bounds of the map!");

    if (new_value != '#')
        update_position_table(new_value, Point(row, column));

    char_grid[row][column].set_entity(new_value);
}

void Map::update_grid_space(int row, int column, const MapSpace &new_value)
{
    if (row > rows - 1 || row < 0 || column > columns - 1 || column < 0)
        throw std::logic_error("Row or column outside the bounds of the map!");

    if (new_value.get_entity() != '#')
        update_position_table(new_value.get_entity(), Point(row, column));


    char_grid[row][column] = new_value;
}

void Map::update_grid_space_pos(int row, int column, const sf::Vector2f &new_pos)
{
    if (row > rows - 1 || row < 0 || column > columns - 1 || column < 0)
        throw std::logic_error("Row or column outside the bounds of the map!");

    char_grid[row][column].set_sprite_pos(new_pos);
}

void Map::update_position_table(char entity, const Point &pos)
{
    if (position_table.count(entity) != 0)
    {
        position_table[entity].push_back(pos);
    }
    else
    {
        position_table.emplace(entity, std::vector<Point>{pos});
    }
}

void Map::draw_entities(sf::RenderWindow &window, const std::vector<int> &grid_positions, float line_width)
{
    for (const auto &entry : position_table)
    {
        for (const auto &point : entry.second)
        {
            update_grid_space_pos(point.x, point.y, sf::Vector2f(grid_positions[point.x] + line_width,
                                                         grid_positions[point.y] + line_width));
            window.draw(char_grid[point.x][point.y].get_sprite());
        }
    }
}

void Map::move_player(int dx, int dy, const sf::Texture &player_texture, const sf::Texture &block_texture)
{
    for (auto &point : position_table.at('P'))
    {
        auto dest_point = Point(point.x + dx, point.y + dy);
        if (dest_point.x < columns && dest_point.y < rows && dest_point.x >= 0 && dest_point.y >= 0)
        {
            if (char_grid[dest_point.x][dest_point.y].get_entity() != 'C')
            {
                if (char_grid[dest_point.x][dest_point.y].get_entity() == 'B')
                {
                    for (auto &block_point : position_table.at('B'))
                    {
                        if (block_point.x == dest_point.x && block_point.y == dest_point.y)
                        {
                            block_point.x += dx;
                            block_point.y += dy;

                        }
                    }
                    char_grid[dest_point.x + dx][dest_point.y + dy].set_entity('B');
                    char_grid[dest_point.x + dx][dest_point.y + dy].set_sprite_texture(block_texture);

                }
                update_grid_space(point.x, point.y, MapSpace('#'));
                char_grid[point.x][point.y].set_entity('#');
                point.x = dest_point.x;
                point.y = dest_point.y;
                char_grid[point.x][point.y].set_entity('P');
                char_grid[point.x][point.y].set_sprite_texture(player_texture);
            }
        }
    }
}

bool Map::compute_game_won() const noexcept
{
    for (const auto &chick_point : position_table.at('C'))
    {
        char above_chick = char_grid[chick_point.x][chick_point.y - 1].get_entity();
        char below_chick = char_grid[chick_point.x][chick_point.y + 1].get_entity();
        char right_chick = char_grid[chick_point.x + 1][chick_point.y].get_entity();
        char left_chick = char_grid[chick_point.x - 1][chick_point.y].get_entity();
        if (left_chick != 'B' || right_chick != 'B' || below_chick != 'B' || above_chick != 'B')
            return true;
    }
    return false;
}

std::vector<int> Map::get_grid_positions(int map_size, int offset, int rows)
{
    std::vector<int> positions;

    int i;
    for (i = offset; i < map_size; i += map_size / rows)
        positions.push_back(i);

    positions.push_back(i);
    return positions;
}

std::vector<sf::RectangleShape>
Map::get_grid_lines(const std::vector<int> &positions, float map_size, int offset, float line_width)
{
    std::vector<sf::RectangleShape> grid_lines;

    for (const auto &p : positions)
    {
        // row line
        sf::RectangleShape row_line{sf::Vector2f{map_size, line_width}};
        row_line.setPosition(offset, p);
        row_line.setFillColor(sf::Color::Black);
        // column line
        sf::RectangleShape column_line{sf::Vector2f{line_width, map_size}};
        column_line.setPosition(p, offset);
        column_line.setFillColor(sf::Color::Black);

        grid_lines.push_back(row_line);
        grid_lines.push_back(column_line);
    }

    return grid_lines;
}