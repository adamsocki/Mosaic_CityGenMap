


void BuildingInit(Building* buildingEntity)
{
    //Building* buildingEntity = (Building*)GetEntity(&Data->em, gameMapEntity->buildings[i]);
    // INIT PERSONS IN BUILDING

	buildingEntity->personCapacity = 50;
	buildingEntity->personCount = 0;
	buildingEntity->personSizeInBytes = sizeof(EntityHandle);
	buildingEntity->persons = (EntityHandle*)malloc(buildingEntity->personCapacity * buildingEntity->personSizeInBytes);
	memset(buildingEntity->persons, 0, sizeof(EntityHandle) * buildingEntity->personCapacity);
	
}


