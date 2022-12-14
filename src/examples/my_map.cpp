

MemoryArena tokenArena = {};

#include "structs.cpp"

MyData* Data = {};

#include "renderCode.cpp"
#include "cameraController.cpp"
#include "InputLogicRender.cpp"
#include "geoTools.cpp"
#include "EntityManager.cpp"
#include "LoadSprites.cpp"
#include "BuildingLogicRender.cpp"
#include "UIEventLogicRender.cpp"
#include "PersonsLogicRender.cpp"


#include "ParseOBJ.cpp"
#include "MeshModelManager.cpp"

#include "Voronoi.cpp"
#include "city.cpp"
#include "MouseLogicRender.cpp"
#include "KeyboardLogicRender.cpp"
#include "CityStateLogic.cpp"
#include "TimerManager.cpp"

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
    Game->cameraPosition = V3(0, 0, -10);
    Game->cameraRotation = IdentityQuaternion();
    //// gameMem->cameraRotation = AxisAngle(V3(0, 1, 0), gameMem->camAngle);

    mat4 camWorld = TRS(Game->cameraPosition, Game->cameraRotation, V3(0));
    cam->view = OrthogonalInverse(camWorld);

    cam->viewProjection = cam->projection * cam->view;

    InitializeEntityManager();
    InitializeEntityBuffers();

    MeshModelInit();

    CityMapEntitiesInit();    
    CityMapTileInit(V2(10, 10), V2(1, 1));

    SetCameraToMapPositionInit();

    MouseEntityInit();
    TileArrowEntityInit();
}

void MyGameUpdate(GameMemory* gameMem)
{

    vec2 mousePos = Input->mousePosNormSigned;
    vec3 pos = V3(mousePos.x, mousePos.y, -1.0f);
    vec3 scale = V3(1.0f, 1.0f, 1.0f);
    real32 angle = 0;
    vec4 color = V4(1.0f, 0.1f, 1.0f, 1.0f);

    pos = V3(-10, -3, 1);

    
    // *********************
    // *********************
    //      lOGIC
    // *********************
    // *********************
    GameTimerAdvance();
    
    //      ***HANDLE USER INPUT***
    InputLogic(); // camera control || gameplay control
    

    //      ***EXECUTE GAME LOGIC***   
    // TODO1 - ENSURE THIS IS IN PROPER EXECUTION ORDER
    CityMapLogic();
    TileArrowLogic();
	CityStateLogic();
	PersonsLogic();
    
    // *********************
    // *********************
    //      RENDER
    // *********************
    // *********************
    
    CityMapRender();
    TileArrowRender();	
    CityStateRender();
    UIEventRender();
}
