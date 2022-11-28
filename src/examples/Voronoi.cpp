
vec2 vec3ToVec2 (vec3 vec)
{
	vec2 vecOut ={};
	vecOut = V2(vec.x, vec.y);
	return vecOut;
}



vec2 IntersectionFourPoints(vec2 line1PointA, vec2 line1PointB, vec2 line2PointA, vec2 line2PointB)
{
	real32 a = line1PointB.y - line1PointA.y;
	real32 b = line1PointA.x - line1PointB.x;
	real32 c = (a * line1PointA.x) + (b * line1PointA.y);

	real32 a1 = line2PointB.y - line2PointA.y;
	real32 b1 = line2PointA.x - line2PointB.x;
	real32 c1 = (a1 * line2PointA.x) + (b1 * line2PointA.y);

	real32 det = a * b1 - a1 * b;

	if (det == 0)
	{
		// ??
	}
	else
	{
		real32 x = (b1 * c - b * c1) / det;
		real32 y = (a * c1 - a1 * c) / det;
		return V2(x, y);
	}
}
	/*Start
		//Step 1->Declare function to print the x and y coordinates
		//void display(mk_pair par)
		//Print par.first and par.second
		//Step 2->declare function to calculate the intersection point
		//mk_pair intersection(mk_pair A, mk_pair B, mk_pair C, mk_pair D)
		
		
		
		Declare double a = B.second - A.second
		Declare double b = A.first - B.first
		Declare double c = a * (A.first) + b * (A.second)
		Declare double a1 = D.second - C.second
		Declare double b1 = C.first - D.first
		Declare double c1 = a1 * (C.first) + b1 * (C.second)
		Declare double det = a * b1 - a1 * b
		IF(det = 0)
		return make_pair(FLT_MAX, FLT_MAX)
		End
		Else
		Declare double x = (b1 * c - b * c1) / det
		Declare double y = (a * c1 - a1 * c) / det
		return make_pair(x, y)
		End
		Step 3->In main()
		Declare and call function for points as mk_pair q = make_pair(2, 1)
		IF(inter.first = FLT_MAX AND inter.second = FLT_MAX)
		Print “given lines are parallel“
		End
		Else
		Call display(inter)
		End
		Stop*/


real32 TwoPointSlopeReal(vec3 pointA, vec3 pointB)
{
	real32 y_dif = (pointB.y - pointA.y);
	real32 x_dif = (pointB.x - pointA.x);

	real32 slope;

	if (x_dif != 0)
	{
		return slope = y_dif / x_dif;
	}
	else
	{
		return slope = NULL;
	}
}

vec3 TwoPointSlopeVector(vec3 pointA, vec3 pointB)
{
	vec3 slopeVector;

	slopeVector.y = (pointB.y - pointA.y);
	slopeVector.x = (pointB.x - pointA.x);

	return slopeVector;
}

real32 PerpendicularSlopeReal(real32 slopeReal)
{
	real32 perpSlopeReal =  - 1 / slopeReal;
	return perpSlopeReal;
}

vec3 PerpendicularSlopeVector(vec3 slopeVector)
{
	vec3 perpSlopeVector;

	perpSlopeVector.x = - slopeVector.y;
	perpSlopeVector.y =   slopeVector.x;

	return perpSlopeVector;
}

