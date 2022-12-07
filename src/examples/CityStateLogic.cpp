

void CityStateInit()
{
	// init persons in city





	// init buildings int city

	// init roads in city

	//

}



void CityStateLogic()
{

	// get tiles


	// determine if 




}


void CityStateRender()
{
	// display no of peoples
	DrawTextScreenPixel(&Game->monoFont, V2(60,100), 10.0f, RGB(1.0f, 1.0f, 1.0f), "Persons: %d", 1);
	DrawSpriteScreen(V2(1, 1), V2(1, 1), 0, &Data->sprites.pop_sprite);
}