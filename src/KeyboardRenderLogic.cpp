
void KeyboardInit()
{
	EntityHandle keyboardHandle = AddEntity(&Data->em, Keyboard_Type);
	KeyboardEntity* keyboardEntity = (KeyboardEntity*)GetEntity(&Data->em, keyboardHandle);

	keyboardEntity->handle = keyboardHandle;
	keyboardEntity->position = V3(0, 0, -10);

}

void KeyboardLogic()
{


	if (InputPressed(Keyboard, Input_UpArrow))
	{

	}

}