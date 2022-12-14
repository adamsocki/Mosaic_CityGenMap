
void SetCameraToMapPositionInit()
{
    Camera* cam = &Game->camera;

    vec3 posToStartCamera = {};
 
    posToStartCamera.x = 9.f;
    posToStartCamera.y = 10.0f;
    posToStartCamera.z = -18.0f;

    Game->cameraRotation.x += 0.3f;
    Game->cameraPosition = posToStartCamera;
}