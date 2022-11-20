


bool isLetter(char c)
{
	return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');	
}
bool isNumber(char c)
{
	return c >= '0' && c <= '9';
}
bool isPeriod(char c)
{
	return c == '.';
}
bool isComma(char c)
{
	return c == ',';
}
bool isSpace(char c)
{
    return c == ' ';
}
bool isNegative(char c)
{
    return c == '-';
}
bool isForwardSlash(char c)
{
    return c == '/';
}
bool isNewLine(char c)
{
    return c == '\n';
}

void LoadModelParse(OBJModel* model)
{
    DynamicArray<TokenVal> tokens   = MakeDynamicArray<TokenVal>(&tokenArena, 10000);
    DynamicArray<OBJFaceVec> faces = MakeDynamicArray<OBJFaceVec>(&facesArena, 10000);
    DynamicArray<vec3> vertices = MakeDynamicArray<vec3>(&vertexArena, 10000);
    DynamicArray<OBJvNormals> normals = MakeDynamicArray<OBJvNormals>(&normalArena, 10000);
    DynamicArray<OBJvTexture> textures = MakeDynamicArray<OBJvTexture>(&textureArena, 10000);
   
    FileHandle file;

    char* path[] = 
    {
        "data/building1.obj"
    };

    if (OpenFileForRead(path[0], & file, &Game->frameMem))
    {
        //      STEP 1 - TOKENIZE .OBJ CONTENTS
        TokenVal t = {};

        while (file.offset < file.size)
        {
            t = {};
            char c = ReadChar(&file);

            while (c == ' ' || c == '\n' || c == '\r') {
				goto Advance;
			}

            while (isLetter(c))
            {
                if (t.start == NULL)
                {
                    t.type = TokenType_Identifier;
                    t.start = (char*)&file.data[file.offset - 1];
                }

                t.length++;
                char nextChar = file.data[file.offset];
                if (!isLetter(nextChar))
                {
                    goto AddToken;
                    break;
                }
                else
                {
                    c = ReadChar(&file);
                }
            }

            if (isComma(c))
            {
                t.start = (char*)&file.data[file.offset - 1];
				t.length = 1;
				t.type = TokenType_Comma;
            }

            while (isNumber(c) || isNegative(c))
            {
                if (t.start == NULL)
                {
                    t.type = TokenType_Value,
                    t.start = (char*)&file.data[file.offset - 1];
                }
                t.length++;
                char nextChar = file.data[file.offset];
                if (isSpace(nextChar) || isNewLine(nextChar) || isForwardSlash(nextChar))
                {
                    goto AddToken;
                    break;
                }
                if (isPeriod(nextChar))
                {
                    c = ReadChar(&file);
                    t.length++;
                    c = ReadChar(&file);
                }
                else
                {
                    c = ReadChar(&file);
                }
            }
            if (isForwardSlash(c))
            {
                t.start = (char*)&file.data[file.offset - 1];
                t.length = 1;
                t.type = TokenType_ForwardSlash;
            }
            goto Advance;

        AddToken:
			PushBack(&tokens, t);

		Advance:
			int32 baba = 0;

        }

        CloseFile(&file);
    }


    // READ DEM TOKEs
    int32 tokenIndex = 0;

    while (tokenIndex < tokens.count)
    {
        TokenVal t = tokens[tokenIndex];

        if (t.type = TokenType_Identifier)
        {
            if (strncmp(t.start, "v", t.length) == 0)
            {
                tokenIndex++;
                t = tokens[tokenIndex];

                // vec3 objVertex = {};

                model->vectors = (vec3*)malloc(sizeof(vec3) * 1000);
                memset(model->vectors, 0, sizeof(vec3) * 1000);

                model->vectors[model->vectorsCount].x = strtod(t.start, NULL);
                tokenIndex++;
                t = tokens[tokenIndex];
                model->vectors[model->vectorsCount].y = strtod(t.start, NULL);
                tokenIndex++;
                t = tokens[tokenIndex];
                model->vectors[model->vectorsCount].z = strtod(t.start, NULL);
                tokenIndex++;
                t = tokens[tokenIndex];
                model->vectorsCount++;

                //PushBack(&vertices, model.vectors);
            }
            else if (strncmp(t.start, "vn", 2) == 0)
            {

                tokenIndex++;
                t = tokens[tokenIndex];

                //vec3 objvNormal = {};

                model->normals = (vec3*)malloc(sizeof(vec3) * 1000);
                memset(model->normals, 0, sizeof(vec3) * 1000);

                model->normals[model->normalsCount].x = strtod(t.start, NULL);
                tokenIndex++;
                t = tokens[tokenIndex];
                model->normals[model->normalsCount].x = strtod(t.start, NULL);
                tokenIndex++;
                t = tokens[tokenIndex];
                model->normals[model->normalsCount].x = strtod(t.start, NULL);
                tokenIndex++;
                t = tokens[tokenIndex];
                model->normalsCount++;

                //PushBack(&normals, objvNormal);
            }
            else if (strncmp(t.start, "vt", 2) == 0)
            {
                tokenIndex++;
                t = tokens[tokenIndex];

                //OBJvTexture objvTexture = {};

                model->textureCoords = (vec2*)malloc(sizeof(vec2) * 1000);
                memset(model->textureCoords, 0, sizeof(vec2) * 1000);

                model->textureCoords[model->textureCoordsCount].x = strtod(t.start, NULL);
                tokenIndex++;
                t = tokens[tokenIndex];
                model->textureCoords[model->textureCoordsCount].x = strtod(t.start, NULL);
                tokenIndex++;
                t = tokens[tokenIndex];
                model->textureCoords[model->textureCoordsCount].x = strtod(t.start, NULL);
                tokenIndex++;
                t = tokens[tokenIndex];
                model->textureCoordsCount++;

            }
            else if (strncmp(t.start, "f", t.length) == 0)
            {
                tokenIndex++;
                t = tokens[tokenIndex];

                model->faces = (OBJFaceArray*)malloc(sizeof(OBJFaceArray) * 1000);
                memset(model->faces, 0, sizeof(OBJFaceArray) * 1000);

                while (strncmp(t.start, "\n", t.length) != 0)
                {
                    model->faces[model->facesCount].face1.x = strtod(t.start, NULL);
                    tokenIndex++;
                    t = tokens[tokenIndex];
                    model->faces[model->facesCount].face1.y = strtod(t.start, NULL);
                    tokenIndex++;
                    t = tokens[tokenIndex];
                    model->faces[model->facesCount].face1.z = strtod(t.start, NULL);
                    tokenIndex++;
                    t = tokens[tokenIndex];
                    model->faces[model->facesCount].face2.x = strtod(t.start, NULL);
                    tokenIndex++;
                    t = tokens[tokenIndex];
                    model->faces[model->facesCount].face2.y = strtod(t.start, NULL);
                    tokenIndex++;
                    t = tokens[tokenIndex];
                    model->faces[model->facesCount].face2.z = strtod(t.start, NULL);
                    tokenIndex++;
                    t = tokens[tokenIndex];
                    model->faces[model->facesCount].face3.x = strtod(t.start, NULL);
                    tokenIndex++;
                    t = tokens[tokenIndex];
                    model->faces[model->facesCount].face3.y = strtod(t.start, NULL);
                    tokenIndex++;
                    t = tokens[tokenIndex];
                    model->faces[model->facesCount].face3.z = strtod(t.start, NULL);
                    tokenIndex++;
                    t = tokens[tokenIndex];
                    model->faces[model->facesCount].face4.x = strtod(t.start, NULL);
                    tokenIndex++;
                    t = tokens[tokenIndex];
                    model->faces[model->facesCount].face4.y = strtod(t.start, NULL);
                    tokenIndex++;
                    t = tokens[tokenIndex];
                    model->faces[model->facesCount].face4.z = strtod(t.start, NULL);
                    tokenIndex++;
                    t = tokens[tokenIndex];
                    model->facesCount++;
                    tokenIndex++;
                    t = tokens[tokenIndex];
                }
            }
            else
            {
                tokenIndex++;
                t = tokens[tokenIndex];
            }
        }
    }


   /* model->vectors = (vec3*)malloc(sizeof(vec3) * vertices.count);
    memset(model->vectors, 0, sizeof(OBJVertex) * vertices.count);
    model->vectorsCount = vertices.count;

    for (int i = 0; i < vertices.count; i++)
    {
        model->vectors[i] = vertices[i];
    }*/
    
    /*model->normals = (OBJvNormals*)malloc(sizeof(OBJvNormals) * normals.count);
    memset(model->normals, 0, sizeof(OBJVertex)* normals.count);
    model->normalsCount = normals.count;
    
    for (int i = 0; i < normals.count; i++)
    {
        model->normals[i] = normals[i];
    }*/

    /*model->textures = (OBJvTexture*)malloc(sizeof(OBJvTexture) * textures.count);
    memset(model->textures, 0, sizeof(OBJvTexture)* textures.count);
    model->texturesCount = textures.count;

    for (int i = 0; i < textures.count; i++)
    {
        model->textures[i] = textures[i];
    }*/

    /*model->faces = (OBJFaceVec*)malloc(sizeof(OBJFaceVec) * faces.count);
    memset(model->faces, 0, sizeof(OBJFaceVec)* faces.count);
    model->facesCount = faces.count;

    for (int i = 0; i < faces.count; i++)
    {
        model->faces[i] = faces[i];
    }*/
}




