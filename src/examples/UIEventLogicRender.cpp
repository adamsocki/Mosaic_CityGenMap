


void UIEventInit()
{



}


void UIEventLogic()
{



}


void UIEventCreate()
{




}






void UIEventRender()
{
    EntityTypeBuffer* uiEventBuffer = &Data->em.buffers[UIEvent_Type];
    UIEvent* uiEventEntitiesInBuffer = (UIEvent*)uiEventBuffer->entities;

    for (int i = 0; i < uiEventBuffer->count; i++)
    {
        //(UIEvent*) uiEventEntity = (UIEvent*)GetEntity(&Data->em, uiEventEntitiesInBuffer[i].handle);
        
    }


}
