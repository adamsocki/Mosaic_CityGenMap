void MeshModelInit()
{
    Data->model.pathNumber = 0;
    LoadModelParse(&Data->model);

    Data->modelBld.pathNumber = 2;
    LoadModelParse(&Data->modelBld);
    
    Data->modelTest.pathNumber = 3;
    LoadModelParse(&Data->modelTest);

    AllocateModelOBJMesh(&Data->meshManager.meshes[Tile_Mesh], &Data->model);
    InitMesh(&Data->meshManager.meshes[Tile_Mesh]);
    Data->meshManager.meshCount++;

    AllocateModelOBJMesh(&Data->meshManager.meshes[CommercialBuilding_Mesh], &Data->modelBld);
    InitMesh(&Data->meshManager.meshes[CommercialBuilding_Mesh]);
    Data->meshManager.meshCount++;

    AllocateModelOBJMesh(&Data->meshManager.meshes[ResidentialBuildingType1_Mesh], &Data->modelTest);
    InitMesh(&Data->meshManager.meshes[ResidentialBuildingType1_Mesh]);
    Data->meshManager.meshCount++;


}