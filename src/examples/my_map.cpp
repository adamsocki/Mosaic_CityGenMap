
// DONE: Get a Line to render
// Doneish: Create a street grid
// TODO: Create a Controller to move around scene (cam)
//MemoryArena nodeArena = {};
//MemoryArena boundArena = {};
//MemoryArena tokenArena = {};
//MemoryArena tagArena = {};
//MemoryArena wayArena = {};

MemoryArena meshArena = {};


// TODO: Import and Render single XML file OSM

#include "structs.cpp"



MyData* Data = {};


#include "renderCode.cpp"
#include "cameraController.cpp"
#include "geoTools.cpp"
#include "EntityManager.cpp"



#include <vector>
#include <string>
#include <string>
#include <math.h>
using namespace std;



//#include "OSMParse.cpp"









void MyInit()
{



   /* AllocateMemoryArena(&nodeArena, Megabytes(50));
    AllocateMemoryArena(&boundArena, Megabytes(1));
    AllocateMemoryArena(&tokenArena, Megabytes(50));
    AllocateMemoryArena(&tagArena, Megabytes(50));
    AllocateMemoryArena(&wayArena, Megabytes(50));*/
    AllocateMemoryArena(&meshArena, Megabytes(10));


    Game->myData = malloc(sizeof(MyData));
    memset(Game->myData, 0, sizeof(MyData));

    Data = (MyData*)Game->myData;


    Data->meshManager.meshCapacity = 100000;
    Data->meshManager.meshes = (Mesh*)malloc(sizeof(Mesh) * Data->meshManager.meshCapacity);
    memset(Data->meshManager.meshes, 0, sizeof(Mesh) * Data->meshManager.meshCapacity);
    Data->meshManager.meshCount = 0;

    Camera* cam = &Game->camera;
    cam->type = CameraType_Orthographic;


    //InitializeEntityManager();
    //InitializeEntityBuffers();
    //ParseOSM();

    //meshes = MakeDynamicArray<Mesh>(&meshArena, 1000);

}

int32 counter = 0;

#include "ModelRender.cpp"

void MyGameUpdate()
{
    
    DrawLine(V2(0.3f, 0.3f), V2(1.0f, 1.0f), 1, V4(1.0f, 0.4f, 0.4f, 1.0f));

}


    // Step 1
    
    // Step 2