vec3 MidPointTwoPoints(vec3 pointA, vec3 pointB)
{
	vec3 midpoint;
	midpoint.x = (pointA.x + pointB.x) / 2;
	midpoint.y = (pointA.y + pointB.y) / 2;
	midpoint.z = pointA.z;
	return midpoint;
}
void CalcMidpointVoronoi(VoronoiLine *vLine)
{
	vLine->midpoint.x = (vLine->distPosA.x + vLine->distPosB.x) / 2;
	vLine->midpoint.y = (vLine->distPosA.y + vLine->distPosB.y) / 2;
	vLine->midpoint.z = (vLine->distPosA.z + vLine->distPosB.z) / 2;
}
void CalcSlopesVoronoi(VoronoiLine* vLine) 
{
	vLine->slopeVector.y = (vLine->distPosB.y - vLine->distPosA.y);
	vLine->slopeVector.x = (vLine->distPosB.x - vLine->distPosA.x);

	vLine->perpSlopeVector.y = -vLine->slopeVector.x;
	vLine->perpSlopeVector.x =  vLine->slopeVector.y;

	if (vLine->slopeVector.x == 0)
	{
		vLine->undefinedVerticalSlope = true;
	}
	else
	{
		vLine->slopeReal = vLine->slopeVector.y / vLine->slopeVector.x;
	}

	if (vLine->perpSlopeVector.x == 0)
	{
		vLine->undefinedVerticalPerpSlope = true;
	}
	else 
	{
		vLine->perpSlopeReal = vLine->perpSlopeVector.y / vLine->perpSlopeVector.x;
	}
}

vec3 intersection(float m1, float b1, float m2, float b2)
{
	assert((m1 - m2) != 0);				 // avoid divide by zero 
	vec3 p;
	p.x = (b2 - b1) / (m1 - m2);
	p.y = p.x * m1 + b1;
	return p;
}

bool IsWithinBBox(vec2 point, Rect bbox)
{
	bool isInside = false;
	
	if (point.x > bbox.min.x && point.x < bbox.max.x && point.y > bbox.min.y && point.y < bbox.max.y)
	{
		isInside = true;
	}
	return isInside;
}


void CalcLineFormula(VoronoiLine * vLine)
{
	// 1. calc the slopeFromMidpoint
	vLine->slopePointFromMidpoint.x = vLine->midpoint.x + vLine->slopeVector.x;
	vLine->slopePointFromMidpoint.y = vLine->midpoint.y + vLine->slopeVector.y;

	// 2. calc the y-intercept
	vLine->yIntercept.y = vLine->midpoint.y - (vLine->slopeReal * vLine->midpoint.x);
}

bool CalcStartEndWithBBox(VoronoiLine* vLine, Rect bbox)
{
	bool completed = true;

	//vline == 1
	//bbox  == 2

	real32 bottomIntersect;
	real32 topIntersect;
	real32 leftIntersect;
	real32 rightIntersect;

	// y = mx + b

	// right sied of box 
	real32 yRight = (vLine->slopeReal * bbox.max.x) + vLine->yIntercept.y;
	// left side of box
	real32 yLeft = (vLine->slopeReal * bbox.min.x) + vLine->yIntercept.y;
	// bottom
	real32 xBottom = (bbox.min.y - vLine->yIntercept.y) / vLine->slopeReal;
	// top
	real32 xTop = (bbox.max.y - vLine->yIntercept.y) / vLine->slopeReal;

	if (yRight < bbox.max.y && yRight > bbox.min.y)
	{
		vLine->startOfLine.y = yRight;
		//vLine->startOfLine.x = bbox.max.y;
		
	}
	else 
	{
		//vLine->startOfLine.y = NULL;
	}
	if (yLeft < bbox.max.y && yLeft > bbox.min.y)
	{
		vLine->endOfLine.y = yLeft;
		//vLine->endOfLine.x = bbox.min.y;
	}
	else
	{
		//vLine->endOfLine.y = NULL;
	}

	if (xBottom < bbox.max.x && xBottom > bbox.min.x)
	{
		vLine->startOfLine.x = xBottom;
		//vLine->startOfLine.y = bbox.min.x;
	}
	else
	{
		//vLine->startOfLine.x = NULL;
	}
	if (xTop < bbox.max.x && xTop > bbox.min.x)
	{
		vLine->endOfLine.x = xTop;
	}
	else
	{
		//vLine->endOfLine.x = NULL;
	}



	return completed;
}

void CaclulateSlope(VoronoiLine* vLine)
{

}


