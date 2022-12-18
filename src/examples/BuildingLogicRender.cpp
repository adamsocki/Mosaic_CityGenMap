
void BuildingInit(Building* buildingEntity)
{
    // Building* buildingEntity = (Building*)GetEntity(&Data->em, gameMapEntity->buildings[i]);
    // INIT PERSONS IN BUILDING
	switch (buildingEntity->buildingType)
	{
		case (BuildingType_Commercial):
		{
			buildingEntity->personCapacity = 50;
			break;
		}
		case (BuildingType_Residential_Type1):
		{
			buildingEntity->personCapacity = 2;
			break;
		}
		default:
		{
			break;
		}
	}
	
	buildingEntity->personCount = 0;
	buildingEntity->personSizeInBytes = sizeof(EntityHandle);
	buildingEntity->persons = (EntityHandle*)malloc(buildingEntity->personCapacity * buildingEntity->personSizeInBytes);
	memset(buildingEntity->persons, 0, sizeof(EntityHandle) * buildingEntity->personCapacity);	
}
