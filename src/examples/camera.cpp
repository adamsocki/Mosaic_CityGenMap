void SetCameraToMap()
{

   // EntityTypeBuffer* gameMapBuffer = &Data->em.buffers[GameMap_Type];
	//GameMap* gameMapEntitiesInBuffer = (GameMap*)gameMapBuffer->entities;

	//GameMap* gameMapEntity = &gameMapEntitiesInBuffer[0];


    Camera* cam = &Game->camera;

    //int32 r_tile = RandiRange(0, gameMapEntity->tileCount);
    //EntityHandle randomTile = gameMapEntity->tiles[r_tile];

    //Tile* tileEntityRand = (Tile*)GetEntity(&Data->em, randomTile);
    //vec3 posToStartCamera = tileEntityRand->position;
    vec3 posToStartCamera = {};
    //posToStartCamera.x -= 10.0f;
    posToStartCamera.x = 9.f;
    posToStartCamera.y = 10.0f;
    posToStartCamera.z = -18.0f;

    Game->cameraRotation.x += 0.3f;

    Game->cameraPosition = posToStartCamera;


}