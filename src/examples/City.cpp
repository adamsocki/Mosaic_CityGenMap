






void CityMapInit()
{

	EntityHandle gameMapHandle = AddEntity(&Data->em, GameMap_Type);
	GameMap* gameMapEntity = (GameMap*)GetEntity(&Data->em, gameMapHandle);
	gameMapEntity->handle = gameMapHandle;

	gameMapEntity->tileCapacity = 1000;
	gameMapEntity->tileCount = 0;
	gameMapEntity->tileSizeInBytes = sizeof(EntityHandle);
	gameMapEntity->tiles = (EntityHandle*)malloc(gameMapEntity->tileCapacity * gameMapEntity->tileSizeInBytes);
	memset(gameMapEntity->tiles, 0, sizeof(EntityHandle) * gameMapEntity->tileCapacity);

	/*gameMapEntity->handle = gameMapHandle;
	gameMapEntity->buildingCapacity = 1000;
	gameMapEntity->buildingCount = 0;
	gameMapEntity->buildingSizeInBytes = sizeof(Building);
	gameMapEntity->buildings = (Building*)malloc(gameMapEntity->buildingCapacity * gameMapEntity-> buildingSizeInBytes);
	memset(gameMapEntity->buildings, 0, sizeof(Building) * gameMapEntity->buildingCapacity);

	gameMapEntity->personCapacity = 1000;
	gameMapEntity->personCount = 0;
	gameMapEntity->personSizeInBytes = sizeof(Person);
	gameMapEntity->persons = (Person*)malloc(gameMapEntity->personCapacity * gameMapEntity->personSizeInBytes);
	memset(gameMapEntity->buildings, 0, sizeof(Person) * gameMapEntity->personCapacity);

	gameMapEntity->roadCapacity = 1000;
	gameMapEntity->roadCount = 0;
	gameMapEntity->roadSizeInBytes = sizeof(Road);
	gameMapEntity->roads = (Road*)malloc(gameMapEntity->roadCapacity * gameMapEntity->roadSizeInBytes);
	memset(gameMapEntity->roads, 0, sizeof(Road) * gameMapEntity->roadCapacity);*/

}

void CityMapTileInit(vec2 tileGridSize, vec2 tileSize)
{
	EntityTypeBuffer* gameMapBuffer = &Data->em.buffers[GameMap_Type];
	GameMap* gameMapEntitiesInBuffer = (GameMap*)gameMapBuffer->entities;

	GameMap* gameMapEntity = &gameMapEntitiesInBuffer[0];

	// CREATE TILES
	int32 tileIndex = 0;
	for (int i = 0; i < tileGridSize.x; i++)
	{
		for (int j = 0; j < tileGridSize.y; j++)
		{
			EntityHandle tileHandle = AddEntity(&Data->em, GameMap_Tile);
			Tile* tileEntity = (Tile*)GetEntity(&Data->em, tileHandle);
				
			tileEntity->handle = tileHandle;
			tileEntity->size = tileSize;
			tileEntity->position.x = i * tileSize.x;
			tileEntity->position.y = j * tileSize.y;

			tileIndex++;

			// ADD TILE HANDLES TO GAME MAP
			gameMapEntity->tiles[gameMapEntity->tileCount] = tileEntity->handle;
			gameMapEntity->tileCount++;
		}
	}



	LoadModelParse(&Data->model);

}


void CityMapLogic()
{



	// check to see if a person can be added
		// check for a building


	// create a building 
		// check to see if location is along road


	// create a road
		// check





}

void CityMapRender()
{

	vec4 color = V4(1.0f, 0.1f, 1.0f, 1.0f);

	EntityTypeBuffer* gameMapBuffer = &Data->em.buffers[GameMap_Type];
	GameMap* gameMapEntitiesInBuffer = (GameMap*)gameMapBuffer->entities;

	GameMap* gameMapEntity = &gameMapEntitiesInBuffer[0];

	// RENDER TILES
	for (int i = 0; i < gameMapEntity->tileCount; i++)
	{
		Tile* tileEntity = (Tile*)GetEntity(&Data->em, gameMapEntity->tiles[i]);
		DrawSprite(tileEntity->position, tileEntity->size, 0, &Data->sprites.bld);
	}

}