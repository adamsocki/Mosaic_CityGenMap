Ray MousePositionToWorldRay(Camera *camera, vec2 mousePos) {
    Ray result = {};
    
    //Transform camTrans = camera->entity.worldTransform;

    mat4 camWorld = TRS(Game->cameraPosition, Game->cameraRotation, V3(1));

    switch (camera->type) {
        case CameraType_Perspective: {
            vec2 mousePosSigned = (mousePos - V2(0.5f)) * 2;
            vec3 rayNDS = V3(mousePosSigned, 1.0f);

            vec4 rayClip = V4(rayNDS.x, rayNDS.y, -1.0f, 1.0f);

            mat4 invProjection;
            Inverse(camera->projection, &invProjection);

            vec4 rayEye = invProjection * rayClip;
            rayEye.z = 1;
            rayEye.w = 0.0;

            mat4 invView;
            Inverse(camera->view, &invView);
            // This is the direction
                       
            vec4 rayWorld4 = invView * rayEye;
            vec3 rayWorld = Normalize(rayWorld4.xyz);
            
            result.origin = rayEye.xyz;
            result.direction = rayWorld;

           // result.origin = Game->cameraPosition;
        } break;

         case CameraType_Orthographic: {
            // mouse position is normalized and I want it on the range -1 to 1
            vec2 mousePosSigned = mousePos - V2(0.5f, 0.5f);

            vec2 mouseOnNearPlane = V2(mousePosSigned.x * camera->width * camera->size,
                                       mousePosSigned.y * camera->height * camera->size);

            vec3 mouseWorld = MultiplyPoint(camWorld, V3(mouseOnNearPlane, 0));
            result.direction = Rotate(Game->cameraRotation, FORWARD);
            result.origin = mouseWorld;
        } break;
    }
    return result;
}



void MouseEntityInit()
{
    EntityHandle mouseHandle = AddEntity(&Data->em, Mouse_Type);
    MouseEntity* mouseEntity = (MouseEntity*)GetEntity(&Data->em, mouseHandle);

    mouseEntity->handle = mouseHandle;
    mouseEntity->position = V3(0,0,-10);
}

