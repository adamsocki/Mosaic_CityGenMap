

void CityStateInit()
{
	// init persons in city

	// init buildings int city

	// init roads in city

}

void CityStateLogic(GameMap* gameMapEntity)
{
	// GET MAP
	

	// get tiles

	// determine if 
	
	// calculate person commercial capacity
	gameMapEntity->mapData.commercialBuildingPersonCapacity = {};
	gameMapEntity->mapData.residentialBuildingPersonCapacity = {};
	for (int i = 0; i < gameMapEntity->buildingCount; i++)
	{
		Building* buildingEntity = (Building*)GetEntity(&Data->em, gameMapEntity->buildings[i]);
		switch (buildingEntity->buildingType)
		{
			case BuildingType_Residential_Type1:
			{
				gameMapEntity->mapData.residentialBuildingPersonCapacity += buildingEntity->personCapacity;
				break;
			}
			case BuildingType_Commercial:
			{
				gameMapEntity->mapData.commercialBuildingPersonCapacity += buildingEntity->personCapacity;
				break;
			}
			default:
			{
				break;
			}
		}	
	}
	// for (int i = 0; i < gameMapEntity->buildingCount; i++)
	// {
	// 	Building* buildingEntity = (Building*)GetEntity(&Data->em, gameMapEntity->buildings[i]);
	// 	gameMapEntity->mapData.commercialBuildingPersonCapacity += buildingEntity->personCapacity;
	// }
}


void CityStateRender(GameMap* gameMapEntity)
{
	// display no of peoples
	
	DrawTextScreenPixel(&Game->monoFont, V2(60,100), 10.0f, RGB(1.0f, 1.0f, 1.0f), "Commerical total cap: %d", gameMapEntity->mapData.commercialBuildingPersonCapacity);
	DrawTextScreenPixel(&Game->monoFont, V2(60,120), 10.0f, RGB(1.0f, 1.0f, 1.0f), "Residential total cap: %d", gameMapEntity->mapData.residentialBuildingPersonCapacity);
	DrawTextScreenPixel(&Game->monoFont, V2(60,140), 10.0f, RGB(1.0f, 1.0f, 1.0f), "Total persons: %d", gameMapEntity->personCount);

	// calculate person residential capacity
}