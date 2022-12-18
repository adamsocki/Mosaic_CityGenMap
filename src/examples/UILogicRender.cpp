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
	CityStateRender(gameMapEntity);
	ManagerRender(gameMapEntity);
}