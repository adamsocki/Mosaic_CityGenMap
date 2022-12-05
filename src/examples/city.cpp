void CityMapInit()
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
			tileEntity->row = j;
			tileEntity->column = i;
			tileEntity->position.x = i * 2;
			tileEntity->position.z = j * 2 - 10.0f;
			//tileEntity->rotation = AxisAngle(V3(1, 0, 0), 1.5708f);
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




	// check to see if a person can be added
		// check for a building


	// create a building 
		// check to see if location is along road


	// create a road
		
	if (InputPressed(Keyboard, Input_R))
	{	// get current tile arrow
		EntityTypeBuffer* tileArrowBuffer = &Data->em.buffers[TileArrow_Type];
		TileArrow* tileArrowEntity = (TileArrow*)tileArrowBuffer->entities;

		TileArrow* arrowEntity = &tileArrowEntity[0];

		Tile* tileEntity = (Tile*)GetEntity(&Data->em, arrowEntity->tileHandle);

		tileEntity->tileType = TileType_Road;

	}

	if (InputPressed(Keyboard, Input_C))
	{	// get current tile arrow
		EntityTypeBuffer* tileArrowBuffer = &Data->em.buffers[TileArrow_Type];
		TileArrow* tileArrowEntity = (TileArrow*)tileArrowBuffer->entities;

		TileArrow* arrowEntity = &tileArrowEntity[0];

		Tile* tileEntity = (Tile*)GetEntity(&Data->em, arrowEntity->tileHandle);

		tileEntity->tileType = TileType_Commercial;

	}




}

void CityMapRender()
{

	vec4 color = V4(1.0f, 0.1f, 1.0f, 1.0f);

	EntityTypeBuffer* gameMapBuffer = &Data->em.buffers[GameMap_Type];
	GameMap* gameMapEntitiesInBuffer = (GameMap*)gameMapBuffer->entities;

	GameMap* gameMapEntity = &gameMapEntitiesInBuffer[0];

	// Test rotation of tiles
	real32 angle_zMod = 0;

	real32 angle_xMod = 0;

	if (InputPressed(Keyboard, Input_T))
	{
		angle_zMod += Game->deltaTime * 3;
	}
	if (InputPressed(Keyboard, Input_Y))
	{
		angle_zMod -= Game->deltaTime * 3;
	}
	if (InputHeld(Keyboard, Input_U))
	{
		angle_xMod += Game->deltaTime * 3;
	}
	if (InputHeld(Keyboard, Input_I))
	{
		angle_xMod -= Game->deltaTime * 3;
	}

	// RENDER TILES
	for (int i = 0; i < gameMapEntity->tileCount; i++)
	{
		Tile* tileEntity = (Tile*)GetEntity(&Data->em, gameMapEntity->tiles[i]);
		//vec3 position = V3(tileEntity->position.x, tileEntity->position.y, tileEntity->position.z -10.0f);

		//tileEntity->angle_x += angle_xMod;

		//tileEntity->rotation = AxisAngle(V3(1, 0, 0), tileEntity->angle_x);


		switch (tileEntity->tileType)
		{
			case TileType_Road:
			{
				RenderOBJModel(&Game->modelMesh, tileEntity->position, V3(1.0f, 1.0f, 1.0f), color, tileEntity->rotation, &Data->sprites.road_uv);
				break;
			}
			case TileType_Commercial:
			{
				RenderOBJModel(&Game->bldMesh, tileEntity->position, V3(1.0f, 1.0f, 1.0f), color, tileEntity->rotation, &Data->sprites.bld2);
				break;
			}
			default:
			{
				RenderOBJModel(&Game->modelMesh, tileEntity->position, V3(1.0f, 1.0f, 1.0f), color, tileEntity->rotation, &Data->sprites.tile3);

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


