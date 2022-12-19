

MemoryArena tokenArena = {};

#include "structs.cpp"

MyData* Data = {};

#include "EntityManager.cpp"
#include "renderCode.cpp"
#include "cameraController.cpp"
#include "geoTools.cpp"
#include "LoadSprites.cpp"

#include "PersonsLogicRender.cpp"
#include "BuildingLogicRender.cpp"

#include "UIEventLogicRender.cpp"

#include "ParseOBJ.cpp"
#include "MeshModelManager.cpp"

#include "InputLogicRender.cpp"
#include "CityEntityLogicRender.cpp"
#include "ManagerLogicRender.cpp"
#include "GameplayLogic.cpp"

#include "Voronoi.cpp"
#include "MapLogicRender.cpp"
#include "MouseLogicRender.cpp"
#include "KeyboardLogicRender.cpp"
#include "TimerManager.cpp"
#include "UILogicRender.cpp"

int32 counter = 0;
vec3* positions = {};

void MyInit()
{
    AllocateMemoryArena(&tokenArena, Megabytes(90));
    Game->myData = malloc(sizeof(MyData));
    memset(Game->myData, 0, sizeof(MyData));

    Data = (MyData*)Game->myData;

    Data->meshManager.meshCapacity = MeshType_Count;
    Data->meshManager.meshes = (Mesh*)malloc(sizeof(Mesh) * Data->meshManager.meshCapacity);
    memset(Data->meshManager.meshes, 0, sizeof(Mesh) * Data->meshManager.meshCapacity);
    Data->meshManager.meshCount = 0;

    // Data->meshManager.meshes[Data->meshManager.meshCount] = testMesh;
    LoadSprites();

    Camera* cam = &Game->camera;
    cam->type = CameraType_Perspective;
    cam->projection = Perspective(1, 16.0f / 9.0f, 0.1f, 1000.0f);

    //Game->cameraPosition = V3(0, 0, -10);
    // Game->cameraRotation = IdentityQuaternion();
    //// gameMem->cameraRotation = AxisAngle(V3(0, 1, 0), gameMem->camAngle);

    mat4 camWorld = TRS(Game->cameraPosition, Game->cameraRotation, V3(1));
    cam->view = OrthogonalInverse(camWorld);

    //cam->viewProjection = cam->projection * cam->view;

    InitializeEntityManager();
    InitializeEntityBuffers();

    MeshModelInit();

    CityMapEntitiesInit();    
    CityMapTileInit(V2(10, 10), V2(1, 1));

    ManagerInit(100.0f);

    SetCameraToMapPositionInit();

    MouseEntityInit();
    TileArrowEntityInit();
}

//#include "wtypes.h"
//#include <iostream>
//using namespace std;



void MyGameUpdate(GameMemory* gameMem)
{
    EntityTypeBuffer* gameMapBuffer = &Data->em.buffers[GameMap_Type];
	GameMap* gameMapEntitiesInBuffer = (GameMap*)gameMapBuffer->entities;

	GameMap* gameMapEntity = &gameMapEntitiesInBuffer[0];
    
    vec2 mousePos = Input->mousePosNormSigned;
    vec3 pos = V3(mousePos.x, mousePos.y, -1.0f);
    vec3 scale = V3(1.0f, 1.0f, 1.0f);
    real32 angle = 0;
    vec4 color = V4(1.0f, 0.1f, 1.0f, 1.0f);

    pos = V3(-10, -3, 1);


    // @TODO set up horizontal and vertical screen size capacity Mod
   // int horizontal = 0;
   //int vertical = 0;
   //GetDesktopResolution(horizontal, vertical);
   //DrawTextScreenPixel(&Game->monoFont, V2(60,200), 10.0f, RGB(1.0f, 1.0f, 1.0f), "Horiz: %d", horizontal);

    
    
    // *********************
    // *********************
    //      lOGIC
    // *********************
    // *********************

    
    //      ***HANDLE USER INPUT***
    
    //      ***EXECUTE GAME LOGIC***   
    // TODO1 - ENSURE THIS IS IN PROPER EXECUTION ORDER
    // 1. ADVANCE GAME CLOCK
    // 2. HANDLE USER INPUT
    //      A. MOUSE/POINTER LOGIC
    //      B. LISTEN FOR USER INPUT
    //      C. EXECUTE INPUT INTO GAMEPLAY
    // 2. EXECUTE GAMEPLAY LOGIC
    //      B. ?? CALCULATE AND EXECUTE THE CONDITIONS FOR GAMEPLAY LOGIC (GENERATE PERSONS ETC.)
    //      A. CALCULATE THE NEW AND MOST CURRENT MAP CONDITIONS LOGIC 
    
    GameTimerAdvance();             // STEP 1. -- TimerManager.cpp
    InputLogic(gameMapEntity);                   // camera control || gameplay control
    MouseLogic();               // DOESN'T WORK YET

    GameplayLogic(gameMapEntity);                // STEP 3. -- EXECUTE GAMEPLAY LOGIC
    
    // *********************
    // *********************
    //      RENDER
    // *********************
    // *********************
    
    // 1. RENDER THE MAP                    - MapRender();
    // 2. RENDER THE CITY                   - CityEntityRender();    ILOvE YOU <3
    // 3. RENDER THE MOUSE/POINTER/INPUT          - 
    // 4. RENDER THE UI
    MapRender(gameMapEntity);           // MapRenderLogic.cpp
    // CityEntityRender(gameMapEntity); // CityEntityRender.cpp
    InputRender();                      // InputLogicRender.cpp
    UIRender(gameMapEntity);            // UIRender.cpp
}


    // ******
    // EXTRAS
    // ******

    //DrawTextScreenPixel(&Game->monoFont, V2(60,100), 10.0f, RGB(1.0f, 1.0f, 1.0f), "Commerical total cap: %d", commercialBuildingPersonCapacity);