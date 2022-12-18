

enum EntityType
{
	OSMType_Way,
	OSMType_Relation,
	OSMType_Node,
	OSMType_Bound,

	VoronoiType_Line,
	VoronoiType_Node,
	VoronoiType_District,
	VoronoiType_Map,
	VoronoiType_Intersection,

	GameMap_Type,
	GameMap_Tile,

	Mouse_Type,
	Keyboard_Type,
	TileArrow_Type,

	Road_Type,
	Building_Type,
	Person_Type,

	EntryPort_Type,


	UIEvent_Type,

	EntityType_Count,
};


struct OBJVertex
{
	int32 vVertexCount;

	vec3* vectorArray;
};

struct OBJvNormals
{
	int32 vNormalsCount;

	vec3* vNormalsArray;
};

struct OBJvTexture
{
	int32 vTextureCount;

	vec2* vTextureArray;
};

struct OBJFaceVec
{
	int32 facVecCount;

	vec3* faceValue;

};


struct OBJFaceArray
{
	int32 faceArrayCount;

	vec3 face1;
	vec3 face2;
	vec3 face3;
	vec3 face4;
};

struct OBJModel
{
	int32 vectorsCount;
	vec3* vectors;
	int32 normalsCount;
	vec3* normals;
	int32 textureCoordsCount;
	vec2* textureCoords;
	int32 facesCount;
	OBJFaceArray* faces;

	int32 indexCount;

	int32 pathNumber;
};

struct EntityHandle {
	int32 generation;
	int32 indexInInfo;
	EntityType type;
};


struct EntityInfo {
	int32 generation;
	int32 indexInBuffer;

	EntityType type;
};

struct EntityTypeBuffer {
	int32 count;
	int32 capacity;
	int32 sizeInBytes;

	void* entities;
};


struct EntityManager {
	EntityTypeBuffer buffers[EntityType_Count];
	EntityInfo* entities;
	int32 entityCapacity;

	int32 nextID;
};


struct MeshManager
{

	Mesh* meshes;
	int32 meshCount;
	int32 meshCapacity;

	//string dir;

};

struct EntitySprites {
	Sprite bld;

	Sprite tile3;
	Sprite tile3_mouse;
	Sprite road_uv;
	Sprite bld2;
	Sprite pop_sprite;
	Sprite ui1;
};

struct TimerManager
{
	real32 playerGenerationTimer;
	real32 annualTaxationTimer;
	real32 timer3;
};

struct MyData
{
	EntitySprites sprites;
	EntityManager em;

	int32 currentLevel;

	MeshManager meshManager;

	OBJModel model;
	OBJModel modelBld;
	OBJModel modelTest;

	TimerManager timerManager;
};


struct BBox
{
	real32 left;			// minlon
	real32 right;			// maxlon
	real32 top;				// maxlat
	real32 bottom;			// minlat

	real32 meterLeft;
	real32 meterRight;
	real32 meterTop;
	real32 meterBottom;

	//real32 lengthBottom;
	real32 lengthTop;
	//real32 lengthLeft;
	real32 lengthRight;
};



enum MeshType
{
	Tile_Mesh,
	CommercialBuilding_Mesh,
	ResidentialBuildingType1_Mesh,

	MeshType_Count,

};


// UI STRUCTS

struct UIEvent
{
	EntityHandle handle;
};

struct Points
{
	int32 pointCount;
	int32 pointCapacity;

	vec3* points;
};

struct Type_Lot
{
	vec3 position;

	vec3 lotOutline[4];
};

struct VoronoiEntity {
	EntityHandle handle;
	vec3 position;
};


enum CityGenState_Type
{
	CityGenState_Sequential,

	CityGenState_TypeCount,

};

struct MapData
{
	int32 residentialOccupancy;
	int32 residentialCapacity;
	int32 residentialBuildingPersonCapacity;
	int32 residentialDelta;
	int32 numberOfResidentalBuildingsWithVacancy;

	int32 commercialOccupancy;
	int32 commercialCapacity;
	int32 commercialBuildingPersonCapacity;
	int32 commercialDelta;
	int32 numberOfCommercialBuildingsWithVacancy;

};

enum TileType
{
	TileType_Grass,
	TileType_Land,
	TileType_Water,

	TileType_Road,
	TileType_CommercialBuilding,
	TileType_ResidentialBuilding_Type1,
	TileType_Test,

	TileType_Count,
};


struct Tile
{
	EntityHandle handle;
	EntityHandle entityOnTileHandle;

	quaternion rotation;
	real32 angle_x;
	real32 angle_z;

	vec3 position;
	vec2 size;

	int32 row;
	int32 column;

	bool mouseOver;

	MeshType meshType;

	TileType tileType;
	//int32 height;
	
	bool developed;
	
	DynamicArray<EntityHandle> previousDevelopments;
	int32 generationsDeveloped;
};

