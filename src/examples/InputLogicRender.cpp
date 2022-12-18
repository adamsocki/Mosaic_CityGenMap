//  TileArrowEntityInit();
// 	TileArrowLogic();
//  CameraInputControl();
//  InputLogic();
//  Gameplay

bool CostCheckForConstruction(GameMap * gameMapEntity, real32 buildingCost)
{
	bool canBuild = false;
	if (gameMapEntity->gameManager.currentMoney >= buildingCost)
	{
		canBuild = true;
	}
	return canBuild;
}
void TileArrowEntityInit()
{
	EntityHandle tileArrowHandle = AddEntity(&Data->em, TileArrow_Type);
	TileArrow* tileArrowEntity = (TileArrow*)GetEntity(&Data->em, tileArrowHandle);

	tileArrowEntity->handle = tileArrowHandle;
	tileArrowEntity->position = V3(0, 0, -10);

}

void TileArrowLogic()
{
	EntityTypeBuffer* tileArrowBuffer = &Data->em.buffers[TileArrow_Type];
	TileArrow* tileArrowEntity = (TileArrow*)tileArrowBuffer->entities;

	TileArrow *arrowEntity = &tileArrowEntity[0];

	EntityTypeBuffer* gameMapBuffer = &Data->em.buffers[GameMap_Type];
	GameMap* gameMapEntitiesInBuffer = (GameMap*)gameMapBuffer->entities;

	GameMap* gameMapEntity = &gameMapEntitiesInBuffer[0];

	
	if (InputPressed(Keyboard, Input_UpArrow))
	{
		arrowEntity->row++;
		//arrowEntity->position = tileEntity
	}
	if (InputPressed(Keyboard, Input_DownArrow))
	{
		arrowEntity->row--;
	}
	if (InputPressed(Keyboard, Input_RightArrow))
	{
		arrowEntity->column--;
	}
	if (InputPressed(Keyboard, Input_LeftArrow))
	{
		arrowEntity->column++;
	}

	for (int i = 0; i < gameMapEntity->tileCount; i++)
	{
		Tile* tileEntity = (Tile*)GetEntity(&Data->em, gameMapEntity->tiles[i]);

		if (arrowEntity->column == tileEntity->column && arrowEntity->row == tileEntity->row)
		{
			arrowEntity->tileHandle = tileEntity->handle;
			
			arrowEntity->position = tileEntity->position;
			arrowEntity->developed = tileEntity->developed;

			arrowEntity->position.y += 0.1f;
			arrowEntity->meshType = Tile_Mesh;
			arrowEntity->rotation = tileEntity->rotation;
		}
	}
}

void CameraInputControl()
{
	Camera* cam = &Game->camera;
	real32 cameraSpeed = 8.0f;
	real32 rotationSpeed = 0.4f;
    
	if (InputHeld(Keyboard, Input_W))
    {
        Game->cameraPosition.z += cameraSpeed * Game->deltaTime;
    }
    if (InputHeld(Keyboard, Input_S))
    {
        Game->cameraPosition.z -= cameraSpeed * Game->deltaTime;
    }
    if (InputHeld(Keyboard, Input_A))
    {
        Game->cameraRotation.x += rotationSpeed * Game->deltaTime;
    }
    if (InputHeld(Keyboard, Input_D))
    {
        Game->cameraRotation.x -= rotationSpeed * Game->deltaTime;
    }
	if (InputHeld(Keyboard, Input_E))
	{
		Game->cameraPosition.y += cameraSpeed * Game->deltaTime;
	}
	if (InputHeld(Keyboard, Input_Q))
	{
		Game->cameraPosition.y -= cameraSpeed * Game->deltaTime;
	}
	// if (InputHeld(Keyboard, Input_C))
	// {
		// Game->cameraRotation.y += rotationSpeed * Game->deltaTime;
	// }
}