void DisplayOBJModel(OBJModel* model, Mesh* meshModel, int32 faceNum)
{
    
    //InitMesh(model);
    
    //meshModel;

    meshModel->vertCount = model->vectorsCount;
    meshModel->normalsCount = model->normalsCount;
    meshModel->texcoordsCount = model->textureCoordsCount;

    meshModel->data = (void*)malloc((sizeof(vec3) * meshModel->vertCount) + (sizeof(vec2) * meshModel->texcoordsCount));
    meshModel->size = (sizeof(vec3) * meshModel->vertCount) + (sizeof(vec2) * meshModel->texcoordsCount);

    meshModel->verts = (vec3*)meshModel->data;

    for (int i = 0; i < meshModel->vertCount; i++)
    {
        meshModel->verts[i] = model->vectors[i];
    }

    meshModel->texcoords = (vec2*)((uint8*)meshModel->data + (sizeof(vec3) * meshModel->vertCount));

    for (int i = 0; i < meshModel->texcoordsCount; i++)
    {
        meshModel->texcoords[i] = model->textureCoords[i];
    }

    meshModel->indexCount = model->facesCount;
    meshModel->indices = (uint32*)malloc(sizeof(uint32) * meshModel->indexCount);

    meshModel->indices[0 + (faceNum * 4)] = model->faces[faceNum].face1.x;
    meshModel->indices[1 + (faceNum * 4)] = model->faces[faceNum].face2.x;
    meshModel->indices[2 + (faceNum * 4)] = model->faces[faceNum].face3.x;
    meshModel->indices[3 + (faceNum * 4)] = model->faces[faceNum].face4.x;

    for (int i = 0; i < 1; i++)
    {
        

       
    }

    //meshModel->
    vec2 mousePos = Input->mousePosNormSigned;
    mousePos.x = mousePos.x * 8;
    mousePos.y = mousePos.y * 4.5f;

    vec3 pos = V3(mousePos.x, mousePos.y,-1.0f);
    vec2 scale = V2(1.0f, 1.0f);
    real32 angle = 0;
    vec4 color = V4(1.0f, 0.1f, 1.0f, 1.0f);
        

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    /*AllocateQuad(meshModel);
    InitMesh(meshModel);*/

    //Shader* shader = &Game->shader;
    //SetShader(shader);

    //glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    ////Mesh* mesh = meshModel;

    //mat4 model_ = TRS(V3(pos.x, pos.y, 0), AxisAngle(V3(0, 0, 1), angle), V3(scale.x, scale.y, 0.0f));

    //glUniformMatrix4fv(shader->uniforms[0].id, 1, GL_FALSE, model_.data);
    //glUniformMatrix4fv(shader->uniforms[1].id, 1, GL_FALSE, Game->camera.viewProjection.data);

    //glUniform4fv(shader->uniforms[2].id, 1, color.data);

    //glBindBuffer(GL_ARRAY_BUFFER, meshModel->vertBufferID);
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshModel->indexBufferID);

    //// 1st attribute buffer : vertices
    //int vert = glGetAttribLocation(shader->programID, "vertexPosition_modelspace");
    //glEnableVertexAttribArray(vert);
    //glVertexAttribPointer(vert, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);


    //glDrawElements(GL_TRIANGLES, meshModel->indexCount, GL_UNSIGNED_INT, (GLvoid*)0);

    //glDisableVertexAttribArray(vert);
    





    //glDisableVertexAttribArray(model_);

    //void DrawRect(vec2 pos, vec2 scale, real32 angle, vec4 color) {
    //    // @PERF: don't do this every draw call
    //    Shader* shader = &Game->shader;
    //    SetShader(shader);

    //    glEnable(GL_BLEND);
    //    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //    Mesh* mesh = &Game->quad;

    //    mat4 model = TRS(V3(pos.x, pos.y, 0), AxisAngle(V3(0, 0, 1), angle), V3(scale.x, scale.y, 0.0f));

    //    glUniformMatrix4fv(shader->uniforms[0].id, 1, GL_FALSE, model.data);
    //    glUniformMatrix4fv(shader->uniforms[1].id, 1, GL_FALSE, Game->camera.viewProjection.data);

    //    glUniform4fv(shader->uniforms[2].id, 1, color.data);

    //    glBindBuffer(GL_ARRAY_BUFFER, mesh->vertBufferID);
    //    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBufferID);

    //    // 1st attribute buffer : vertices
    //    int vert = glGetAttribLocation(shader->programID, "vertexPosition_modelspace");
    //    glEnableVertexAttribArray(vert);
    //    glVertexAttribPointer(vert, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);


    //    glDrawElements(GL_TRIANGLES, mesh->indexCount, GL_UNSIGNED_INT, (GLvoid*)0);

    //    glDisableVertexAttribArray(vert);
    //}

}