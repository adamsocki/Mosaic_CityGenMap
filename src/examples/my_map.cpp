

MemoryArena tokenArena = {};

#include "structs.cpp"

MyData* Data = {};

#include "renderCode.cpp"
#include "cameraController.cpp"
#include "geoTools.cpp"
#include "EntityManager.cpp"
#include "LoadSprites.cpp"
#include "BuildingLogicRender.cpp"
#include "UIEventLogicRender.cpp"

#include "ParseOBJ.cpp"
#include "Voronoi.cpp"
#include "city.cpp"
#include "camera.cpp"
#include "MouseLogicRender.cpp"
#include "KeyboardLogicRender.cpp"
#include "CityStateLogic.cpp"
#include "TimerManager.cpp"

int32 counter = 0;

void MyInit()
{

    AllocateMemoryArena(&tokenArena, Megabytes(90));
    Game->myData = malloc(sizeof(MyData));
    memset(Game->myData, 0, sizeof(MyData));

    Data = (MyData*)Game->myData;

    Data->meshManager.meshCapacity = 1000;
    Data->meshManager.meshes = (Mesh*)malloc(sizeof(Mesh) * Data->meshManager.meshCapacity);
    memset(Data->meshManager.meshes, 0, sizeof(Mesh) * Data->meshManager.meshCapacity);
    Data->meshManager.meshCount = 0;

    LoadSprites();

    Camera* cam = &Game->camera;
    cam->type = CameraType_Perspective;
    cam->projection = Perspective(1, 16.0f / 9.0f, 0.1f, 1000.0f);
    Game->cameraPosition = V3(0, 0, -10);
    Game->cameraRotation = IdentityQuaternion();
    //// gameMem->cameraRotation = AxisAngle(V3(0, 1, 0), gameMem->camAngle);

    mat4 camWorld = TRS(Game->cameraPosition, Game->cameraRotation, V3(0));
    cam->view = OrthogonalInverse(camWorld);

    cam->viewProjection = cam->projection * cam->view;

    InitializeEntityManager();
    InitializeEntityBuffers();
    //ParseOSM();

    Data->model.pathNumber = 0;
    LoadModelParse(&Data->model);

    Data->modelBld.pathNumber = 2;
    LoadModelParse(&Data->modelBld);
    
    Data->modelTest.pathNumber = 3;
    LoadModelParse(&Data->modelTest);

    InitializeVoronoiMap();
    VoronoiTest2();

    CityMapInit();
    
    CityMapTileInit(V2(10, 10), V2(1, 1));

    TimerInit();
    SetCameraToMap();
    MouseInit();
    TileArrowInit();

    AllocateModelOBJMesh(&Game->modelMesh, &Data->model);
    InitMesh(&Game->modelMesh);

    AllocateModelOBJMesh(&Game->bldMesh, &Data->modelBld);
    InitMesh(&Game->bldMesh);

    AllocateModelOBJMesh(&Game->testMesh, &Data->modelTest);
    InitMesh(&Game->testMesh);
}

void MyGameUpdate()
{
    TimerAdvance();
    vec2 mousePos = Input->mousePosNormSigned;

    vec3 pos = V3(mousePos.x, mousePos.y, -1.0f);
    vec3 scale = V3(1.0f, 1.0f, 1.0f);
    real32 angle = 0;
    vec4 color = V4(1.0f, 0.1f, 1.0f, 1.0f);

    pos = V3(-10, -3, 1);


    DrawSprite(V2(0), V2(1, 1), &Data->sprites.bld);

    Camera* cam = &Game->camera;
    int32 cameraSpeed = 8;
   /* if (InputHeld(Keyboard, Input_Q))
    {
        Game->cameraPosition.y += cameraSpeed * Game->deltaTime;
    }
    if (InputHeld(Keyboard, Input_E))
    {
        Game->cameraPosition.y -= cameraSpeed * Game->deltaTime;
    }
    if (InputHeld(Keyboard, Input_Z))
    {
        Game->cameraPosition.x += cameraSpeed * Game->deltaTime;
    }*/
   /* if (InputHeld(Keyboard, Input_C))
    {
        Game->cameraPosition.x -= cameraSpeed * Game->deltaTime;
    }*/
    if (InputHeld(Keyboard, Input_W))
    {
        Game->cameraPosition.z += cameraSpeed * Game->deltaTime;
    }
    if (InputHeld(Keyboard, Input_S))
    {
        Game->cameraPosition.z -= cameraSpeed * Game->deltaTime;
    }
    if (InputHeld(Keyboard, Input_A))
    {
        Game->cameraRotation.x += 1.5f * Game->deltaTime;
    }
    if (InputHeld(Keyboard, Input_D))
    {
        Game->cameraRotation.x -= 1.5f * Game->deltaTime;

    }
    /*if (InputHeld(Keyboard, Input_I))
    {
        Game->cameraRotation.z += 1.5f * Game->deltaTime;
    }*/
    if (InputHeld(Keyboard, Input_J))
    {
      //  Game->cameraRotation.w += 1.5f * Game->deltaTime;
    }

    CityMapLogic();
    MouseLogic();
    TileArrowLogic();
	
	CityStateLogic();
	
    CityMapRender();
    TileArrowRender();
    MouseRender();
	
    CityStateRender();

    UIEventRender();
}