void GameplayInputControl(GameMap* gameMapEntity)
{
    // get current tile arrow
	EntityTypeBuffer* tileArrowBuffer = &Data->em.buffers[TileArrow_Type];
	TileArrow* tileArrowEntity = (TileArrow*)tileArrowBuffer->entities;

	TileArrow* arrowEntity = &tileArrowEntity[0];
	bool canBeDeveloped = false;
    //  CREATE COMMERCIAL BUILDING
    if (InputPressed(Keyboard, Input_C))
	{	
		real32 buildingCost = 20.0f; 
		canBeDeveloped = CostCheckForConstruction(gameMapEntity, buildingCost);
		
		if (arrowEntity->developed || !canBeDeveloped)
		{
			// create UI Event asking about what to do here
		}
		else 
		{
			EntityHandle buildingHandle = AddEntity(&Data->em, Building_Type);
			Building* buildingEntity = (Building*)GetEntity(&Data->em, buildingHandle);
			buildingEntity->handle = buildingHandle;
			buildingEntity->tileHandle = tileArrowEntity->handle;
			buildingEntity->buildingType = BuildingType_Commercial;

			gameMapEntity->buildings[gameMapEntity->buildingCount] = buildingHandle;
			gameMapEntity->buildingCount++;
			gameMapEntity->mapData.commercialBuildingPersonCapacity += 50;

			BuildingInit(buildingEntity);

			Tile* tileEntity = (Tile*)GetEntity(&Data->em, arrowEntity->tileHandle);
			tileEntity->entityOnTileHandle = buildingHandle;
			tileEntity->tileType = TileType_CommercialBuilding;
			tileEntity->meshType = CommercialBuilding_Mesh;
			tileEntity->developed = true;

			gameMapEntity->gameManager.currentMoney -= buildingCost;
		}

	}
    //  CREATE RESIDENTIAL BUILDING TYPE1
    if (InputPressed(Keyboard, Input_H))
	{	
		bool canBeDeveloped = false;
		real32 buildingCost = 10.0f;
		
		
		canBeDeveloped = CostCheckForConstruction(gameMapEntity, buildingCost);
		
		// TODO: CREATE MECHANISM THAT DETECTS EXISTING BUILDING / ENTITY ON THE TILE AND WARNS AGAINST DELETION (OR PREVENTS IT)
		if (arrowEntity->developed || !canBeDeveloped)
		{
			// create UI Event asking about what to do here
		}
		else 
		{
			// CREATE THE BUILDING ENTITY 
			EntityHandle buildingHandle = AddEntity(&Data->em, Building_Type);
			Building* buildingEntity = (Building*)GetEntity(&Data->em, buildingHandle);
			buildingEntity->handle = buildingHandle;
			buildingEntity->tileHandle = tileArrowEntity->handle;
			buildingEntity->buildingType = BuildingType_Residential_Type1;
			// INITIALIZE COMPONENTS SPECIFIC TO BUILDING TYPE **BuildingLogicRender.cpp**
			BuildingInit(buildingEntity);
	
			// ADD BUILDING ENTITY HANDLE TO GAMEMAP ENTITY
			gameMapEntity->buildings[gameMapEntity->buildingCount] = buildingHandle;
			gameMapEntity->buildingCount++;
			gameMapEntity->mapData.residentialBuildingPersonCapacity += 2;
	
			// ADD BUILDING ENTITY HANDLE TO tileEntity
			Tile* tileEntity = (Tile*)GetEntity(&Data->em, arrowEntity->tileHandle);
			tileEntity->entityOnTileHandle = buildingHandle;
			// SET THE tileENTITY TO THE NEW TILE TYPE THAT IS BEING CREATED
			tileEntity->tileType = TileType_ResidentialBuilding_Type1;
			tileEntity->meshType = ResidentialBuildingType1_Mesh;
			tileEntity->developed = true;

			// DEDUCT BUILDING COST FROM TOTAL MONEY IN MANAGER
			gameMapEntity->gameManager.currentMoney -= buildingCost;
		}
	}
    //  CREATE ROAD
    if (InputPressed(Keyboard, Input_R))
	{	// get current tile arrow
		EntityTypeBuffer* tileArrowBuffer = &Data->em.buffers[TileArrow_Type];
		TileArrow* tileArrowEntity = (TileArrow*)tileArrowBuffer->entities;

        //  CREATE
		//  add to map
        //  gameMapEntity->infrastructure[gameMapEntity->insfrastructureCount] = 
		TileArrow* arrowEntity = &tileArrowEntity[0];

		Tile* tileEntity = (Tile*)GetEntity(&Data->em, arrowEntity->tileHandle);

		tileEntity->tileType = TileType_Road;
		tileEntity->meshType = Tile_Mesh;
		tileEntity->developed = true;
	}
}

void MousePointerRender()
{
	EntityTypeBuffer* tileArrowBuffer = &Data->em.buffers[TileArrow_Type];
	TileArrow* tileArrowEntity = (TileArrow*)tileArrowBuffer->entities;
	TileArrow* arrowEntity = &tileArrowEntity[0];
	DrawTextScreenPixel(&Game->monoFont, V2(60, 60), 10.0f, RGB(1.0f, 1.0f, 1.0f), "o.x: %.10f", arrowEntity->position.x);

	RenderOBJModel(&Data->meshManager.meshes[arrowEntity->meshType], arrowEntity->position, V3(1.0f, 1.0f, 1.0f), V4(0), arrowEntity->rotation, &Data->sprites.tile3_mouse);
}

void InputInit()
{
	// @TODO - put tile arrow init execution here
}

void InputLogic(GameMap* gameMapEntity)
{
    CameraInputControl();			// @TODO: WORK ON CAMERA INPUT CONTROLLER
	TileArrowLogic();				// POINTER-GRABBER-TILE ARROW 
    GameplayInputControl(gameMapEntity);  		// TODO: things like create buildings
}

void InputRender()
{
	MousePointerRender();
}