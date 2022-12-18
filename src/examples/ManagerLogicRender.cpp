void ManagerInit(real32 startingMoney)
{

    EntityTypeBuffer* gameMapBuffer = &Data->em.buffers[GameMap_Type];
	GameMap* gameMapEntitiesInBuffer = (GameMap*)gameMapBuffer->entities;

	GameMap* gameMapEntity = &gameMapEntitiesInBuffer[0];


    gameMapEntity->gameManager.currentMoney = startingMoney;
    // gameMapEntity->gameManager.taxTimer
}


void ResidentialTaxLogic(GameMap* gameMapEntity)
{
    bool collectTax = false; 
    if (Data->timerManager.annualTaxationTimer > 10.0f)
    {
        collectTax = true;
    }
    if (collectTax)
    {
        real32 taxCollectionTotal = 0;
        for (int i = 0; i < gameMapEntity->personCount; i++)
        {
            Person* personEntity = (Person*)GetEntity(&Data->em, gameMapEntity->persons[i]);
            switch (personEntity->taxBracket)
            {
                case 1:
                {
                    
                    taxCollectionTotal += 4.0f;
                    break;
                } 
                case 2:
                {
                    taxCollectionTotal += 10.0f;
                    break;
                } 
                case 3:
                {
                    taxCollectionTotal += -1.0f;
                    break;
                }
                default:
                {
                    break;
                } 
            }
        }
        gameMapEntity->gameManager.currentMoney += taxCollectionTotal;
        Data->timerManager.annualTaxationTimer = 0;
    }
   
}

void ManagerLogic(GameMap* gameMapEntity)
{
    ResidentialTaxLogic(gameMapEntity);
}
