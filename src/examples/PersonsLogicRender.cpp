void GeneratePerson(Person* personEntity, int32 buildingCount)
{

	// examine world conditions to find propensity of immigrant type
	
	
	personEntity->age = 25;
	//personEntity->incomeBracketType = 
	//personEntity->educationType = 
	//personEntity->commerical


	// calculate residential assignment
	bool buildingAssigned = false;
	personEntity->residentialAssignment = RandiRange(0, buildingCount);
}

void PersonsInit()
{


}

MapData PersonCapacityOccupancyCalc(GameMap* gameMapEntity)
{
	for (int i = 0; i < gameMapEntity->buildingCount; i++)
	{
		Building* buildingEntity = (Building*)GetEntity(&Data->em, gameMapEntity->buildings[i]);
		switch (buildingEntity->buildingType)
		{
			case BuildingType_Residential_Type1:
			{
				gameMapEntity->mapData.residentialOccupancy += buildingEntity->personCount;
				gameMapEntity->mapData.residentialCapacity  += buildingEntity->personCapacity; 
				break;
			}
			case BuildingType_Commercial:
			{
				gameMapEntity->mapData.commercialOccupancy += buildingEntity->personCount;
				gameMapEntity->mapData.commercialCapacity += buildingEntity->personCapacity;
				break;
			}
			default:
			{
				break;
			}
		} 
	}
	// calculate pop delta
	gameMapEntity->mapData.residentialDelta = gameMapEntity->mapData.residentialCapacity - gameMapEntity->mapData.residentialOccupancy;
	gameMapEntity->mapData.commercialDelta = gameMapEntity->mapData.commercialCapacity - gameMapEntity->mapData.commercialOccupancy;
	
	return gameMapEntity->mapData;
}

void PersonsLogic()
{
	//EntityTypeBuffer* buildingBuffer = &Data->em.buffers[Building_Type];
    //Building* buildingEntitiesInBuffer = (Building*)roomBuffer->entities;

	// GENERATION OF PERSONS

	// check to see if there are buildings in the current map
	EntityTypeBuffer* gameMapBuffer = &Data->em.buffers[GameMap_Type];
	GameMap* gameMapEntitiesInBuffer = (GameMap*)gameMapBuffer->entities;
	GameMap* gameMapEntity = &gameMapEntitiesInBuffer[0];

	DrawTextScreenPixel(&Game->monoFont, V2(60,200), 10.0f, RGB(1.0f, 1.0f, 1.0f), "ResDelta: %d", 	gameMapEntity->mapData.residentialDelta);
    
	// check capacity and occupancy of residential buildings
	bool canGeneratePerson = false;
	
	// check number and location of ports of entry

	// CHECK GENERATOR TIMER
	real32 timeSinceLastPlayerGenerated = Data->timerManager.playerGenerationTimer;
	if (timeSinceLastPlayerGenerated > 2.0f )
	{
		canGeneratePerson = true;
		// if capacity is reached, still generate person ? to allow for overcrowding 
	} 
	
	// if above conditions->add personEntity
	if (canGeneratePerson)
	{
		MapData mapData = PersonCapacityOccupancyCalc(gameMapEntity);
		Data->timerManager.playerGenerationTimer = 0;
		
		if (mapData.residentialDelta <= 0)
		{
			int32 value = {};
		}
		else 
		{
			EntityHandle personHandle = AddEntity(&Data->em, Person_Type);
			Person* personEntity = (Person*)GetEntity(&Data->em, personHandle);
			personEntity->handle = personHandle;

			// CREATE PERSON
			GeneratePerson(personEntity, gameMapEntity->buildingCount);

			// assign person to specific building
				// person to building assignment logic	

			Building* buildingEntity = (Building*)GetEntity(&Data->em, gameMapEntity->buildings[personEntity->residentialAssignment]);
			buildingEntity->persons[buildingEntity->personCount] = personHandle;
			buildingEntity->personCount++;

			gameMapEntity->persons[gameMapEntity->personCount] = personHandle;
			gameMapEntity->personCount++;

			for (int i = 0; i < gameMapEntity->buildingCount; i++)
			{
				switch (personEntity->residentialAssignment)
				{
					case 1:
					{
						break;
					}
					default:
					{
						break;
					}
				}
				// income bracket choice
				// transport choice
				
			}
		}

		
	}
	
}