void MouseLogic()
{
    EntityTypeBuffer* mouseBuffer = &Data->em.buffers[Mouse_Type];
    MouseEntity* mouseEntitiesInBuffer = (MouseEntity*)mouseBuffer->entities;
    EntityTypeBuffer* gameMapBuffer = &Data->em.buffers[GameMap_Type];
    GameMap* gameMapEntitiesInBuffer = (GameMap*)gameMapBuffer->entities;

    GameMap* gameMapEntity = &gameMapEntitiesInBuffer[0];
    Tile* tileEntityTest = (Tile*)GetEntity(&Data->em, gameMapEntity->tiles[0]);

    MouseEntity* mouseEntity = &mouseEntitiesInBuffer[0];
    Camera* cam = &Game->camera;
    vec3 cameraPosition = Game->cameraPosition;
    
    vec2 mousePos = Input->mousePosNormSigned;
    //mousePos.x = mousePos.x / cam->width;

   // mousePos.y = mousePos.y + 1.0f;
    Ray rayMouse = MousePositionToWorldRay(cam, mousePos);

    Plane p1 = MakePlane(tileEntityTest->position, IdentityQuaternion());

    real32 t_;

    bool rayPlaneBool1 = RaycastPlane(p1, rayMouse, &t_);

   // real32 t = t_;

    //DrawTextScreenPixel(&Game->monoFont, V2(60, 60), 10.0f, RGB(1.0f, 1.0f, 1.0f), "m.x: %.10f", mousePos.x);
   // DrawTextScreenPixel(&Game->monoFont, V2(60, 100), 10.0f, RGB(1.0f, 1.0f, 1.0f), "m.y: %.10f", mousePos.y);

    vec3 pointOnRay1 = PointAt(rayMouse, t_);
    vec3 valueToShow;
    valueToShow = pointOnRay1;
    valueToShow.z = -pointOnRay1.y;
    valueToShow.y = 0;
    valueToShow.x = -pointOnRay1.x;


    DrawMesh(&Game->cube, p1.point, Game->cameraRotation, V3(1), RGB(1.0f, 0.3f, 0.3f));
    RenderOBJModel(&Data->meshManager.meshes[Tile_Mesh], valueToShow, V3(1.0f, 1.0f, 1.0f), V4(0), IdentityQuaternion(), &Data->sprites.tile3);


    for (int i = 0; i < gameMapEntity->tileCount; i++)
    {
        Tile* tileEntity = (Tile*)GetEntity(&Data->em, gameMapEntity->tiles[i]);
        // Ray rayMouse = MousePositionToWorldRay(cam, mousePos);

        Plane plane = MakePlane(tileEntity->position, IdentityQuaternion());

        real32 t;

        bool rayPlaneBool = RaycastPlane(plane, rayMouse, &t);
        vec3 pointOnRay = PointAt(rayMouse, t);
        pointOnRay.y = 0;
        pointOnRay.x = -pointOnRay.x;

        RenderOBJModel(&Data->meshManager.meshes[Tile_Mesh], pointOnRay, V3(1.0f, 1.0f, 1.0f), V4(0), IdentityQuaternion(), &Data->sprites.tile3);
    } 

    //vec3 rayMousetest = rayMouse.origin;
    //rayMousetest.z -= 100;
    //vec3 rayPoint = PointAt()

   // real32 distanceCtoP0 = Distance(Game->cameraPosition, tileEntityTest->position);
   // vec3 rayCto0 = PointAt(rayMouse, -distanceCtoP0);

    //vec3 position = V3(tileEntityTest->position.x, tileEntityTest->position.y, tileEntityTest->position.z - 10.0f);
    //
    //real32 distance1 = Distance(rayMouse.origin, position);
    //;

    //vec3 pRay1 = PointAt(rayMouse, distance1);
    //rayMouse.origin.z -= 10.0f;
    //Plane p1 = MakePlane(pRay1, IdentityQuaternion());
   // rayMouse.origin.z = rayMouse.origin.z - 10;
    //RenderOBJModel(&Game->modelMesh, rayMouse.origin, V3(1.0f, 1.0f, 1.0f), V4(0), IdentityQuaternion(), &Data->sprites.tile3);

   // DrawTextScreenPixel(&Game->monoFont, V2(60, 60), 10.0f, RGB(1.0f, 1.0f, 1.0f), "o.x: %.10f", rayMouse.origin.x);
    // calculate distace from camera to mouseLogic
  
   // DrawMesh(&Game->cube, p1.point,Game->cameraRotation, V3(1), RGB(1.0f, 0.3f, 0.3f));
    
   
   // 

  //      real32 t1 = 0.0f;

  //  Plane p1 = MakePlane(pRay1, Game->cameraRotation);

   // bool rayPlaneBool1 = RaycastPlane(p1, rayMouse, &t1);
        
    //DrawTextScreenPixel(&Game->monoFont, V2(60, 60), 10.0f, RGB(1.0f, 1.0f, 1.0f), "t: %.10f", t1);
    //Print((char*)t1); 
    
   /// for (int i = 0; i < gameMapEntity->tileCount; i++)
   // {
      //  Tile* tileEntity = (Tile*)GetEntity(&Data->em, gameMapEntity->tiles[i]);
      //  vec3 position = V3(tileEntity->position.x, tileEntity->position.y, tileEntity->position.z - 10.0f);
    
      //  real32 distance = Distance(cameraPosition, position);


       // vec3 pRay = PointAt(rayMouse, distance);

        // real32* t = {};

      //  Plane p = MakePlane(pRay, Game->cameraRotation);

      //  bool rayPlaneBool = RaycastPlane(p, rayMouse, t);
      //  DrawTextScreenPixel(&Game->monoFont, V2(60, 60), 10.0f, RGB(1.0f, 1.0f, 1.0f), "t: %.10f", &t);
       // if (rayPlaneBool)
       // {

       // }

        //if (pRay.x > tileEntity->position.x && pRay.x < tileEntity->position.x + 1 && pRay.y > tileEntity->position.z)
        //{
        //     Plane p = MakePlane(pRay, Game->cameraRotation - tileEntity->rotation);

        //     bool rayPlaneBool = RaycastPlane(p, rayMouse, t);
        //     //real32 t_ = t;
        //        if (rayPlaneBool)
        //        {
        //            tileEntity->mouseOver = true;
        //         }
        //        else {
        //            tileEntity->mouseOver = false;
        //        }
        //     
        //}
        //else
        //{
        //    tileEntity->mouseOver = false;  
        //}

        // Plane p = MakePlane(pRay, IdentityQuaternion());

        // bool rayPlaneBool = RaycastPlane(p, rayMouse);
        // if (rayPlaneBool)
        // {
            // tileEntity->mouseOver = true;
        // }
        // else 
        // {
            // tileEntity->mouseOver = false;  
        // }
   // }

    

   // mouseEntity->position = pRay;
    /*if (rayPlaneBool)
    {
        vec3 test = V3(0);

    }*/

  //  mousePos.x = mousePos.x * cam->width;
    




   // mousePos.y = mousePos.y * cam->height;
    // vec3 pos = V3(mousePos.x, -5, -mousePos.y);
    // mouseEntity->position = -pos;

    // if (InputHeld(Keyboard, Input_UpArrow))
    // {
        // mouseEntity->position.z += (1.0f * Game->deltaTime);
    // }
    // if (InputHeld(Keyboard, Input_DownArrow))
    // {
        // mouseEntity->position.z -= (-1.0f * Game->deltaTime);
    // }
    // if (InputHeld(Keyboard, Input_LeftArrow))
    // {
        // mouseEntity->position.x -= (1.0f * Game->deltaTime);
    // }
    // if (InputHeld(Keyboard, Input_RightArrow))
    // {
        // mouseEntity->position.x += (-1.0f * Game->deltaTime);
    // }
}

void MouseRender()
{
    EntityTypeBuffer* mouseBuffer = &Data->em.buffers[Mouse_Type];
    MouseEntity* mouseEntitiesInBuffer = (MouseEntity*)mouseBuffer->entities;


    MouseEntity* mouseEntity = &mouseEntitiesInBuffer[0];
    //vec3 position = V3(0.0f , 10.0f, 0.0f + change_z );
    //quaternion quat = IdentityQuaternion();

    
    RenderOBJModel(&Game->modelMesh, mouseEntity->position, V3(1.0f, 1.0f, 1.0f), V4(0), IdentityQuaternion(), &Data->sprites.tile3);
}