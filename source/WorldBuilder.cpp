#include "stdafx.h"
#include "WorldBuilder.h"
#include "CameraComponent.h"
#include "TextureManager.h"
#include "RigidbodyComponent.h"
#include "ScoreComponent.h"
#include "GameOverComponent.h"
#include "StartPointComponent.h"
#include "ImpulseComponent.h"
#include "AssetsManager.h"

using namespace sf;

WorldBuilder::WorldBuilder()
{
}

void WorldBuilder::loadTextures(const string& filename)
{
	auto mapBuffer = AssetsManager::getInstance().getMapBuffer(filename);
	NLTmxMap* tilemap = NLLoadTmxMap(mapBuffer);
	delete mapBuffer;

	// load textures for every tileset
	for (auto tileset : tilemap->tilesets)
	{
		TextureManager::getInstance().loadTexture(tileset->filename);
	}
}

std::vector<std::shared_ptr<GameObject>> WorldBuilder::loadWorld(const string& filename, const sf::Vector2f& offset)
{
	std::vector<std::shared_ptr<GameObject>> objects;

	GameObjectCreator& m_gameObjectCreator = GameObjectCreator::getInstance();	
	
	std::map<std::string, vector<shared_ptr<sf::Sprite>>> m_layers;

	auto mapBuffer = AssetsManager::getInstance().getMapBuffer(filename);

	// now lets load a NLTmxMap
	NLTmxMap* tilemap = NLLoadTmxMap(mapBuffer);
	delete mapBuffer;
	 
	// go through all layers
	//m_layers.resize(tilemap->layers.size());
	for (int layerIdx = 0; layerIdx < (int)tilemap->layers.size(); layerIdx++)
	{
		NLTmxMapLayer* layer = tilemap->layers[layerIdx];
		std::string layerName = layer->name;
		
		int size = layer->width * layer->height;
		
		// go over all elements in the layer
		for (int i = 0; i < size; i++)
		{
			int grid = layer->data[i];
			
			if (grid == 0)
			{
				// 0 means there is no tile at this grid position.

				// This continue also indicates that the layers are not 
				// represented as two-dimensional arrays, but 
				// only a list of tiles sorted by position from top left
				// to bottom right. (Hint: position could be useful for 
				// quickly finding, which tiles to cull from current 
				// viewport.)					
				continue;
			}

			// get tileset and tileset texture
			NLTmxMapTileset* tileset = tilemap->getTilesetForGrid(grid);
			Vector2i tileSize(tilemap->tileWidth, tilemap->tileHeight);
			Texture texture = TextureManager::getInstance().getTexture(tileset->filename);
			
			// horizontal tile count in tileset texture
			int tileCountX = texture.getSize().x / tileSize.x;

			// calcualte position of tile
			Vector2f position;
			position.x = (i % layer->width) * (float)tileSize.x;
			position.y = (i / layer->width) * (float)tileSize.y;
			position += offset;

			// calculate 2d idx of tile in tileset texture
			int idx = grid - tileset->firstGid;
			int idxX = idx % tileCountX;
			int idxY = idx / tileCountX;

			// calculate source area of tile in tileset texture
			IntRect source(idxX * tileSize.x, idxY * tileSize.y, tileSize.x, tileSize.y);
						
			auto sprite = std::make_shared<sf::Sprite>();
			sprite->setTexture(TextureManager::getInstance().getTexture(tileset->filename));
			sprite->setTextureRect(source);
			sprite->setPosition(position);
			
			m_layers[layerName].push_back(sprite);
		}
	}

	std::shared_ptr<GameObject> map = m_gameObjectCreator.createMap(sf::Vector2f(0.0f, 0.0f), m_layers);
	objects.push_back(map);

	
	// go through all object layers
	for (auto group : tilemap->groups)
	{
		// go over all objects per layer
		for (auto object : group->objects)
		{
			Vector2f position(object->x, object->y);
			position += offset;
			// example to get a texture rectangle for a sprite
			FloatRect bounds(position.x, position.y, object->width, object->height);

			if (object->name == "StartPoint" && object->type == "trigger")
			{
				sf::FloatRect box{ static_cast<float>(object->x), static_cast<float>(object->y), static_cast<float>(object->width), static_cast<float>(object->height) };
				sf::Vector2f position{ static_cast<float>(object->x), static_cast<float>(object->y) };

				std::shared_ptr<GameObject> startPoint = m_gameObjectCreator.createStartPoint(position, object->properties[0]->value,box);
				objects.push_back(startPoint);

			}

			else if (object->name == "GameOver" && object->type == "trigger")
			{
				sf::FloatRect box{ static_cast<float>(object->x), static_cast<float>(object->y), static_cast<float>(object->width), static_cast<float>(object->height) };
				sf::Vector2f position{ static_cast<float>(object->x), static_cast<float>(object->y) };

				std::shared_ptr<GameObject> gameOver = m_gameObjectCreator.createGameOverTrigger(box, position);
				objects.push_back(gameOver);
			}

			else if (object->name == "staticCollider" && object->type == "box")
			{
				sf::FloatRect box { static_cast<float>(object->x), static_cast<float>(object->y), static_cast<float>(object->width), static_cast<float>(object->height) };
				sf::Vector2f position { static_cast<float>(object->x), static_cast<float>(object->y) };

				std::shared_ptr<GameObject> staticCollider = m_gameObjectCreator.createStaticCollider(box,position);
				objects.push_back(staticCollider);
			}

			else if (object->name == "flipperCollider" && object->type == "box")
			{
				sf::FloatRect box { static_cast<float>(object->x), static_cast<float>(object->y), static_cast<float>(object->width), static_cast<float>(object->height) };
				sf::Vector2f position { static_cast<float>(object->x), static_cast<float>(object->y) };
				std::shared_ptr<GameObject> flipperCollider = m_gameObjectCreator.createFlipperCollider(box,position);
				objects.push_back(flipperCollider);
			}

			else if (object->name == "mouse" && object->type == "trigger")
			{
				sf::FloatRect box{ static_cast<float>(object->x), static_cast<float>(object->y), static_cast<float>(object->width), static_cast<float>(object->height) };
				sf::Vector2f position{ static_cast<float>(object->x), static_cast<float>(object->y) };

				std::shared_ptr<GameObject> mouse = m_gameObjectCreator.createMouse(box, position);
				objects.push_back(mouse);
			}

			else if (object->name == "FlipperLeft")
			{
				std::shared_ptr<GameObject> flipperLeft = m_gameObjectCreator.createLeftFlipper(sf::Vector2f(object->x, object->y));
				objects.push_back(flipperLeft);
			}

			else if (object->name == "FlipperRightTop")
			{
				std::shared_ptr<GameObject> flipperRightTop = m_gameObjectCreator.createRightFlipper(sf::Vector2f(object->x, object->y));
				objects.push_back(flipperRightTop);
			}

			else if (object->name == "FlipperRightBottom")
			{
				std::shared_ptr<GameObject> flipperRightBottom = m_gameObjectCreator.createRightFlipper(sf::Vector2f(object->x, object->y));
				objects.push_back(flipperRightBottom);
			}
			else if (object->type == "character")
			{
				int id = std::stoi(object->properties[0]->value);				
				sf::Vector2f position{ static_cast<float>(object->x), static_cast<float>(object->y) };
				sf::FloatRect box{ static_cast<float>(object->x), static_cast<float>(object->y), static_cast<float>(object->width), static_cast<float>(object->height) };

				std::shared_ptr<GameObject> character = m_gameObjectCreator.createCharacter(box,id, position);
				objects.push_back(character);
			}
			else if (object->type == "area")
			{
				int id = std::stoi(object->properties[0]->value);
				sf::Vector2f position{ static_cast<float>(object->x), static_cast<float>(object->y) };
				sf::FloatRect box{ static_cast<float>(object->x), static_cast<float>(object->y), static_cast<float>(object->width), static_cast<float>(object->height) };

				std::shared_ptr<GameObject> area = m_gameObjectCreator.createCharacterArea(box, id, position);
				objects.push_back(area);
			}
		}
	}

	std::shared_ptr<GameObject> score = m_gameObjectCreator.createScore(sf::Vector2f());

	objects.push_back(score);
	
	return objects;
}

void WorldBuilder::registerObserver(std::vector<std::shared_ptr<GameObject>> objects)
{
	for (auto i : objects)
	{
		if (i->getName() == "ball")
		{
			for (auto i2 : objects)
			{
				if (i2->getName() == "mouse")
				{
					i->getComponent<Rigidbody>()->addObserver(*i2->getComponent<ScoreComponent>());
				}
				if (i2->getName() == "end")
				{
					i->getComponent<Rigidbody>()->addObserver(*i2->getComponent<GameOverComponent>());
				}
				if (i2->getName() == "start")
				{
					i->getComponent<Rigidbody>()->addObserver(*i2->getComponent<StartPointComponent>());
				}
				if (i2->getName() == "flipperCollider")
				{
					i->getComponent<Rigidbody>()->addObserver(*i2->getComponent<ImpulseComponent>());
				}
			}
		}
	}
}