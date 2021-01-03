#ifndef TILEMAP_H
#define TILEMAP_H


#include "Entity.h"



enum TileMapTypes
{
    Solid,
    TileSpawner

};

 class TileMap : public Drawable, public Transformable
    {
    
   private:
    int fromX;
    int toX;
    int fromY;
    int toY;
    int layer;
    float gridSizeF;
    int gridSizeI;
    Vector2i maxSizeWorldGrid;
    Vector2f maxSizeWorldF;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    RectangleShape collisionBox;
    VideoMode collision;
   
    public:
        VertexArray m_vertices;
        Texture m_tileset;
        TileMap();
        ~TileMap();
        const Vector2f& getMaxSize() const;
        const Vector2i& getMaxSizeGrid() const;
        bool load(const string& tileset, Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height); 
        void render(RenderTarget& target);
        void updateTileCollision(Entity* entity, const float& dt);


 };
#endif // !TILEMAP_H
