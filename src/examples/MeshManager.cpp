void MeshInit()
{
    Data->model.pathNumber = 0;
    LoadModelParse(&Data->model);

    Data->modelBld.pathNumber = 2;
    LoadModelParse(&Data->modelBld);
    
    Data->modelTest.pathNumber = 3;
    LoadModelParse(&Data->modelTest);
}