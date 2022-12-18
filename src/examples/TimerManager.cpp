


void GameTimerInit()
{


}


void GameTimerAdvance()
{    
    real32 speedRateMultiplier = 1.0f;
    Data->timerManager.playerGenerationTimer += Game->deltaTime * speedRateMultiplier;
    Data->timerManager.annualTaxationTimer += Game->deltaTime * speedRateMultiplier;
}