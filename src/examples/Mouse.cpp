void MouseInit()
{
  ///  EntityHandle mouseHandle = AddEntity(&Data->em, Mouse);
   // Mouse* mouseEntity = (Mouse*)GetEntity(&Data->em, mouseHandle);

    //mouseEntity->handle = mouseHandle;
    //mouseEntity->position = {};
}

void MouseLogic()
{
    // EntityTypeBuffer* gameMapMouseBuffer = &Data->em.buffers[GameMap_Mouse];
    // Mouse* mouseEntitiesInBuffer = (Mouse*)gameMapMouseBuffer->entities;

    // Mouse* mouseEntity = mouseEntitiesInBuffer[0];
    
    // if (InputHeld(Keyboard, Input_UpArrow))
    // {
    //     mouseEntity->position.z += (1.0f * Game->deltaTime);
    // }
    // if (InputHeld(Keyboard, Input_DownArrow))
    // {
    //     mouseEntity->position.z -= (-1.0f * Game->deltaTime);
    // }
    // if (InputHeld(Keyboard, Input_LeftArrow))
    // {
    //     mouseEntity->position.x -= (1.0f * Game->deltaTime);
    // }
    // if (InputHeld(Keyboard, Input_RightArrow))
    // {
    //     mouseEntity->position.x += (-1.0f * Game->deltaTime);
    // }
}

void MouseRender()
{
    // EntityTypeBuffer* gameMapMouseBuffer = &Data->em.buffers[GameMap_Mouse];
    // Mouse* mouseEntitiesInBuffer = (Mouse*)gameMapMouseBuffer->entities;

    // Mouse* mouseEntity = mouseEntitiesInBuffer[0];
    // //vec3 position = V3(0.0f , 10.0f, 0.0f + change_z );
    // //quaternion quat = IdentityQuaternion();

    // RenderOBJModel(&Game->modelMesh, mouseEntity->position, V3(1.0f, 1.0f, 1.0f), V4(0), IdentityQuaternion(), &Data->sprites.tile3);
}