void TestVoronoi()
{
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
	real32 slopeRealOfTwoPoints = TwoPointSlopeReal(pointA, pointB);
	vec3 slopeVectorOfTwoPoint = TwoPointSlopeVector(pointA, pointB);
	// step 4 - find perpecdicular slope of this line
	real32 perpSlopeReal = PerpendicularSlopeReal(slopeRealOfTwoPoints);
	vec3 perpSlopeVector = PerpendicularSlopeVector(slopeVectorOfTwoPoint);
	// step 4 - find midpoint between these two points
	vec3 midpoint = MidPointTwoPoints(pointA, pointB);

	// step 5 - calculate the line formula 

	Rect cityRect;
	
	cityRect.min = V2(-14, -14);
	cityRect.max = V2(14, 14);

	VoronoiLine vLine1 = {};

	vLine1.midpoint = midpoint;
	//if (perpSlopeReal)
	vLine1.slopeReal = perpSlopeReal;
	vLine1.slopeVector = perpSlopeVector;

	//find perpecdicular slope of this line
	//PerpendicularSlopeReal(&vLine1);
	//PerpendicularSlopeVector(&vLine1);


	CalcLineFormula(&vLine1);

	CaclulateSlope(&vLine1);

	CalcStartEndWithBBox(&vLine1, cityRect);
	vec4 color = V4(1.0f, 0.1f, 1.0f, 1.0f);



	DrawLine( V2(vLine1.startOfLine.x, vLine1.startOfLine.y), V2(vLine1.endOfLine.x, vLine1.endOfLine.y), 0.3f, color);

	int32 value;
	value = 1;

}

void InitializeVoronoiMap()
{

	//				*******************
	//				INITIALIZE ENTITIES
	//				*******************

	// Initialize/Create Map Entity
	EntityHandle mapHandle = AddEntity(&Data->em, VoronoiType_Map);
	VoronoiMap* mapEntity = (VoronoiMap*)GetEntity(&Data->em, mapHandle);

	mapEntity->vNodeCapacity = 2000;
	mapEntity->vNodeSizeInBytes = sizeof(EntityHandle);
	mapEntity->vNodeCount = 0;
	mapEntity->vNodes = (EntityHandle*)malloc(mapEntity->vNodeCapacity * mapEntity->vNodeSizeInBytes);
	memset(mapEntity->vNodes, 0, sizeof(EntityHandle) * mapEntity->vNodeCapacity);

	mapEntity->vLineCapacity = 2000;
	mapEntity->vLineSizeInBytes = sizeof(EntityHandle);
	mapEntity->vLineCount = 0;
	mapEntity->vLines = (EntityHandle*)malloc(mapEntity->vLineCapacity * mapEntity->vLineSizeInBytes);
	memset(mapEntity->vLines, 0, sizeof(EntityHandle) * mapEntity->vLineCapacity);

	mapEntity->handle = mapHandle;
	mapEntity->position = V3(0, 0, -10);
	Rect mapSizeRect;
	mapSizeRect.min = V2(-10, -10);
	mapSizeRect.max = V2(10, 10);
	mapEntity->mapSizeRect = mapSizeRect;

	//				Initialize/Create Two Node Entities
	for (int i = 0; i < 2; i++)
	{
		EntityHandle nodeHandle = AddEntity(&Data->em, VoronoiType_Node);
		VoronoiNode* nodeEntity = (VoronoiNode*)GetEntity(&Data->em, nodeHandle);
		nodeEntity->handle = nodeHandle;
		nodeEntity->districtID = i + 1;
		nodeEntity->position = V3(4, 6 - (4 * i), -10);
	}

	//				Add node handles to map

	EntityTypeBuffer* vNodeBuffer = &Data->em.buffers[VoronoiType_Node];
	VoronoiNode* vNodeEntitiesInBuffer = (VoronoiNode*)vNodeBuffer->entities;

	for (int i = 0; i < 2; i++)
	{
		EntityHandle vNodeHandle = vNodeEntitiesInBuffer[i].handle;
		mapEntity->vNodes[mapEntity->vNodeCount] = vNodeHandle;
		mapEntity->vNodeCount++;
	}
	
}

