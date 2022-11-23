



real32 TwoPointSlope(vec3 pointA, vec3 pointB)
{
	real32 y_dif = (pointB.y - pointA.y);
	real32 x_dif = (pointB.x - pointA.x);

	real32 slope = y_dif / x_dif;

	return slope;
}

real32 PerpendicularSlope(real32 slope)
{
	real32 perpSlope = 1 / slope;
	return perpSlope;
}

vec3 MidPointTwoPoints(vec3 pointA, vec3 pointB)
{
	vec3 midpoint;
	midpoint.x = (pointA.x + pointB.x) / 2;
	midpoint.y = (pointA.y + pointB.y) / 2;
	midpoint.z = pointA.z;
	return midpoint;
}


//pointList.pointCapacity = 100;
//pointList->points = (vec3*)malloc(sizeof(vec3) * pointList->pointCapacity);
//memset(pointList->points, 0, sizeof(vec3)* pointList->pointCapacity);

//model->faces = (OBJFaceArray*)malloc(sizeof(OBJFaceArray) * 5000);
//memset(model->faces, 0, sizeof(OBJFaceArray) * 5000);

// step 1 - get a bunch of points
vec3 pointA = V3(1, 1, -1);
vec3 pointB = V3(9, 4, -1);
// step 2 - take a single point and find the closest other point
	// step 2.1 - calculate distance between two points;
real32 distanceBetweenPoints = Distance(pointA, pointB);
// step 3 - find the slope bewteen two points
real32 slopeOfTwoPoints = TwoPointSlope(pointA, pointB);
// step 4 - find perpecdicular slope of this line
real32 perpSlope = PerpendicularSlope(slopeOfTwoPoints);

// step 4 - find midpoint between these two points
vec3 midpoint = MidPointTwoPoints(pointA, pointB);

// step 5 - calculate the line formula 

Rect cityRect;

cityRect.min = V2(-4, -4);
cityRect.max = V2(4, 4);

VoronoiLine vLine1;

vLine1.calcMidpoint = midpoint;
vLine1.slopeOfLine = slopeOfTwoPoints;