

// DONE: Get a Line to render
// Doneish: Create a street grid
// TODO: Create a Controller to move around scene (cam)
MemoryArena nodeArena = {};
MemoryArena tokenArena = {};

// TODO: Import and Render single XML file OSM

#include "structs.cpp"
#include "renderCode.cpp"
#include "cameraController.cpp"
#include "geoTools.cpp"

#include <math.h>





MyData* Data = {};

void MyInit()
{



    AllocateMemoryArena(&nodeArena, Megabytes(20));
    AllocateMemoryArena(&tokenArena, Megabytes(20));

    Game->myData = malloc(sizeof(MyData));
    memset(Game->myData, 0, sizeof(MyData));

    Data = (MyData*)Game->myData;


    Camera* cam = &Game->camera;
    cam->type = CameraType_Orthographic;


}



void MyGameUpdate()
{
    // Step 1
    //DrawLine(V2(0.3f, 0.3f), V2(1.0f, 1.0f), 1, V4(1.0f, 0.4f, 0.4f, 1.0f));
    // Step 2
    vec2 dim = V2(8.0f, 8.0f);
    vec2 start = V2(-4.0f, -4.0f);
    vec2 gap = V2(1.0f, 0.4f);
    real32 laneWidth = 0.01f;
    vec4 color = V4(1.0f, 0.4f, 0.4f, 1.0f);
    //RenderRoadwayGrid(start, dim, gap, laneWidth, color);

    // Step 3
    MoveCamera();

    // step 4
    //<node id="152193676" visible="true" version="4" changeset="75795977" timestamp="2019-10-16T17:46:04Z" user="rivermont" uid="4085780" lat="29.7545188" lon="-95.3813103"/>

    Bound bound1 = {};
    bound1.minlon = -95.3790000f;
    bound1.maxlon = -95.3815000f;
    bound1.maxlat = 29.7565000f;
    bound1.minlat = 29.7545000f;


    BBox bbox = {};

    setBBox(&bbox, bound1);
    // BBoxLatLonToMeter(bound1);
    BBoxLatLonToMeter(&bbox);
    BBoxCalculateSizeInMeters(&bbox);

/*
<node id="152263425" visible="true" version="5" changeset="52662183" timestamp="2017-10-05T17:57:47Z" user="afdreher" uid="1110270" lat="29.7563899" lon="-95.3840460"/>
  <node id="152153163" visible="true" version="4" changeset="75795977" timestamp="2019-10-16T17:46:04Z" user="rivermont" uid="4085780" lat="29.7563968" lon="-95.3831314"/>
 <node id="8152766969" visible="true" version="1" changeset="94605097" timestamp="2020-11-23T01:58:17Z" user="rkkomat1" uid="11676217" lat="29.7563997" lon="-95.3827948"/>
<node id="4571246303" visible="true" version="1" changeset="44656049" timestamp="2016-12-25T05:27:17Z" user="clay_c" uid="119881" lat="29.7564013" lon="-95.3826002"/>
 
<node id="6886703707" visible="true" version="1" changeset="75795977" timestamp="2019-10-16T17:46:04Z" user="rivermont" uid="4085780" lat="29.7564052" lon="-95.3822864">
 <node id="152263420" visible="true" version="5" changeset="75795977" timestamp="2019-10-16T17:46:04Z" user="rivermont" uid="4085780" lat="29.7564072" lon="-95.3822369"/>
 <node id="4571246307" visible="true" version="2" changeset="75795977" timestamp="2019-10-16T17:46:04Z" user="rivermont" uid="4085780" lat="29.7564096" lon="-95.3816566"/>
  <node id="6886703711" visible="true" version="1" changeset="75795977" timestamp="2019-10-16T17:46:04Z" user="rivermont" uid="4085780" lat="29.7564097" lon="-95.3813977">
<node id="152193660" visible="true" version="5" changeset="75795977" timestamp="2019-10-16T17:46:04Z" user="rivermont" uid="4085780" lat="29.7564098" lon="-95.3813404"/>
 

  <nd ref="152263425"/>       270" lat="29.7563899" lon="-95.3840460"/> 
  <nd ref="152153163"/>       085780" lat="29.7563968" lon="-95.3831314"/> 
  <nd ref="8152766969"/>      676217" lat="29.7563997" lon="-95.3827948"/> 
  <nd ref="4571246303"/>      1" lat="29.7564013" lon="-95.3826002"/> 
  <nd ref="6886703707"/>      85780" lat="29.7564052" lon="-95.3822864"> 
  <nd ref="152263420"/>       85780" lat="29.7564072" lon="-95.3822369"/>     
  <nd ref="4571246307"/>      085780" lat="29.7564096" lon="-95.3816566"/> 
  <nd ref="6886703711"/>      4085780" lat="29.7564097" lon="-95.3813977"> 
  <nd ref="152193660"/>       5780" lat="29.7564098" lon="-95.3813404"/>     
    */
    vec2 latLonCord = V2(29.7563899f, -95.3840460f);
    vec2 latLonCord1 = V2(29.7563968f, -95.3831314f);
    vec2 latLonCord2 = V2(29.7563997f, -95.3827948f);
    vec2 latLonCord3 = V2(29.7564013f,-95.3826002f);
    vec2 latLonCord4 = V2(29.7564052f,-95.3822864f);
    vec2 latLonCord5 = V2(29.7564072f,-95.3822369f);
    vec2 latLonCord6 = V2(29.7564096f,-95.3816566f);

    vec2 latLonCord7 = V2(29.7564097f ,-95.3816566f);
    vec2 latLonCord8 = V2(29.7564098f, -95.3813404f);
    

    vec2 meterCord  = convertLatLonToMeters(latLonCord.x, latLonCord.y);
    vec2 meterCord1 = convertLatLonToMeters(latLonCord1.x, latLonCord1.y);
    vec2 meterCord2 = convertLatLonToMeters(latLonCord2.x, latLonCord2.y);
    vec2 meterCord3 = convertLatLonToMeters(latLonCord3.x, latLonCord3.y);
    vec2 meterCord4 = convertLatLonToMeters(latLonCord4.x, latLonCord4.y);
    vec2 meterCord5 = convertLatLonToMeters(latLonCord5.x, latLonCord5.y);
    vec2 meterCord6 = convertLatLonToMeters(latLonCord6.x, latLonCord6.y);
    vec2 meterCord7 = convertLatLonToMeters(latLonCord7.x, latLonCord7.y);
    vec2 meterCord8 = convertLatLonToMeters(latLonCord8.x, latLonCord8.y);

   // vec2MeterCord = 

    vec2 shift = V2(bbox.meterBottom, bbox.meterLeft);

    meterCord.x  = meterCord.x - shift.x;
    meterCord.y  = meterCord.y - shift.y;
    meterCord1.x = meterCord1.x - shift.x;
    meterCord1.y = meterCord1.y - shift.y;
    meterCord2.x = meterCord2.x - shift.x;
    meterCord2.y = meterCord2.y - shift.y;
    meterCord3.x = meterCord3.x - shift.x;
    meterCord3.y = meterCord3.y - shift.y;
    meterCord4.x = meterCord4.x - shift.x;
    meterCord4.y = meterCord4.y - shift.y;
    meterCord5.x = meterCord5.x - shift.x;
    meterCord5.y = meterCord5.y - shift.y;
    meterCord6.x = meterCord6.x - shift.x;
    meterCord6.y = meterCord6.y - shift.y;
    meterCord7.x = meterCord7.x - shift.x;
    meterCord7.y = meterCord7.y - shift.y;
    meterCord8.x = meterCord8.x - shift.x;
    meterCord8.y = meterCord8.y - shift.y;





   // vec2 nodeProjectedInBBox = V2(bbox.lengthTop - meterCord.x, bbox.lengthRight - meterCord.y);
    vec2 nodeConvert = V2(meterCord.x / bbox.lengthTop, meterCord.y / bbox.lengthRight);
    vec2 nodeConvert1 = V2(meterCord1.x / bbox.lengthTop, meterCord1.y / bbox.lengthRight);
    vec2 nodeConvert2 = V2(meterCord2.x / bbox.lengthTop, meterCord2.y / bbox.lengthRight);
    vec2 nodeConvert3 = V2(meterCord3.x / bbox.lengthTop, meterCord3.y / bbox.lengthRight);
    vec2 nodeConvert4 = V2(meterCord4.x / bbox.lengthTop, meterCord4.y / bbox.lengthRight);
    vec2 nodeConvert5 = V2(meterCord5.x / bbox.lengthTop, meterCord5.y / bbox.lengthRight);
    vec2 nodeConvert6 = V2(meterCord6.x / bbox.lengthTop, meterCord6.y / bbox.lengthRight);
    vec2 nodeConvert7 = V2(meterCord7.x / bbox.lengthTop, meterCord7.y / bbox.lengthRight);
    vec2 nodeConvert8 = V2(meterCord8.x / bbox.lengthTop, meterCord8.y / bbox.lengthRight);
    vec2 baba = {};

    vec4 color1 = V4(0.0f, 0.3f, 0.0f, 1.0f);
    vec4 color2 = V4(0.2f, 0.4f, 0.0f, 1.0f);
    vec4 color3 = V4(0.3f, 0.5f, 0.0f, 1.0f);
    vec4 color4 = V4(0.4f, 0.6f, 0.0f, 1.0f);
    vec4 color5 = V4(0.5f, 0.7f, 0.0f, 1.0f);
    vec4 color6 = V4(0.6f, 0.0f, 0.0f, 1.0f);
    vec4 color7 = V4(0.7f, 0.0f, 0.0f, 1.0f);
    vec4 color8 = V4(0.8f, 0.0f, 0.0f, 1.0f);

    DrawLine(nodeConvert, nodeConvert1, laneWidth,  color1);
    DrawLine(nodeConvert1, nodeConvert2, laneWidth, color2);
    DrawLine(nodeConvert2, nodeConvert3, laneWidth, color3);
    DrawLine(nodeConvert3, nodeConvert4, laneWidth, color4);
    DrawLine(nodeConvert4, nodeConvert5, laneWidth, color5);
    DrawLine(nodeConvert5, nodeConvert6, laneWidth, color6);
    DrawLine(nodeConvert6, nodeConvert7, laneWidth, color7);
    DrawLine(nodeConvert7, nodeConvert8, laneWidth, color8);
    
    
    
   // DrawRectBottomLeft(nodeConvert, V2(1, 1), 0, color);



}