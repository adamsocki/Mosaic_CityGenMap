

void CityStateInit()
{
	// init persons in city





	// init buildings int city

	// init roads in city

	//

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
	for (int i = 0; i < gameMapEntity->buildingCount; i++)
	{
		Building* buildingEntity = (Building*)GetEntity(&Data->em, gameMapEntity->buildings[i]);
		commercialBuildingPersonCapacity += buildingEntity->personCapacity;
	}
	
	DrawTextScreenPixel(&Game->monoFont, V2(60,140), 10.0f, RGB(1.0f, 1.0f, 1.0f), "Commerical total cap: %d", commercialBuildingPersonCapacity);
	
	
	
	



}


void CityStateRender()
{
	// display no of peoples
	DrawTextScreenPixel(&Game->monoFont, V2(60,100), 10.0f, RGB(1.0f, 1.0f, 1.0f), "Persons: %d", 1);
	DrawSpriteScreen(V2(1, 1), V2(1, 1), 0, &Data->sprites.pop_sprite);
}