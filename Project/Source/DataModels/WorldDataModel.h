#pragma once
#include <vector>
#include <unordered_map>
#include <memory>
#include <string>

//Forward declaration
class Entity;

class WorldDataModel
{
private:
    int mapWidth, mapHeight = 0;
    std::vector<std::vector<char>> map;
    std::unordered_map<int, std::shared_ptr<Entity>> entities;

public:
    WorldDataModel();
    ~WorldDataModel();
#pragma region Getters
    int GetWidth() const;
    int GetHeight() const;
    char GetTileAt(int row, int column) const;
    std::shared_ptr<Entity> GetEntityAt(int x, int y) const;
    std::shared_ptr<Entity> GetEntityById(int id) const;
    std::vector<std::shared_ptr<Entity>> GetEnemies() const;
#pragma endregion    
#pragma region Setters
    void SetMapSize(int newWidth, int newHeight);
    void SetTileAt(int row, int column, char value);
    void AddEntity(std::shared_ptr<Entity> entity);
#pragma endregion

};
