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


	// check capacity of buildings
	


	// if above conditions->add personEntity



	// add person to specific building


}