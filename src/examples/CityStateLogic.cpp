

void CityStateInit()
{
	// init persons in city

	// init buildings int city

	// init roads in city

}

void CityStateLogic()
{
	// GET MAP
	EntityTypeBuffer* gameMapBuffer = &Data->em.buffers[GameMap_Type];
	GameMap* gameMapEntitiesInBuffer = (GameMap*)gameMapBuffer->entities;

	GameMap* gameMapEntity = &gameMapEntitiesInBuffer[0];

	// get tiles

	// determine if 
	
	// calculate person commercial capacity
	int32 commercialBuildingPersonCapacity = {};
	int32 residentialBuildingPersonCapacity = {};
	for (int i = 0; i < gameMapEntity->buildingCount; i++)
	{
		Building* buildingEntity = (Building*)GetEntity(&Data->em, gameMapEntity->buildings[i]);
		switch (buildingEntity->buildingType)
		{
			case BuildingType_Residential_Type1:
			{
				residentialBuildingPersonCapacity += buildingEntity->personCapacity;
				break;
			}
			case BuildingType_Commercial:
			{
				commercialBuildingPersonCapacity += buildingEntity->personCapacity;
				break;
			}
			default:
			{
				break;
			}
		}
		
	}
	
	DrawTextScreenPixel(&Game->monoFont, V2(60,100), 10.0f, RGB(1.0f, 1.0f, 1.0f), "Commerical total cap: %d", commercialBuildingPersonCapacity);
	DrawTextScreenPixel(&Game->monoFont, V2(60,120), 10.0f, RGB(1.0f, 1.0f, 1.0f), "Residential total cap: %d", residentialBuildingPersonCapacity);
	DrawTextScreenPixel(&Game->monoFont, V2(60,140), 10.0f, RGB(1.0f, 1.0f, 1.0f), "Total persons: %d", gameMapEntity->personCount);
	// calculate person residential capacity
	
	for (int i = 0; i < gameMapEntity->buildingCount; i++)
	{
		Building* buildingEntity = (Building*)GetEntity(&Data->em, gameMapEntity->buildings[i]);
		commercialBuildingPersonCapacity += buildingEntity->personCapacity;
	}
}


void CityStateRender()
{
	// display no of peoples
	//DrawSpriteScreen(V2(1, 1), V2(1, 1), 0, &Data->sprites.pop_sprite);
}