enum LandUse_Type
{
	road,
};

struct MouseEntity
{
	EntityHandle handle;

	vec3 position;

};
struct TileArrow
{
	EntityHandle handle;
	vec3 position;
	int32 row;
	int32 column;
	int32 tileIndex;
	quaternion rotation;
	EntityHandle tileHandle;
	MeshType meshType;

	bool developed;
};

struct MapEntity
{
	vec3 position;
};

struct Manager
{
	real32 currentMoney;
};

enum BuildingType
{
	BuildingType_Commercial,
	BuildingType_Residential_Type1,
};

struct Building : MapEntity
{
	EntityHandle handle;
	LandUse_Type landUseType;

	EntityHandle tileHandle;
	BuildingType buildingType;

	EntityHandle *persons;
	int32 personCount;
	int32 personCapacity;
	int32 personSizeInBytes;
};

struct Road : MapEntity
{

};


enum Race
{
	White,
	Black,
	Asian,
};

enum Income
{

};



struct Person : MapEntity
{
	EntityHandle handle;
	Race race;
	int32 age;

	Income incomeGroup;
	int32 taxBracket;

	EntityHandle employmentLocation;

	int32 residentialAssignment;
	EntityHandle residentialLocation;
};

struct EntryPort : MapEntity
{
	EntityHandle handle;
};

struct GameMap
{
	EntityHandle handle;

	vec2 size;

	CityGenState_Type cityGenState;

	MapData mapData;
	Manager gameManager;

	EntityHandle* tiles;
	int32 tileCount;
	int32 tileCapacity;
	int32 tileSizeInBytes;

	EntityHandle* buildings;
	int32 buildingCount;
	int32 buildingCapacity;
	int32 buildingSizeInBytes;

	EntityHandle* roads;
	int32 roadCount;
	int32 roadCapacity;
	int32 roadSizeInBytes;

	EntityHandle* persons;
	int32 personCount;
	int32 personCapacity;
	int32 personSizeInBytes;
};

struct VoronoiIntersection : VoronoiEntity
{

};


struct VoronoiLine : VoronoiEntity
{
	bool lineFinalized;

	vec3 distPosA;
	EntityHandle distHandleA;
	vec3 distPosB;
	EntityHandle distHandleB;

	vec3 startOfLine;
	vec3 endOfLine;

	real32 length;

	vec3 midpoint;

	int32 district1;
	int32 district2;

	vec3 slopeVector;
	vec3 perpSlopeVector;
	real32 slopeReal;
	real32 perpSlopeReal;

	bool intersectsBottomBBox;
	bool intersectsRightBBox;
	bool intersectsTopBBox;
	bool intersectsLeftBBox;

	bool undefinedVerticalSlope;
	bool undefinedVerticalPerpSlope;
	vec3 slopePointFromMidpoint;

	vec3 yIntercept;
};

struct VoronoiNode : VoronoiEntity
{
	int32 districtID;

	//vec3 position;
};


struct VoronoiMap : VoronoiEntity
{
	EntityHandle* vNodes;
	int32 vNodeCount;
	int32 vNodeCapacity;
	int32 vNodeSizeInBytes;

	EntityHandle* vLines;
	int32 vLineCount;
	int32 vLineCapacity;
	int32 vLineSizeInBytes;

	Rect mapSizeRect;
};

struct Entity
{
	EntityHandle handle;
	int32 id;
};

struct Tag : Entity
{
	// char* k;
	// char* v;
};

struct Node : Entity
{

	bool visible;
	int32 version;
	int32 uid;
	real32 lat;
	real32 lon;

	int32 renderTestID;

	DynamicArray<Tag> tagList;

};


struct Bound : Entity
{
	real32 minlon;
	real32 maxlon;
	real32 maxlat;
	real32 minlat;
};


struct Way : Entity
{
	Node* nodeEntities;
	int32 nodeCount;
	//DynamicArray<Node> nodeArrayForWay;
};

struct Relation : Entity
{

};


struct OSMXml
{
	BBox bbox;

	Way* wayList;
	Node* nodeList;
	Tag* tagList;
	Relation* relationList;
};

enum TokenTypeForLevel
{
	TokenType_LeftParen,
	TokenType_RightParen,
	TokenType_AmpSymb,
	TokenType_PoundSymb,
	TokenType_Comma,
	TokenType_LeftAngleBracket,
	TokenType_RightAngleBracket,
	TokenType_EqualSymb,
	TokenType_DoubleQuoteMark,
	TokenType_ForwardSlash,
	TokenType_Real32,
	TokenType_QuestionMark,
	TokenType_Value,

	TokenType_Integer,
	TokenType_PeriodSymb,
	TokenType_Identifier,
	TokenType_DollarSymb,
	TokenType_Count,


};

struct TokenVal
{
	TokenTypeForLevel type;
	char* start;
	int32 length;
};





