
void GenerateLotOnLine()
{

 EntityTypeBuffer* vMapBuffer = &Data->em.buffers[VoronoiType_Map];
    EntityTypeBuffer* vNodeBuffer = &Data->em.buffers[VoronoiType_Node];
    EntityTypeBuffer* lotBuffer = &Data->em.buffers[Type_Lot];
	
    VoronoiMap* vMapEntitiesInBuffer = (VoronoiMap*)vMapBuffer->entities;
    VoronoiNode* vNodeEntitiesInBuffer = (VoronoiNode*)vNodeBuffer->entities;
	
    TypeLot* lotEntitiesInBuffer = (TypeLot*)lotBuffer->entities;

    //				GET MAP ENTITY FOR REFERENCE WITHIN FUNCTION	
    VoronoiMap* vMapEntity = (VoronoiMap*)GetEntity(&Data->em, vMapEntitiesInBuffer[0].handle);
    //				GET REFERENCE TO NODES FOR REFERENCE WITHIN FUNCTION


    VoronoiLine* vLine = (VoronoiLine*)GetEntity(&Data->em, vMapEntity->vLines[0]);
   


    real32 lineLength = vLine->length;

    EntityHandle lotHandle = AddEntity(&Data->em, Type_Lot);
	TypeLot* lotEntity = (TypeLot*)GetEntity(&Data->em, lotHandle);

    lotEntity->handle = lotHandle;
    lotEntity->lotOffsetFromStreet = 0.5f;

    lotEntity->vLineIndex = 0;
	
	lotEntity->lotSize[0] = V2(0,0);
	lotEntity->lotSize[1] = V2(0,1);
	lotEntity->lotSize[2] = V2(1,0);
	lotEntity->lotSize[3] = V2(1,1);
	
	lotEntity->lotOutline[0] = V3(vLine->startOfLine.x + lotEntity->lotOffsetFromStreet, vLine->startOfLine.y, vLine->startOfLine.z);
	lotEntity->lotOutline[1] = V3(vLine->startOfLine.x + lotEntity->lotOffsetFromStreet, vLine->startOfLine.y, vLine->startOfLine.z);
	lotEntity->lotOutline[2] = V3(vLine->startOfLine.x + lotEntity->lotOffsetFromStreet, vLine->startOfLine.y, vLine->startOfLine.z);
	lotEntity->lotOutline[3] = V3(vLine->startOfLine.x + lotEntity->lotOffsetFromStreet, vLine->startOfLine.y, vLine->startOfLine.z);

	lotEntity->lotOutline[0].x += lotEntity->lotSize[0].x;
	lotEntity->lotOutline[1].x += lotEntity->lotSize[1].x;
	lotEntity->lotOutline[2].x += lotEntity->lotSize[2].x;
	lotEntity->lotOutline[3].x += lotEntity->lotSize[3].x;
	
	lotEntity->lotOutline[0].y += lotEntity->lotSize[0].y;
	lotEntity->lotOutline[1].y += lotEntity->lotSize[1].y;
	lotEntity->lotOutline[2].y += lotEntity->lotSize[2].y;
	lotEntity->lotOutline[3].y += lotEntity->lotSize[3].y;

}