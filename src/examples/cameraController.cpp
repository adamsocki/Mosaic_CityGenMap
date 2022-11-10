


void MoveCamera()
{

	Camera* cam = &Game->camera;
	

	if (InputPressed(Keyboard, Input_W))
	{

		real32 movement = 1.0f;
		Game->cameraPosition.y += movement;
	}

	if (InputPressed(Keyboard, Input_S))
	{

		real32 movement = 1.0f;
		Game->cameraPosition.y -= movement;
	}

	if (InputPressed(Keyboard, Input_D))
	{

		real32 movement = 1.0f;
		Game->cameraPosition.x += movement;
	}

	if (InputPressed(Keyboard, Input_A))
	{

		real32 movement = 1.0f;
		Game->cameraPosition.x -= movement;
	}



	if (InputPressed(Keyboard, Input_G))
	{

		Game->cameraRotation = AxisAngle(V3(1,1,0), 1.0);
	}





}