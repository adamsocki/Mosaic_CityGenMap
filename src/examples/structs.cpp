




struct MyData
{

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


struct Bound
{
	real32 minlon;
	real32 maxlon;
	real32 maxlat;
	real32 minlat;
};


struct Node
{
	real32 id;
	bool visible;
	int32 version;
	int32 uid;
	real32 lat;
	real32 lon;
};

struct Tag
{
	// char* k;
	// char* v;
};


struct Way
{

};

struct Relation
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

