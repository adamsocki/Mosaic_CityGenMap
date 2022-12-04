

int32 freeList[10000];
int32 freeListCount = 0;


void* GetEntity(EntityManager* em, EntityHandle handle) {
	if (handle.indexInInfo >= em->entityCapacity) {
		return NULL;
	}

	EntityInfo* info = &Data->em.entities[handle.indexInInfo];

	if (info->generation != handle.generation) {
		return NULL;
	}
	if (info->type != handle.type) {
		return NULL;
	}

	EntityTypeBuffer* buffer = &em->buffers[info->type];

	return ((u8*)buffer->entities + (buffer->sizeInBytes * info->indexInBuffer));
}

void DeleteEntity(EntityManager* em, EntityHandle handle) {
	
	
	freeList[freeListCount] = handle.indexInInfo;
	freeListCount++;

	EntityTypeBuffer* buffer = &em->buffers[handle.type];
	EntityInfo* info = &em->entities[handle.indexInInfo];
	EntityHandle handleOfSwappedEntity;

	buffer->count--;
}

EntityHandle AddEntity(EntityManager *em, EntityType type) {
	int32 nextFreeIdInIndex = em->nextID;
	
	if (freeListCount > 0) {
		nextFreeIdInIndex = freeList[freeListCount - 1];
		freeListCount--;
	}
	else {
		em->nextID++;
	}
	
	EntityInfo* info = &em->entities[nextFreeIdInIndex];
	info->type = type;
	info->generation++;

	EntityTypeBuffer* buffer = &em->buffers[type];
	info->indexInBuffer = buffer->count;
	buffer->count++;

	EntityHandle handle = {};
	handle.generation = info->generation;
	handle.indexInInfo = nextFreeIdInIndex;
	handle.type = type;

	return handle;
}

void InitializeEntityManager() {
	// Entity Manager
	Data->em.entityCapacity = 100000;
	Data->em.entities = (EntityInfo*)malloc(sizeof(EntityInfo) * Data->em.entityCapacity);
	memset(Data->em.entities, 0, sizeof(EntityInfo) * Data->em.entityCapacity);
	Data->em.nextID = 0;
	
}

void InitializeEntityBuffers()
{
	EntityTypeBuffer* nodeBuffer = &Data->em.buffers[OSMType_Node];
	nodeBuffer->capacity = 8000;
	nodeBuffer->sizeInBytes = sizeof(Node);
	nodeBuffer->count = 0;
	nodeBuffer->entities = (Node*)malloc(nodeBuffer->capacity * nodeBuffer->sizeInBytes);
	memset(nodeBuffer->entities, 0, sizeof(Node) * nodeBuffer->capacity);

	EntityTypeBuffer* boundBuffer = &Data->em.buffers[OSMType_Bound];
	boundBuffer->capacity = 2000;
	boundBuffer->sizeInBytes = sizeof(Bound);
	boundBuffer->count = 0;
	boundBuffer->entities = (Bound*)malloc(boundBuffer->capacity * boundBuffer->sizeInBytes);
	memset(boundBuffer->entities, 0, sizeof(Bound) * boundBuffer->capacity);

	EntityTypeBuffer* wayBuffer = &Data->em.buffers[OSMType_Way];
	wayBuffer->capacity = 2000;
	wayBuffer->sizeInBytes = sizeof(Way);
	wayBuffer->count = 0;
	wayBuffer->entities = (Way*)malloc(wayBuffer->capacity * wayBuffer->sizeInBytes);
	memset(wayBuffer->entities, 0, sizeof(Way) * wayBuffer->capacity);

	EntityTypeBuffer* vMapBuffer = &Data->em.buffers[VoronoiType_Map];
	vMapBuffer->capacity = 2000;
	vMapBuffer->sizeInBytes = sizeof(VoronoiMap);
	vMapBuffer->count = 0;
	vMapBuffer->entities = (VoronoiMap*)malloc(vMapBuffer->capacity * vMapBuffer->sizeInBytes);
	memset(vMapBuffer->entities, 0, sizeof(VoronoiMap) * vMapBuffer->capacity);

	EntityTypeBuffer* vNodeBuffer = &Data->em.buffers[VoronoiType_Node];
	vNodeBuffer->capacity = 2000;
	vNodeBuffer->sizeInBytes = sizeof(VoronoiNode);
	vNodeBuffer->count = 0;
	vNodeBuffer->entities = (VoronoiNode*)malloc(vNodeBuffer->capacity * vNodeBuffer->sizeInBytes);
	memset(vNodeBuffer->entities, 0, sizeof(VoronoiNode) * vNodeBuffer->capacity);

	EntityTypeBuffer* vLineBuffer = &Data->em.buffers[VoronoiType_Line];
	vLineBuffer->capacity = 4000;
	vLineBuffer->sizeInBytes = sizeof(VoronoiLine);
	vLineBuffer->count = 0;
	vLineBuffer->entities = (VoronoiLine*)malloc(vLineBuffer->capacity * vLineBuffer->sizeInBytes);
	memset(vLineBuffer->entities, 0, sizeof(VoronoiLine) * vLineBuffer->capacity);
	
	EntityTypeBuffer* vIntersectionBuffer = &Data->em.buffers[VoronoiType_Intersection];
	vIntersectionBuffer->capacity = 4000;
	vIntersectionBuffer->sizeInBytes = sizeof(VoronoiIntersection);
	vIntersectionBuffer->count = 0;
	vIntersectionBuffer->entities = (VoronoiIntersection*)malloc(vIntersectionBuffer->capacity * vIntersectionBuffer->sizeInBytes);
	memset(vIntersectionBuffer->entities, 0, sizeof(VoronoiIntersection) * vIntersectionBuffer->capacity);	

	EntityTypeBuffer* lotBuffer = &Data->em.buffers[Type_Lot];
	lotBuffer->capacity = 4000;
	lotBuffer->sizeInBytes = sizeof(TypeLot);
	lotBuffer->count = 0;
	lotBuffer->entities = (TypeLot*)malloc(lotBuffer->capacity * lotBuffer->sizeInBytes);
	memset(lotBuffer->entities, 0, sizeof(Type_Lot) * lotBuffer->capacity);	

}
