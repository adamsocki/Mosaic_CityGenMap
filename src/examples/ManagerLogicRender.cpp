void ManagerInit(real32 startingMoney)
{

    EntityTypeBuffer* gameMapBuffer = &Data->em.buffers[GameMap_Type];
	GameMap* gameMapEntitiesInBuffer = (GameMap*)gameMapBuffer->entities;

	GameMap* gameMapEntity = &gameMapEntitiesInBuffer[0];


    gameMapEntity->gameManager.currentMoney = startingMoney;
    // gameMapEntity->gameManager.taxTimer
}


void ManagerLogic()
{
        
}
