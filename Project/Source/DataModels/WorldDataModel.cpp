#include "WorldDataModel.h"

WorldDataModel::WorldDataModel() : mapWidth(0), mapHeight(0)
{
}

WorldDataModel::~WorldDataModel()
{
    
}

int WorldDataModel::GetWidth() const
{
    return mapWidth;
}

int WorldDataModel::GetHeight() const
{
    return mapHeight;
}

char WorldDataModel::GetTileAt(int row, int column) const
{
    if (column < 0 || column >= mapWidth || row < 0 || row >= mapHeight)
    {
        return ' ';
    }
    return map[row][column];
}

std::shared_ptr<Entity> WorldDataModel::GetEntityAt(int x, int y) const
{
    return std::shared_ptr<Entity>();
}

std::shared_ptr<Entity> WorldDataModel::GetEntityById(int id) const
{
    return std::shared_ptr<Entity>();
}

std::vector<std::shared_ptr<Entity>> WorldDataModel::GetEnemies() const
{
    return std::vector<std::shared_ptr<Entity>>();
}

void WorldDataModel::SetMapSize(int newWidth, int newHeight)
{
    map.resize(newHeight, std::vector<char>(newWidth, '.'));
}

void WorldDataModel::SetTileAt(int row, int column, char value)
{
    map[row][column] = value;
}

void WorldDataModel::AddEntity(std::shared_ptr<Entity> entity)
{
    int lastAddedId = entities.size();
    //set entity id
    entities[++lastAddedId] = entity;
}
