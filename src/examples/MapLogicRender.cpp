void CityMapEntitiesInit()
{

	// INIT TILES
	EntityHandle gameMapHandle = AddEntity(&Data->em, GameMap_Type);
	GameMap* gameMapEntity = (GameMap*)GetEntity(&Data->em, gameMapHandle);
	gameMapEntity->handle = gameMapHandle;

	gameMapEntity->tileCapacity = 1000;
	gameMapEntity->tileCount = 0;
	gameMapEntity->tileSizeInBytes = sizeof(EntityHandle);
	gameMapEntity->tiles = (EntityHandle*)malloc(gameMapEntity->tileCapacity * gameMapEntity->tileSizeInBytes);
	memset(gameMapEntity->tiles, 0, sizeof(EntityHandle) * gameMapEntity->tileCapacity);

	// INIT PERSONS
	gameMapEntity->personCapacity = 8000;
	gameMapEntity->personCount = 0;
	gameMapEntity->personSizeInBytes = sizeof(EntityHandle);
	gameMapEntity->persons = (EntityHandle*)malloc(gameMapEntity->personCapacity * gameMapEntity->personSizeInBytes);
	memset(gameMapEntity->persons, 0, sizeof(EntityHandle) * gameMapEntity->personCapacity);
	
	// INIT ROADS
	gameMapEntity->roadCapacity = 8000;
	gameMapEntity->roadCount = 0;
	gameMapEntity->roadSizeInBytes = sizeof(EntityHandle);
	gameMapEntity->roads = (EntityHandle*)malloc(gameMapEntity->roadCapacity * gameMapEntity->roadSizeInBytes);
	memset(gameMapEntity->roads, 0, sizeof(EntityHandle) * gameMapEntity->roadCapacity);
	

	// INIT BUILDINGS
	gameMapEntity->buildingCapacity = 8000;
	gameMapEntity->buildingCount = 0;
	gameMapEntity->buildingSizeInBytes = sizeof(EntityHandle);
	gameMapEntity->buildings = (EntityHandle*)malloc(gameMapEntity->buildingCapacity * gameMapEntity->buildingSizeInBytes);
	memset(gameMapEntity->buildings, 0, sizeof(EntityHandle) * gameMapEntity->buildingCapacity);



	
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
			tileEntity->tileType = TileType_Grass; 
			tileEntity->row = j;
			tileEntity->column = i;
			tileEntity->position.x = i * 2;
			tileEntity->position.z = j * 2 - 10.0f;
			//tileEntity->rotation = AxisAngle(V3(1, 0, 0), 1.5708f);
			tileEntity->meshType = Tile_Mesh;
			tileEntity->rotation = IdentityQuaternion();
			tileIndex++;

			// ADD TILE HANDLES TO GAME MAP
			gameMapEntity->tiles[gameMapEntity->tileCount] = tileEntity->handle;
			gameMapEntity->tileCount++;
		}
	}
}



void CityMapLogic()
{
	
	
}

void MapRender(GameMap* gameMapEntity)
{
	vec4 color = V4(1.0f, 0.1f, 1.0f, 1.0f);

	// RENDER TILES
	for (int i = 0; i < gameMapEntity->tileCount; i++)
	{
		Tile* tileEntity = (Tile*)GetEntity(&Data->em, gameMapEntity->tiles[i]);
		
		switch (tileEntity->tileType)
		{
			case TileType_Road:
			{
				RenderOBJModel(&Data->meshManager.meshes[tileEntity->meshType], tileEntity->position, V3(1.0f, 1.0f, 1.0f), color, tileEntity->rotation, &Data->sprites.road_uv);
				break;
			}
			case TileType_CommercialBuilding:
			{
				RenderOBJModel(&Data->meshManager.meshes[tileEntity->meshType], tileEntity->position, V3(1.0f, 1.0f, 1.0f), color, tileEntity->rotation, &Data->sprites.bld2);
				break;
			}
			case TileType_Test:
			{
				RenderOBJModel(&Data->meshManager.meshes[tileEntity->meshType], tileEntity->position, V3(1.0f, 1.0f, 1.0f), color, tileEntity->rotation, &Data->sprites.tile3);
				break;
			}
			case TileType_ResidentialBuilding_Type1:
			{
				RenderOBJModel(&Data->meshManager.meshes[tileEntity->meshType], tileEntity->position, V3(1.0f, 1.0f, 1.0f), color, tileEntity->rotation, &Data->sprites.tile3);
				break;
			}
			default:
			{
				RenderOBJModel(&Data->meshManager.meshes[tileEntity->meshType], tileEntity->position, V3(1.0f, 1.0f, 1.0f), color, tileEntity->rotation, &Data->sprites.tile3);
				break;
			}
		}


		/*if (!tileEntity->mouseOver)
		{
			RenderOBJModel(&Game->modelMesh, tileEntity->position, V3(1.0f, 1.0f, 1.0f), color, tileEntity->rotation, &Data->sprites.tile3);
		}
		else
		{
			RenderOBJModel(&Game->modelMesh, tileEntity->position, V3(1.0f, 1.0f, 1.0f), color, tileEntity->rotation, &Data->sprites.tile3_mouse);
		}*/
	}
}


