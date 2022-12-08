void PersonsInit()
{

	// INIT PERSONS IN BUILDING
	EntityTypeBuffer* gameMapBuffer = &Data->em.buffers[GameMap_Type];
	GameMap* gameMapEntitiesInBuffer = (GameMap*)gameMapBuffer->entities;

	GameMap* gameMapEntity = &gameMapEntitiesInBuffer[0];

	for (int i = 0; i < gameMapEntity->buildingCount; i++)
	{
		Building* tileEntity = (Tile*)GetEntity(&Data->em, tileHandle);

	}
}



void PersonsLogic()
{

	// check to see if there are buildings
	EntityTypeBuffer* gameMapBuffer = &Data->em.buffers[GameMap_Type];
	GameMap* gameMapEntitiesInBuffer = (GameMap*)gameMapBuffer->entities;

	GameMap* gameMapEntity = &gameMapEntitiesInBuffer[0];
	// check capacity and occupancy of residential buildings
	MapData mapData = {};

	for (int i = 0; i < gameMapEntity->buildingCount; i++)
	{
		Building* buildingEntity = (Tile*)GetEntity(&Data->em, gameMapEntity->buildings[i]);
		switch (buildingEntity->buildingType):
		{
			case BuildingType_Residential_Type1:
			{
				mapData.residentialOccupancy += buildingEntity->personCount;
				mapData.residentialCapacity  += buildingEntity->personCapacity; 
				break;
			}
			case BuildType_Commercial:
			{
				break;
			}
			default:
			{
				break;
			}
		} 
	}

	// check number and location of ports of entry

	


	// if above conditions->add personEntity



	// add person to specific building

}