void VoronoiTest2()
{


	//				*********************
	//				*********************
	//						LOGIC
	//				*********************
	//				*********************
	
	//				BUFFER REFERENCES
	EntityTypeBuffer* vMapBuffer  = &Data->em.buffers[VoronoiType_Map];
	EntityTypeBuffer* vNodeBuffer = &Data->em.buffers[VoronoiType_Node];
	VoronoiMap*  vMapEntitiesInBuffer  = (VoronoiMap*)vMapBuffer->entities;
	VoronoiNode* vNodeEntitiesInBuffer = (VoronoiNode*)vNodeBuffer->entities;
	
	//				GET MAP ENTITY FOR REFERENCE WITHIN FUNCTION	
	VoronoiMap* vMapEntity = (VoronoiMap*)GetEntity(&Data->em, vMapEntitiesInBuffer[0].handle);
	//				GET REFERENCE TO NODES FOR REFERENCE WITHIN FUNCTION

	real32 distanceBetweenPoints; 
	VoronoiNode* vNodes[2];
	//vec3 pointB;
	//				Get nodes 
	for (int i = 0; i < vMapEntity->vNodeCount; i++)
	{
		VoronoiNode* vNodeEntity = (VoronoiNode*)GetEntity(&Data->em, vMapEntity->vNodes[i]);
		vNodes[i] = vNodeEntity;
		//vNodes[i] = vNodeEntity;
	}

	distanceBetweenPoints = Distance(V2(vNodes[0]->position.x, vNodes[0]->position.y), V2(vNodes[1]->position.x, vNodes[1]->position.y));
	//				CREATE VORONOI LINE FOR FIRST POINTS ITERATIONS
	EntityHandle vLineHandle = AddEntity(&Data->em, VoronoiType_Line);
	VoronoiLine* vLineEntity = (VoronoiLine*)GetEntity(&Data->em, vLineHandle);
	vLineEntity->handle = vLineHandle;

	vMapEntity->vLines[vMapEntity->vLineCount] = vLineHandle;
	vMapEntity->vLineCount++;

	vLineEntity->distPosA = vNodes[0]->position;
	vLineEntity->distHandleA = vNodes[0]->handle;
	vLineEntity->distPosB = vNodes[1]->position;
	vLineEntity->distHandleB = vNodes[1]->handle;

	vLineEntity->length = distanceBetweenPoints;

	vLineEntity->district1 = vNodes[0]->districtID;
	vLineEntity->district2 = vNodes[1]->districtID;

	CalcMidpointVoronoi(vLineEntity);
	CalcSlopesVoronoi(vLineEntity);
	

	// detect edge of vLine with bbox
	// y - y1 = m(x - x1)
	if (!vLineEntity->undefinedVerticalPerpSlope)
	{
		real32 y1 = vLineEntity->midpoint.y;
		real32 x1 = vLineEntity->midpoint.x;
		real32 m = vLineEntity->perpSlopeReal;
		//rightSide
		real32 x = vMapEntity->mapSizeRect.max.x;
		real32 rightSideEquation = (m * x) - (m * x1);
		real32 yRight = rightSideEquation + y1;
		bool startOfLineCreated = false;
		if (yRight < vMapEntity->mapSizeRect.max.y && yRight > vMapEntity->mapSizeRect.min.y)
		{
			vLineEntity->intersectsRightBBox = true;
			if (!startOfLineCreated)
			{
				vLineEntity->startOfLine.x = vMapEntity->mapSizeRect.max.x;
				vLineEntity->startOfLine.y = yRight;
			}
			else
			{
				vLineEntity->endOfLine.x = vMapEntity->mapSizeRect.max.x;
				vLineEntity->endOfLine.y = yRight;
			}
			startOfLineCreated = true;
		}
		//leftSide
		x = vMapEntity->mapSizeRect.min.x;
		rightSideEquation = (m * x) - (m * x1);
		real32 yLeft = rightSideEquation + y1;
		if (yLeft < vMapEntity->mapSizeRect.max.y && yLeft > vMapEntity->mapSizeRect.min.y)
		{
			vLineEntity->intersectsLeftBBox = true;
			if (!startOfLineCreated)
			{
				vLineEntity->startOfLine.x = vMapEntity->mapSizeRect.min.x;
				vLineEntity->startOfLine.y = yLeft;
			}
			else
			{
				vLineEntity->endOfLine.x = vMapEntity->mapSizeRect.min.x;
				vLineEntity->endOfLine.y = yLeft;
			}
			startOfLineCreated = true;
		}
		//topSide
		real32 y = vMapEntity->mapSizeRect.max.y;
		real32 leftSideEquation = (y - y1);
		//(m*x)-(m*x1)
		real32 eqStep2 = leftSideEquation + (m * x1);
		real32 xTop = eqStep2 / m;
		if (xTop < vMapEntity->mapSizeRect.max.x && xTop > vMapEntity->mapSizeRect.min.x)
		{
			vLineEntity->intersectsTopBBox = true;
			if (!startOfLineCreated)
			{
				vLineEntity->startOfLine.x = xTop;
				vLineEntity->startOfLine.y = vMapEntity->mapSizeRect.max.y;
			}
			else
			{
				vLineEntity->endOfLine.x = xTop;
				vLineEntity->endOfLine.y = vMapEntity->mapSizeRect.max.y;
			}
			startOfLineCreated = true;
		}

		//bottomSide
		y = vMapEntity->mapSizeRect.min.y;
		leftSideEquation = (y - y1);
		eqStep2 = leftSideEquation + (m * x1);
		real32 xBottom = eqStep2 / m;
		if (xBottom < vMapEntity->mapSizeRect.max.x && xBottom > vMapEntity->mapSizeRect.min.x)
		{
			vLineEntity->intersectsBottomBBox = true;
			if (!startOfLineCreated)
			{
				vLineEntity->startOfLine.x = xBottom;
				vLineEntity->startOfLine.y = vMapEntity->mapSizeRect.min.y;
			}
			else
			{
				vLineEntity->endOfLine.x = xBottom;
				vLineEntity->endOfLine.y = vMapEntity->mapSizeRect.min.y;
			}
			startOfLineCreated = true;
		}

		vLineEntity->lineFinalized = true;

	}
	
}


