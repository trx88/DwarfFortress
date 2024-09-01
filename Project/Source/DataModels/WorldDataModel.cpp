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

int WorldDataModel::GetEntityNextId() const
{
    int nextId = (int)entities.size() + 1;
    return nextId;
}

std::shared_ptr<Entity> WorldDataModel::GetEntityAt(int row, int column) const
{
    for (const auto& pair : entities)
    {
        const auto& entity = pair.second;  // Access the shared_ptr<Entity>
        if (entity->GetRow() == row && entity->GetColumn() == column)
        {
            return entity;
        }
    }

    return nullptr;  // Return nullptr if no entity is found at the position
}

std::shared_ptr<Entity> WorldDataModel::GetEntityById(int id) const
{
    return entities.at(id);
}

std::vector<std::shared_ptr<Entity>> WorldDataModel::GetEntitiesByType(EntityType entityType) const
{
    std::vector<std::shared_ptr<Entity>> entitiesByType;
    for (const auto& entity : entities)
    {
        if (entity.second->GetType() == entityType)
        {
            entitiesByType.push_back(entity.second);
        }
    }

    return entitiesByType;
}

void WorldDataModel::SetMapSize(int newWidth, int newHeight)
{
    mapWidth = newWidth;
    mapHeight = newHeight;
    map.resize(newHeight, std::vector<char>(newWidth, ' '));
}

void WorldDataModel::SetTileAt(int row, int column, char value)
{
    map[row][column] = value;
}

void WorldDataModel::AddEntity(std::shared_ptr<Entity> entity)
{
    entities[entity->GetId()] = entity;
}

void WorldDataModel::RemoveEntity(std::shared_ptr<Entity> entity)
{
    entities.erase(entity->GetId());
}
