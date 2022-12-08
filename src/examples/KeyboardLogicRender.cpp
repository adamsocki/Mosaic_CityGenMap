
void TileArrowInit()
{
	EntityHandle tileArrowHandle = AddEntity(&Data->em, TileArrow_Type);
	TileArrow* tileArrowEntity = (TileArrow*)GetEntity(&Data->em, tileArrowHandle);

	tileArrowEntity->handle = tileArrowHandle;
	tileArrowEntity->position = V3(0, 0, -10);

}

void TileArrowLogic()
{
	EntityTypeBuffer* tileArrowBuffer = &Data->em.buffers[TileArrow_Type];
	TileArrow* tileArrowEntity = (TileArrow*)tileArrowBuffer->entities;

	TileArrow *arrowEntity = &tileArrowEntity[0];

	EntityTypeBuffer* gameMapBuffer = &Data->em.buffers[GameMap_Type];
	GameMap* gameMapEntitiesInBuffer = (GameMap*)gameMapBuffer->entities;

	GameMap* gameMapEntity = &gameMapEntitiesInBuffer[0];

	
	if (InputPressed(Keyboard, Input_UpArrow))
	{
		arrowEntity->row++;
		//arrowEntity->position = tileEntity
	}
	if (InputPressed(Keyboard, Input_DownArrow))
	{
		arrowEntity->row--;
	}
	if (InputPressed(Keyboard, Input_RightArrow))
	{
		arrowEntity->column--;
	}
	if (InputPressed(Keyboard, Input_LeftArrow))
	{
		arrowEntity->column++;
	}

	for (int i = 0; i < gameMapEntity->tileCount; i++)
	{
		Tile* tileEntity = (Tile*)GetEntity(&Data->em, gameMapEntity->tiles[i]);

		if (arrowEntity->column == tileEntity->column && arrowEntity->row == tileEntity->row)
		{
			arrowEntity->tileHandle = tileEntity->handle;
			
			arrowEntity->position = tileEntity->position;
			arrowEntity->developed = true;

			arrowEntity->position.y += 0.1f;
			arrowEntity->rotation = tileEntity->rotation;
		}
	}
}

void TileArrowRender()
{
	EntityTypeBuffer* tileArrowBuffer = &Data->em.buffers[TileArrow_Type];
	TileArrow* tileArrowEntity = (TileArrow*)tileArrowBuffer->entities;
	TileArrow* arrowEntity = &tileArrowEntity[0];
	DrawTextScreenPixel(&Game->monoFont, V2(60, 60), 10.0f, RGB(1.0f, 1.0f, 1.0f), "o.x: %.10f", arrowEntity->position.x);

	RenderOBJModel(&Game->modelMesh, arrowEntity->position, V3(1.0f, 1.0f, 1.0f), V4(0), arrowEntity->rotation, &Data->sprites.tile3_mouse);

	
}