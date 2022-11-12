

int32 freeList[1000];
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

EntityHandle AddEntity(EntityManager *em, OSMType type) {
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
}