void AddVoronoiPoint(vec2 newVPointPos)
{
	//				BUFFER REFERENCES
	EntityTypeBuffer* vMapBuffer = &Data->em.buffers[VoronoiType_Map];
	EntityTypeBuffer* vNodeBuffer = &Data->em.buffers[VoronoiType_Node];
	EntityTypeBuffer* vLineBuffer = &Data->em.buffers[VoronoiType_Line];
	VoronoiMap* vMapEntitiesInBuffer = (VoronoiMap*)vMapBuffer->entities;
	VoronoiNode* vNodeEntitiesInBuffer = (VoronoiNode*)vNodeBuffer->entities;
	VoronoiLine* vLineEntitiesInBuffer = (VoronoiLine*)vLineBuffer->entities;

	// step 1 add node to buffer
	EntityHandle vNodeHandle = AddEntity(&Data->em, VoronoiType_Node);
	VoronoiNode* vNodeEntity = (VoronoiNode*)GetEntity(&Data->em, vNodeHandle);

	vNodeEntity->handle = vNodeHandle;
	vec3 projPos = V3(newVPointPos.x, newVPointPos.y, -10);
	vNodeEntity->position = projPos;
	//vNodeEntity->id = 3;


	// step 2 add new node to map 
	VoronoiMap* vMapEntity = (VoronoiMap*)GetEntity(&Data->em, vMapEntitiesInBuffer[0].handle);
	vMapEntity->vNodes[vMapEntity->vNodeCount] = vNodeEntity->handle;
	vMapEntity->vNodeCount++;

	// step 3 create new vLine
	EntityHandle vLineHandle = AddEntity(&Data->em, VoronoiType_Line);
	VoronoiLine* vLineEntity = (VoronoiLine*)GetEntity(&Data->em, vLineHandle);
	vLineEntity->handle = vLineHandle;

	// step 3.1 add vLine to map
	vMapEntity->vLines[vMapEntity->vLineCount] = vLineEntity->handle;
	vMapEntity->vLineCount++;

	// step 4 find closest existing node to new node
	real32 closestDistance = 9999;
	VoronoiNode* nearestNode = {};
	for (int i = 0; i < vMapEntity->vNodeCount; i++)
	{
		VoronoiNode* vNodeNearestEntity = (VoronoiNode*)GetEntity(&Data->em, vMapEntity->vNodes[i]);
		if (projPos != vNodeNearestEntity->position)
		{
			real32 dist = Distance(projPos, vNodeNearestEntity->position);
			if (dist < closestDistance)
			{
				closestDistance = dist;
				nearestNode = vNodeNearestEntity;
			}
		}
		
		
	}
	// assign these nodes
	vLineEntity->distPosA = vNodeEntity->position;
	vLineEntity->distPosB = nearestNode->position;

	// step 5 calculate midpoint & new slope/perpSlope bewteen closest node and new node
	CalcMidpointVoronoi(vLineEntity);
	CalcSlopesVoronoi(vLineEntity);

	// step 5.1 make sure the line isn't undefined/Verrtical
	if (!vLineEntity->undefinedVerticalPerpSlope)
	{
		// step 6 determine if perpSlope of the new vLine is intersecting with any other existing vLines
		real32 vLineIntShortestDistance = 9999;
		VoronoiLine* closestIntersectVLineEntity;
		vec2 intersectionPointToChange;
		bool intersectionModChangeRequired = false;
		for (int i = 0; i < vMapEntity->vLineCount; i++)
		{
			VoronoiLine* vLineNearestEntity = (VoronoiLine*)GetEntity(&Data->em, vMapEntity->vLines[i]);
			/*if (vLineNearestEntity->handle != vLineEntity->handle)
			{
				
			}*/
			if (vLineNearestEntity->lineFinalized)
			{
				
				// start and end point of teseting vLine
				vec3 vLineNearestPointA  = vLineNearestEntity->startOfLine;
				vec2 vLineNearestPointA_ = vec3ToVec2(vLineNearestPointA);
				vec3 vLineNearestPointB  = vLineNearestEntity->endOfLine;
				vec2 vLineNearestPointB_ = vec3ToVec2(vLineNearestPointB);

				// start and end point of new line using midpoint and perpSlopeVector
				vec3 vLineEntityPointA   = vLineEntity->midpoint;
				vec2 vLineEntityPointA_  = vec3ToVec2(vLineEntityPointA);
				vec3 vLineEntityPointB   = vLineEntity->perpSlopeVector;
				vec2 vLineEntityPointB_  = vec3ToVec2(vLineEntityPointB);

				// location of intersecting point between test line and new line
				vec2 intersectionPoint = IntersectionFourPoints(vLineNearestPointA_,vLineNearestPointB_,vLineEntityPointA_,vLineEntityPointB_);
				// is it within the bbox
				bool isWithinBox = IsWithinBBox(intersectionPoint, vMapEntity->mapSizeRect);
				if (isWithinBox)
				{
					// is it the nearest line tested so far?
					// TODO: Potential for optimization ==> select only lines within radius
					
					// distance between vLineMidpoint and intersection
					// is ^^ this value the smallest value calculated?
					real32 distance = Distance(intersectionPoint, vec3ToVec2(vLineEntity->midpoint));
					if (vLineIntShortestDistance > distance)
					{
						vLineIntShortestDistance = distance;
						closestIntersectVLineEntity = vLineNearestEntity;
						intersectionPointToChange = intersectionPoint;
						intersectionModChangeRequired = true;
						
						
					}
				}
				else
				{
					
				}
			}
			
		}
		bool startOfLineCreated = false;
		bool endOfLineCreated = false;
		if (intersectionModChangeRequired)
		{
			vLineEntity->startOfLine.x = intersectionPointToChange.x;
			vLineEntity->startOfLine.y = intersectionPointToChange.y;
			startOfLineCreated = true;

			//vLineEntity->startOfLine.
			// check and see what side of the bbox
			// TODO - this is only temporary because i know where the point is going. 
			// TODO - I NEED to change this to find the other side of the line
			//if (intersectionPointToChange.x > vLineEntity->midPoint.x && intersectionPointToChange.x > vLineEntity->midPoint.x)

		}
		

		// if no...continue

		// if yes...calculate where the intersection is
		//		find midpoint between other 

		if (true)
		{
			real32 y1 = vLineEntity->midpoint.y;
			real32 x1 = vLineEntity->midpoint.x;
			real32 m = vLineEntity->perpSlopeReal;
			//rightSide
			real32 x = vMapEntity->mapSizeRect.max.x;
			real32 rightSideEquation = (m * x) - (m * x1);
			real32 yRight = rightSideEquation + y1;
			
			if (yRight < vMapEntity->mapSizeRect.max.y && yRight > vMapEntity->mapSizeRect.min.y)
			{
				vLineEntity->intersectsRightBBox = true;
				if (!startOfLineCreated)
				{
					vLineEntity->startOfLine.x = vMapEntity->mapSizeRect.max.x;
					vLineEntity->startOfLine.y = yRight;
				}
				else if (!endOfLineCreated)
				{
					vLineEntity->endOfLine.x = vMapEntity->mapSizeRect.max.x;
					vLineEntity->endOfLine.y = yRight;
				}
				startOfLineCreated = true;
			}
			//leftSide
			x = vMapEntity->mapSizeRect.min.x;
			rightSideEquation = (m * x) - (m * x1);
			real32 yLeft = rightSideEquation + y1;
			if (yLeft < vMapEntity->mapSizeRect.max.y && yLeft > vMapEntity->mapSizeRect.min.y)
			{
				vLineEntity->intersectsLeftBBox = true;
				if (!startOfLineCreated)
				{
					vLineEntity->startOfLine.x = vMapEntity->mapSizeRect.min.x;
					vLineEntity->startOfLine.y = yLeft;
				}
				else if (!endOfLineCreated)
				{
					vLineEntity->endOfLine.x = vMapEntity->mapSizeRect.min.x;
					vLineEntity->endOfLine.y = yLeft;
				}
				startOfLineCreated = true;
			}
			//topSide
			real32 y = vMapEntity->mapSizeRect.max.y;
			real32 leftSideEquation = (y - y1);
			//(m*x)-(m*x1)
			real32 eqStep2 = leftSideEquation + (m * x1);
			real32 xTop = eqStep2 / m;
			if (xTop < vMapEntity->mapSizeRect.max.x && xTop > vMapEntity->mapSizeRect.min.x)
			{
				vLineEntity->intersectsTopBBox = true;
				if (!startOfLineCreated)
				{
					vLineEntity->startOfLine.x = xTop;
					vLineEntity->startOfLine.y = vMapEntity->mapSizeRect.max.y;
				}
				else if (!endOfLineCreated)
				{
					vLineEntity->endOfLine.x = xTop;
					vLineEntity->endOfLine.y = vMapEntity->mapSizeRect.max.y;
				}
				startOfLineCreated = true;
			}

			//bottomSide
			y = vMapEntity->mapSizeRect.min.y;
			leftSideEquation = (y - y1);
			eqStep2 = leftSideEquation + (m * x1);
			real32 xBottom = eqStep2 / m;
			if (xBottom < vMapEntity->mapSizeRect.max.x && xBottom > vMapEntity->mapSizeRect.min.x)
			{
				vLineEntity->intersectsBottomBBox = true;
				if (!startOfLineCreated)
				{
					vLineEntity->startOfLine.x = xBottom;
					vLineEntity->startOfLine.y = vMapEntity->mapSizeRect.min.y;
				}
				else if (!endOfLineCreated)
				{
					vLineEntity->endOfLine.x = xBottom;
					vLineEntity->endOfLine.y = vMapEntity->mapSizeRect.min.y;
				}
				startOfLineCreated = true;
			}

		}
		 
		vLineEntity->lineFinalized = true;
		// determine if line hits bbox and can stop
		bool doesHitBBox = false;
		while (doesHitBBox)
		{

		}
	}
}