//  CameraInputControl();
//  InputLogic();


void CameraInputControl()
{
	Camera* cam = &Game->camera;
	real32 cameraSpeed = 8.0f;
	real32 rotationSpeed = 0.4f;
    
	if (InputHeld(Keyboard, Input_W))
    {
        Game->cameraPosition.z += cameraSpeed * Game->deltaTime;
    }
    if (InputHeld(Keyboard, Input_S))
    {
        Game->cameraPosition.z -= cameraSpeed * Game->deltaTime;
    }
    if (InputHeld(Keyboard, Input_A))
    {
        Game->cameraRotation.x += rotationSpeed * Game->deltaTime;
    }
    if (InputHeld(Keyboard, Input_D))
    {
        Game->cameraRotation.x -= rotationSpeed * Game->deltaTime;
    }
	if (InputHeld(Keyboard, Input_E))
	{
		Game->cameraPosition.y += cameraSpeed * Game->deltaTime;
	}
	if (InputHeld(Keyboard, Input_Q))
	{
		Game->cameraPosition.y -= cameraSpeed * Game->deltaTime;
	}
	if (InputHeld(Keyboard, Input_C))
	{
		Game->cameraRotation.y += rotationSpeed * Game->deltaTime;
	}
}

void InputLogic()
{
    CameraInputControl();
    //GameplayInputControl();  // TODO: things like create buildings
}

void InputRender()
{
    
}