//    vec2 dim = V2(8.0f, 8.0f);
//    vec2 start = V2(-4.0f, -4.0f);
//    vec2 gap = V2(1.0f, 0.4f);
//    real32 laneWidth = 0.01f;
//    vec4 color = V4(1.0f, 0.4f, 0.4f, 1.0f);
//    //RenderRoadwayGrid(start, dim, gap, laneWidth, color);
//
//    // Step 3
//    MoveCamera();
//
//    // step 4
//    //<node id="152193676" visible="true" version="4" changeset="75795977" timestamp="2019-10-16T17:46:04Z" user="rivermont" uid="4085780" lat="29.7545188" lon="-95.3813103"/>
//
//    /* Bound bound1 = {};
//    bound1.minlon = -95.3790000f;
//    bound1.maxlon = -95.3815000f;
//    bound1.maxlat = 29.7565000f;
//    bound1.minlat = 29.7545000f;
//
//
//    BBox bbox = {};
//
//    setBBox(&bbox, bound1);
//    // BBoxLatLonToMeter(bound1);
//    BBoxLatLonToMeter(&bbox);
//    BBoxCalculateSizeInMeters(&bbox); */
//
///*
//<node id="152263425" visible="true" version="5" changeset="52662183" timestamp="2017-10-05T17:57:47Z" user="afdreher" uid="1110270" lat="29.7563899" lon="-95.3840460"/>
//  <node id="152153163" visible="true" version="4" changeset="75795977" timestamp="2019-10-16T17:46:04Z" user="rivermont" uid="4085780" lat="29.7563968" lon="-95.3831314"/>
// <node id="8152766969" visible="true" version="1" changeset="94605097" timestamp="2020-11-23T01:58:17Z" user="rkkomat1" uid="11676217" lat="29.7563997" lon="-95.3827948"/>
//<node id="4571246303" visible="true" version="1" changeset="44656049" timestamp="2016-12-25T05:27:17Z" user="clay_c" uid="119881" lat="29.7564013" lon="-95.3826002"/>
// 
//<node id="6886703707" visible="true" version="1" changeset="75795977" timestamp="2019-10-16T17:46:04Z" user="rivermont" uid="4085780" lat="29.7564052" lon="-95.3822864">
// <node id="152263420" visible="true" version="5" changeset="75795977" timestamp="2019-10-16T17:46:04Z" user="rivermont" uid="4085780" lat="29.7564072" lon="-95.3822369"/>
// <node id="4571246307" visible="true" version="2" changeset="75795977" timestamp="2019-10-16T17:46:04Z" user="rivermont" uid="4085780" lat="29.7564096" lon="-95.3816566"/>
//  <node id="6886703711" visible="true" version="1" changeset="75795977" timestamp="2019-10-16T17:46:04Z" user="rivermont" uid="4085780" lat="29.7564097" lon="-95.3813977">
//<node id="152193660" visible="true" version="5" changeset="75795977" timestamp="2019-10-16T17:46:04Z" user="rivermont" uid="4085780" lat="29.7564098" lon="-95.3813404"/>
// 
//
//  <nd ref="152263425"/>       270" lat="29.7563899" lon="-95.3840460"/> 
//  <nd ref="152153163"/>       085780" lat="29.7563968" lon="-95.3831314"/> 
//  <nd ref="8152766969"/>      676217" lat="29.7563997" lon="-95.3827948"/> 
//  <nd ref="4571246303"/>      1" lat="29.7564013" lon="-95.3826002"/> 
//  <nd ref="6886703707"/>      85780" lat="29.7564052" lon="-95.3822864"> 
//  <nd ref="152263420"/>       85780" lat="29.7564072" lon="-95.3822369"/>     
//  <nd ref="4571246307"/>      085780" lat="29.7564096" lon="-95.3816566"/> 
//  <nd ref="6886703711"/>      4085780" lat="29.7564097" lon="-95.3813977"> 
//  <nd ref="152193660"/>       5780" lat="29.7564098" lon="-95.3813404"/>     
//    */
//   /* vec2 latLonCord = V2(29.7563899f, -95.3840460f);
//    vec2 latLonCord1 = V2(29.7563968f, -95.3831314f);
//    vec2 latLonCord2 = V2(29.7563997f, -95.3827948f);
//    vec2 latLonCord3 = V2(29.7564013f,-95.3826002f);
//    vec2 latLonCord4 = V2(29.7564052f,-95.3822864f);
//    vec2 latLonCord5 = V2(29.7564072f,-95.3822369f);
//    vec2 latLonCord6 = V2(29.7564096f,-95.3816566f);
//
//    vec2 latLonCord7 = V2(29.7564097f ,-95.3816566f);
//    vec2 latLonCord8 = V2(29.7564098f, -95.3813404f);
//    
//
//    vec2 meterCord  = convertLatLonToMeters(latLonCord.x, latLonCord.y);
//    vec2 meterCord1 = convertLatLonToMeters(latLonCord1.x, latLonCord1.y);
//    vec2 meterCord2 = convertLatLonToMeters(latLonCord2.x, latLonCord2.y);
//    vec2 meterCord3 = convertLatLonToMeters(latLonCord3.x, latLonCord3.y);
//    vec2 meterCord4 = convertLatLonToMeters(latLonCord4.x, latLonCord4.y);
//    vec2 meterCord5 = convertLatLonToMeters(latLonCord5.x, latLonCord5.y);
//    vec2 meterCord6 = convertLatLonToMeters(latLonCord6.x, latLonCord6.y);
//    vec2 meterCord7 = convertLatLonToMeters(latLonCord7.x, latLonCord7.y);
//    vec2 meterCord8 = convertLatLonToMeters(latLonCord8.x, latLonCord8.y);
//
//   // vec2MeterCord = 
//
//    vec2 shift = V2(bbox.meterBottom, bbox.meterLeft);
//
//    meterCord.x  = meterCord.x - shift.x;
//    meterCord.y  = meterCord.y - shift.y;
//    meterCord1.x = meterCord1.x - shift.x;
//    meterCord1.y = meterCord1.y - shift.y;
//    meterCord2.x = meterCord2.x - shift.x;
//    meterCord2.y = meterCord2.y - shift.y;
//    meterCord3.x = meterCord3.x - shift.x;
//    meterCord3.y = meterCord3.y - shift.y;
//    meterCord4.x = meterCord4.x - shift.x;
//    meterCord4.y = meterCord4.y - shift.y;
//    meterCord5.x = meterCord5.x - shift.x;
//    meterCord5.y = meterCord5.y - shift.y;
//    meterCord6.x = meterCord6.x - shift.x;
//    meterCord6.y = meterCord6.y - shift.y;
//    meterCord7.x = meterCord7.x - shift.x;
//    meterCord7.y = meterCord7.y - shift.y;
//    meterCord8.x = meterCord8.x - shift.x;
//    meterCord8.y = meterCord8.y - shift.y;
//
//
//
//
//
//   // vec2 nodeProjectedInBBox = V2(bbox.lengthTop - meterCord.x, bbox.lengthRight - meterCord.y);
//    vec2 nodeConvert = V2(meterCord.x / bbox.lengthTop, meterCord.y / bbox.lengthRight);
//    vec2 nodeConvert1 = V2(meterCord1.x / bbox.lengthTop, meterCord1.y / bbox.lengthRight);
//    vec2 nodeConvert2 = V2(meterCord2.x / bbox.lengthTop, meterCord2.y / bbox.lengthRight);
//    vec2 nodeConvert3 = V2(meterCord3.x / bbox.lengthTop, meterCord3.y / bbox.lengthRight);
//    vec2 nodeConvert4 = V2(meterCord4.x / bbox.lengthTop, meterCord4.y / bbox.lengthRight);
//    vec2 nodeConvert5 = V2(meterCord5.x / bbox.lengthTop, meterCord5.y / bbox.lengthRight);
//    vec2 nodeConvert6 = V2(meterCord6.x / bbox.lengthTop, meterCord6.y / bbox.lengthRight);
//    vec2 nodeConvert7 = V2(meterCord7.x / bbox.lengthTop, meterCord7.y / bbox.lengthRight);
//    vec2 nodeConvert8 = V2(meterCord8.x / bbox.lengthTop, meterCord8.y / bbox.lengthRight);
//    vec2 baba = {};
//
//    vec4 color1 = V4(0.0f, 0.3f, 0.0f, 1.0f);
//    vec4 color2 = V4(0.2f, 0.4f, 0.0f, 1.0f);
//    vec4 color3 = V4(0.3f, 0.5f, 0.0f, 1.0f);
//    vec4 color4 = V4(0.4f, 0.6f, 0.0f, 1.0f);
//    vec4 color5 = V4(0.5f, 0.7f, 0.0f, 1.0f);
//    vec4 color6 = V4(0.6f, 0.0f, 0.0f, 1.0f);
//    vec4 color7 = V4(0.7f, 0.0f, 0.0f, 1.0f);
//    vec4 color8 = V4(0.8f, 0.0f, 0.0f, 1.0f);
//
//    DrawLine(nodeConvert, nodeConvert1, laneWidth,  color1);
//    DrawLine(nodeConvert1, nodeConvert2, laneWidth, color2);
//    DrawLine(nodeConvert2, nodeConvert3, laneWidth, color3);
//    DrawLine(nodeConvert3, nodeConvert4, laneWidth, color4);
//    DrawLine(nodeConvert4, nodeConvert5, laneWidth, color5);
//    DrawLine(nodeConvert5, nodeConvert6, laneWidth, color6);
//    DrawLine(nodeConvert6, nodeConvert7, laneWidth, color7);
//    DrawLine(nodeConvert7, nodeConvert8, laneWidth, color8);
//    */
//    
//    
//   // DrawRectBottomLeft(nodeConvert, V2(1, 1), 0, color);
//
//    // step 5
//    //ParseOSM();
//
//    // step 6
//    // Call and Render Nodes
//    //        BUFFER
//    EntityTypeBuffer* nodeBuffer  = &Data->em.buffers[OSMType_Node];
//    EntityTypeBuffer* boundBuffer = &Data->em.buffers[OSMType_Bound];
//    EntityTypeBuffer* wayBuffer = &Data->em.buffers[OSMType_Way];
//    //        ENTITIES
//    Node* nodeEntitiesInBuffer   = (Node*)nodeBuffer->entities;
//    Bound* boundEntitiesInBuffer = (Bound*)boundBuffer->entities;
//    Way* wayEntitiesInBuffer = (Way*)wayBuffer->entities;
//
//
//
//    Bound bound1 = {};
//
//    for (int i = 0; i < boundBuffer->count; i++)
//    {
//        Bound* boundEntity = (Bound*)GetEntity(&Data->em, boundEntitiesInBuffer[i].handle);
//
//        bound1.minlon = boundEntity->minlon;
//        bound1.maxlon = boundEntity->maxlon;
//        bound1.maxlat = boundEntity->maxlat;
//        bound1.minlat = boundEntity->minlat;
//    }
//
//
//    BBox bbox = {};
//
//    setBBox(&bbox, bound1);
//    // BBoxLatLonToMeter(bound1);
//    BBoxLatLonToMeter(&bbox);
//    BBoxCalculateSizeInMeters(&bbox);
//
//    vec2 shift = V2(bbox.meterBottom, bbox.meterLeft);
//
//    
//
//    struct NodeTest
//    {
//        vec2 loc;
//        int32 renderTestID;
//    };
//
//    NodeTest node[3000] = {};
//    NodeTest nodeDisplay[20] = {};
//
//    //for(int i = 0; i < nodeBuffer->count; i++)
//    //{
//    //    
//    //    Node* nodeEntity = (Node*)GetEntity(&Data->em, nodeEntitiesInBuffer[i].handle);
//    //    vec2 latLon = V2(nodeEntity->lat, nodeEntity->lon);
//    //    vec2 meterNode = convertLatLonToMeters(latLon.x, latLon.y);
//
//    //    vec2 shiftNode = V2(meterNode.x - shift.x, meterNode.y - shift.y);
//    //    node[i].loc = V2(shiftNode.x / bbox.lengthTop, shiftNode.y / bbox.lengthRight);
//
//
//    //    //switch (nodeEntity->id) 
//    //    //{
//
//    //    //    case 152328806:
//    //    //    {
//    //    //        nodeDisplay[0].loc = node[i].loc;
//    //    //        break;
//    //    //    }
//    //    //    case 152328809:
//    //    //    {
//    //    //        nodeDisplay[1].loc = node[i].loc;
//    //    //        break;
//    //    //    }
//    //    //    case 152328811:
//    //    //    {
//    //    //        nodeDisplay[2].loc = node[i].loc;
//    //    //        break;
//    //    //    }
//    //    //    case 152328813:
//    //    //    {
//    //    //        nodeDisplay[3].loc = node[i].loc;
//    //    //        break;
//    //    //    }
//    //    //    case 4571250516:
//    //    //    {
//    //    //        nodeDisplay[4].loc = node[i].loc;
//    //    //        break;
//    //    //    }
//    //    //    case 152328816:
//    //    //    {
//    //    //        nodeDisplay[5].loc = node[i].loc;
//    //    //        break;
//    //    //    }
//    //    //    case 152328819:
//    //    //    {
//    //    //        nodeDisplay[6].loc = node[i].loc;
//    //    //        break;
//    //    //    }
//    //    //    case 152328822:
//    //    //    {
//    //    //        nodeDisplay[7].loc = node[i].loc;
//    //    //        break;
//    //    //    }
//    //    //    case 152328825:
//    //    //    {
//    //    //        nodeDisplay[8].loc = node[i].loc;
//    //    //        break;
//    //    //    }
//    //    //    case 152328828:
//    //    //    {
//    //    //        nodeDisplay[9].loc = node[i].loc;
//    //    //        break;
//    //    //    }
//    //    //    case 4571250515:
//    //    //    {
//    //    //        nodeDisplay[10].loc = node[i].loc;
//    //    //        break;
//    //    //    }
//    //    //    case 4571250521:
//    //    //    {
//    //    //        nodeDisplay[11].loc = node[i].loc;
//    //    //        break;
//    //    //    }
//    //    //    case 4571250514:
//    //    //    {
//    //    //        nodeDisplay[12].loc = node[i].loc;
//    //    //        break;
//    //    //    }
//    //    //    case 152328831:
//    //    //    {
//    //    //        nodeDisplay[13].loc = node[i].loc;
//    //    //        break;
//    //    //    }
//    //    //    default:
//    //    //    {
//    //    //        //nodeDisplay[].loc = node[i];
//    //    //        break;
//    //    //    }
//
//    //    //}
//    //    
//
//    //}
//
//    vec4 color1 = V4(0.0f, 0.3f, 0.0f, 1.0f);
//    vec4 color2 = V4(0.2f, 0.4f, 0.0f, 1.0f);
//    vec4 color3 = V4(0.3f, 0.5f, 0.0f, 1.0f);
//    vec4 color4 = V4(0.4f, 0.6f, 0.0f, 1.0f);
//    vec4 color5 = V4(0.5f, 0.7f, 0.0f, 1.0f);
//    vec4 color6 = V4(0.6f, 0.0f, 0.0f, 1.0f);
//    vec4 color7 = V4(0.7f, 0.0f, 0.0f, 1.0f);
//    vec4 color8 = V4(0.8f, 0.0f, 0.0f, 1.0f);
//
//    vec2 nodeToDrawA[30] = {};
//    vec2 nodeToDrawB[30] = {};
//    //countA = 0;
//    //countB = 0;
//
//    if (InputPressed(Keyboard, Input_RightArrow))
//    {
//        counter += 5;
//    }
//    if (InputPressed(Keyboard, Input_LeftArrow))
//    {
//        counter--;
//    }
//    for (int i = 0; i < counter; i++)
//    {
//        Way* wayEntity = (Way*)GetEntity(&Data->em, wayEntitiesInBuffer[i].handle);
//
//
//
//
//        for (int j = 0; j < wayEntity->nodeCount; j++)
//        {
//            vec2 lineA = {};
//            vec2 lineB = {};
//
//            for (int k = 0; k < nodeBuffer->count; k++)
//            {
//                Node* nodeEntity = (Node*)GetEntity(&Data->em, nodeEntitiesInBuffer[k].handle);
//                
//                if (nodeEntity->id == wayEntity->nodeEntities[j].id)
//                {
//                    vec2 latLon = V2(nodeEntity->lat, nodeEntity->lon);
//                    vec2 meterNode = convertLatLonToMeters(latLon.x, latLon.y);
//                    vec2 shiftNode = V2(meterNode.x - shift.x, meterNode.y - shift.y);
//                    lineA = V2(shiftNode.x / bbox.lengthTop, shiftNode.y / bbox.lengthRight);
//                    //countA++;
//                    for (int l = 0; l < nodeBuffer->count; l++)
//                    {
//                        Node* nodeEntity2 = (Node*)GetEntity(&Data->em, nodeEntitiesInBuffer[l].handle);
//
//                        if (nodeEntity2->id == wayEntity->nodeEntities[j + 1].id)
//                        {
//                            vec2 latLon2 = V2(nodeEntity2->lat, nodeEntity2->lon);
//                            vec2 meterNode2 = convertLatLonToMeters(latLon2.x, latLon2.y);
//                            vec2 shiftNode2 = V2(meterNode2.x - shift.x, meterNode2.y - shift.y);
//                            lineB = V2(shiftNode2.x / bbox.lengthTop, shiftNode2.y / bbox.lengthRight);
//
//                            DrawLine(lineA, lineB, laneWidth, color1);
//                        }
//                    }
//
//
//
//
//                }
//                
//            }
//
//            //DrawLine(nodeDisplay[i].loc, nodeDisplay[i + 1].loc, laneWidth, color1);
//        }
//
//    }
//      /*<nd ref="node[i].id == 152328806  ||"/>
//        <nd ref="node[i].id == 152328809  ||"/>
//        <nd ref="node[i].id == 152328811  ||"/>
//        <nd ref="node[i].id == 152328813  ||"/>
//        <nd ref="node[i].id == 4571250516 ||"/>
//        <nd ref="node[i].id == 152328816  ||"/>
//        <nd ref="node[i].id == 152328819  ||"/>
//        <nd ref="node[i].id == 152328822  ||"/>
//        <nd ref="node[i].id == 152328825  ||"/>
//        <nd ref="node[i].id == 152328828  ||"/>
//        <nd ref="node[i].id == 4571250515 ||"/>
//        <nd ref="node[i].id == 4571250521 ||"/>
//        <nd ref="node[i].id == 4571250514 ||"/>
//        <nd ref="node[i].id == 152328831  ||"/>*/
//
//    
//
//    for (int i = 0; i < 30; i ++)
//    {
//    }
//
//     //DrawLine(node[0], node[5], laneWidth, color1);
//     //DrawLine(node[3], node[10], laneWidth, color1);
//
//
//    for (int i = 0; i < 15; i++)
//    {
//       // DrawLine(nodeDisplay[i].loc, nodeDisplay[i + 1].loc, laneWidth, color1);
//    }
//
//
//    //DrawTextScreenPixel(&Game->monoFont, V2(530, 20), 10.0f, RGB(1.0f, 1.0f, 1.0f), "X: %.10f", node[3].x);
////    DrawTextScreenPixel(&Game->monoFont, V2(530, 60), 10.0f, RGB(1.0f, 1.0f, 1.0f), "X: %.10f", node[3].y);

//}