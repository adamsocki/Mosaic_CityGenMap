


enum OSMType
{
	OSMType_Way,
	OSMType_Relation,
	OSMType_Node,
	OSMType_Bound,

	OSMType_Count,
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

	//<DyanmicArray> <
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
};

struct EntityHandle {
	int32 generation;
	int32 indexInInfo;
	OSMType type;
};


struct EntityInfo {
	int32 generation;
	int32 indexInBuffer;
	
	OSMType type;
};

struct EntityTypeBuffer {
	int32 count;
	int32 capacity;
	int32 sizeInBytes;

	void* entities;
};


struct EntityManager {
	EntityTypeBuffer buffers[OSMType_Count];
	EntityInfo *entities;
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
};

struct MyData
{
	EntitySprites sprites;
	EntityManager em;
	int32 currentLevel;

	MeshManager meshManager;
	//eshManager meshManager;

	OBJModel model;

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


struct Points
{
	int32 pointCount;
	int32 pointCapacity;

	vec3* points;
};

struct VoronoiLine
{

	vec3 startOfLine;
	vec3 endOfLine;

	vec3 calcMidpoint;

	real32 slopeOfLine;

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


