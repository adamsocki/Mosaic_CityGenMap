void CityStateRender(GameMap* gameMapEntity)
{
	// display no of peoples
	
	DrawTextScreenPixel(&Game->monoFont, V2(60,100), 10.0f, RGB(1.0f, 1.0f, 1.0f), "Commerical total cap: %d", gameMapEntity->mapData.commercialBuildingPersonCapacity);
	DrawTextScreenPixel(&Game->monoFont, V2(60,120), 10.0f, RGB(1.0f, 1.0f, 1.0f), "Residential total cap: %d", gameMapEntity->mapData.residentialBuildingPersonCapacity);
	DrawTextScreenPixel(&Game->monoFont, V2(60,140), 10.0f, RGB(1.0f, 1.0f, 1.0f), "Total persons: %d", gameMapEntity->personCount);

	// calculate person residential capacity
}

void ManagerRender(GameMap* gameMapEntity)
{
	DrawTextScreenPixel(&Game->monoFont, V2(60,160), 10.0f, RGB(1.0f, 1.0f, 1.0f), "Total Money: $%.2f", gameMapEntity->gameManager.currentMoney);
}


void UIRender(GameMap* gameMapEntity)
{
	//DrawSprite(V2(Game->cameraPosition.x, Game->cameraPosition.y), V2(10) , Game->cameraRotation, &Data->sprites.road_uv);
    //DrawRectScreen(V2(10.0f, 1.0f), V2(10), V4(1,1,1,1));
	//DrawRectScreenNorm(V2(10.0f, 1.0f), V2(10), V4(1,1,1,1));
	CityStateRender(gameMapEntity);
	ManagerRender(gameMapEntity);
	vec2 cursorPos = V2(400, 500);


    DrawRectScreen(cursorPos, V2(24.0f, 48.0f), V4(0.5f, 0.5f, 0.5f, 0.5f));   
    DrawSpriteScreen(cursorPos, V2(24.0f, 48.0f), 0, &Data->sprites.road_uv); 

	  
    DrawSpriteScreen(V2(800, 400), V2(100.0f, 50.0f), 0, &Data->sprites.ui1);   
}