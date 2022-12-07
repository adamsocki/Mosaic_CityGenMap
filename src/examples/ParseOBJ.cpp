


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
    /*DynamicArray<OBJFaceVec> faces = MakeDynamicArray<OBJFaceVec>(&facesArena, 10000);
    DynamicArray<vec3> vertices = MakeDynamicArray<vec3>(&vertexArena, 10000);
    DynamicArray<OBJvNormals> normals = MakeDynamicArray<OBJvNormals>(&normalArena, 10000);
    DynamicArray<OBJvTexture> textures = MakeDynamicArray<OBJvTexture>(&textureArena, 10000);
   */
    FileHandle file;
    file.currentLine = 0;

    char* path[] = 
    {
        "data/tile4.obj",
        "data/untitled1.obj",
        "data/untitled2.obj",
        "data/block_Test2.obj"
    };



    if (OpenFileForRead(path[model->pathNumber], &file, &Game->frameMem))
    {
        //      STEP 1 - TOKENIZE .OBJ CONTENTS
        TokenVal t = {};

        while (file.offset < file.size)
        {
            t = {};
            char c = ReadChar(&file);

            while (c == ' ' || c == '\n' || c == '\r') {
                if (isNewLine(c))
                {
                    file.currentLine++;
                }
				goto Advance;
			}

            while (isLetter(c) && file.currentLine > 2)
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

        if (t.type == TokenType_Identifier)
        {
            if (strncmp(t.start, "v", t.length) == 0)
            {
               

                // vec3 objVertex = {};

                model->vectors = (vec3*)malloc(sizeof(vec3) * 5000);
                memset(model->vectors, 0, sizeof(vec3) * 5000);

                while (strncmp(t.start, "vt", 2) != 0 && strncmp(t.start, "vn", 2) != 0)
                {
                    tokenIndex++;
                    t = tokens[tokenIndex];
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
                }

               

                //PushBack(&vertices, model.vectors);
            }
            else if (strncmp(t.start, "vn", 2) == 0)
            {
                //vec3 objvNormal = {};

                model->normals = (vec3*)malloc(sizeof(vec3) * 5000);
                memset(model->normals, 0, sizeof(vec3) * 5000);

                while (strncmp(t.start, "vn", 2) == 0)
                {
                    tokenIndex++;
                    t = tokens[tokenIndex];
                    model->normals[model->normalsCount].x = strtod(t.start, NULL);
                    tokenIndex++;
                    t = tokens[tokenIndex];
                    model->normals[model->normalsCount].y = strtod(t.start, NULL);
                    tokenIndex++;
                    t = tokens[tokenIndex];
                    model->normals[model->normalsCount].z = strtod(t.start, NULL);
                    tokenIndex++;
                    t = tokens[tokenIndex];
                    model->normalsCount++;
                }

               

                //PushBack(&normals, objvNormal);
            }
            else if (strncmp(t.start, "vt", 2) == 0)
            {
                //OBJvTexture objvTexture = {};

                model->textureCoords = (vec2*)malloc(sizeof(vec2) * 5000);
                memset(model->textureCoords, 0, sizeof(vec2) * 5000);

                while (strncmp(t.start, "vt", t.length) == 0)
                {
                    tokenIndex++;
                    t = tokens[tokenIndex]; 
                    model->textureCoords[model->textureCoordsCount].x = strtod(t.start, NULL);
                    tokenIndex++;
                    t = tokens[tokenIndex];
                    model->textureCoords[model->textureCoordsCount].y = strtod(t.start, NULL);
                    tokenIndex++;
                    t = tokens[tokenIndex];
                   /* model->textureCoords[model->textureCoordsCount].z = strtod(t.start, NULL);
                    tokenIndex++;
                    t = tokens[tokenIndex];*/
                    model->textureCoordsCount++;
                }

                

            }
            else if (strncmp(t.start, "f", t.length) == 0)
            {
                tokenIndex++;
                t = tokens[tokenIndex];

                model->faces = (OBJFaceArray*)malloc(sizeof(OBJFaceArray) * 5000);
                memset(model->faces, 0, sizeof(OBJFaceArray) * 5000);

                while (strncmp(t.start, "\n", t.length) != 0)
                {
                    model->faces[model->facesCount].face1.x = strtod(t.start, NULL);
                    model->indexCount++;
                    tokenIndex++;
                    t = tokens[tokenIndex];
                    model->faces[model->facesCount].face1.y = strtod(t.start, NULL);
                    model->indexCount++;
                    tokenIndex++;
                    t = tokens[tokenIndex];
                    model->faces[model->facesCount].face1.z = strtod(t.start, NULL);
                    model->indexCount++;
                    tokenIndex++;
                    t = tokens[tokenIndex];
                    model->faces[model->facesCount].face2.x = strtod(t.start, NULL);
                    model->indexCount++;
                    tokenIndex++;
                    t = tokens[tokenIndex];
                    model->faces[model->facesCount].face2.y = strtod(t.start, NULL);
                    model->indexCount++;
                    tokenIndex++;
                    t = tokens[tokenIndex];
                    model->faces[model->facesCount].face2.z = strtod(t.start, NULL);
                    model->indexCount++;
                    tokenIndex++;
                    t = tokens[tokenIndex];
                    model->faces[model->facesCount].face3.x = strtod(t.start, NULL);
                    model->indexCount++;
                    tokenIndex++;
                    t = tokens[tokenIndex];
                    model->faces[model->facesCount].face3.y = strtod(t.start, NULL);
                    model->indexCount++;
                    tokenIndex++;
                    t = tokens[tokenIndex];
                    model->faces[model->facesCount].face3.z = strtod(t.start, NULL);
                    model->indexCount++;
                    tokenIndex++;
                    t = tokens[tokenIndex];
                   /*if (t.type != TokenType_Identifier)
                    {
                        model->faces[model->facesCount].faceArrayCount = 4;
                        model->faces[model->facesCount].face4.x = strtod(t.start, NULL);
                        model->indexCount++;
                        tokenIndex++;
                        t = tokens[tokenIndex];
                        model->faces[model->facesCount].face4.y = strtod(t.start, NULL);
                        model->indexCount++;
                        tokenIndex++;
                        t = tokens[tokenIndex];
                        model->faces[model->facesCount].face4.z = strtod(t.start, NULL);
                        model->indexCount++;
                        tokenIndex++;
                        t = tokens[tokenIndex];
                    }
                    else
                    {
                        model->faces[model->facesCount].faceArrayCount = 3;
                    }*/
                    //tokenIndex++;
                    //t = tokens[tokenIndex];


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
        else
        {
            tokenIndex++;
            t = tokens[tokenIndex];
        }
        
    }
    DeallocateDynamicArray(&tokens);    

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

void AllocateModelOBJMesh(Mesh* mesh, OBJModel* objModel)
{
    uint32 vertexSize = sizeof(vec3) + sizeof(vec3) + sizeof(vec3);

    mesh->vertCount = objModel->facesCount * 3;
    mesh->size = vertexSize * mesh->vertCount;
    mesh->data = malloc(mesh->size);

    mesh->verts = (vec3*)(mesh->data);
    mesh->normals = (vec3*)((uint8*)mesh->data + sizeof(vec3) * mesh->vertCount);
    mesh->texcoords = (vec2*)((uint8*)mesh->data + (sizeof(vec3) + sizeof(vec3)) * mesh->vertCount);
    /*AllocateModel(&gameMem->modelMesh);
    InitMesh(&gameMem->modelMesh);*/

    mesh->indexCount = objModel->facesCount * 3;
    mesh->indices = (uint32*)malloc(sizeof(uint32) * mesh->indexCount);

    uint32 vertexOffset = 0;
    uint32 indexOffset = 0;

    for (int i = 0; i < objModel->facesCount; i++)
    {
        int32 faceVert1 = objModel->faces[i].face1.x - 1;
        int32 faceVert2 = objModel->faces[i].face2.x - 1;
        int32 faceVert3 = objModel->faces[i].face3.x - 1;

        int32 faceTexCoord1 = objModel->faces[i].face1.y - 1;
        int32 faceTexCoord2 = objModel->faces[i].face2.y - 1;
        int32 faceTexCoord3 = objModel->faces[i].face3.y - 1;

        int32 faceNormal1 = objModel->faces[i].face1.z - 1;
        int32 faceNormal2 = objModel->faces[i].face2.z - 1;
        int32 faceNormal3 = objModel->faces[i].face3.z - 1;

        mesh->verts[vertexOffset + 0] = objModel->vectors[faceVert1];
        mesh->verts[vertexOffset + 1] = objModel->vectors[faceVert2];
        mesh->verts[vertexOffset + 2] = objModel->vectors[faceVert3];

        mesh->normals[vertexOffset + 0] = objModel->normals[faceNormal1];
        mesh->normals[vertexOffset + 1] = objModel->normals[faceNormal2];
        mesh->normals[vertexOffset + 2] = objModel->normals[faceNormal3];

        mesh->texcoords[vertexOffset + 0] = objModel->textureCoords[faceTexCoord1];
        mesh->texcoords[vertexOffset + 1] = objModel->textureCoords[faceTexCoord2];
        mesh->texcoords[vertexOffset + 2] = objModel->textureCoords[faceTexCoord3];

        mesh->indices[indexOffset + 0] = vertexOffset + 0;
        mesh->indices[indexOffset + 1] = vertexOffset + 1;
        mesh->indices[indexOffset + 2] = vertexOffset + 2;
       
        vertexOffset += 3;
        indexOffset += 3;
        
        /* mesh->indices[indexOffset + 3] = vertexOffset + 0;
         mesh->indices[indexOffset + 4] = vertexOffset + 3;
         mesh->indices[indexOffset + 5] = vertexOffset + 2;*/
       
       //     mesh->indices[indexOffset + 4] = vertexOffset + 3;
       // }
       ///* mesh->indices[indexOffset + 3] = vertexOffset + 0;
       // mesh->indices[indexOffset + 4] = vertexOffset + 3;
       // mesh->indices[indexOffset + 5] = vertexOffset + 2;*/
       // if (fourCount)
       // {
       //     vertexOffset += 4;
       //     indexOffset += 4;
       // }
       // else
       // {
       //     vertexOffset += 3;
       //     indexOffset += 3;
       // }
       
    }
}

void RenderOBJModel(Mesh* mesh, vec3 pos, vec3 scale, vec4 color, quaternion rotation, Sprite *texture)
{
    Shader* shader = &Game->objShader;
    SetShader(shader);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    mat4 model = TRS(pos, rotation, scale);

    glUniformMatrix4fv(shader->uniforms[0].id, 1, GL_FALSE, model.data);
    glUniformMatrix4fv(shader->uniforms[1].id, 1, GL_FALSE, Game->camera.viewProjection.data);
    glUniform4fv(shader->uniforms[2].id, 1, color.data);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture->textureID);
    glUniform1i(shader->uniforms[3].id, 0);


    glBindBuffer(GL_ARRAY_BUFFER, mesh->vertBufferID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBufferID);

    // 1st attribute buffer : vertices
    int vert = glGetAttribLocation(shader->programID, "vertexPosition_modelspace");
    glEnableVertexAttribArray(vert);
    glVertexAttribPointer(vert, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    int normals = glGetAttribLocation(shader->programID, "normals");
    //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(normals);
    glVertexAttribPointer(normals, 3, GL_FLOAT, GL_FALSE, 0 , (void*)(sizeof(vec3) * mesh->vertCount));

    int texcoord = glGetAttribLocation(shader->programID, "in_texcoord");
    glEnableVertexAttribArray(texcoord);
    glVertexAttribPointer(texcoord, 2, GL_FLOAT, GL_FALSE, 0, (void*)(((sizeof(vec3) + sizeof(vec3)) * mesh->vertCount)));

    glDrawElements(GL_TRIANGLES, mesh->indexCount, GL_UNSIGNED_INT, (GLvoid*)0);

    glDisableVertexAttribArray(vert);
    glDisableVertexAttribArray(normals);
    glDisableVertexAttribArray(texcoord);

    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


void DisplayOBJModel(OBJModel* model, Mesh* meshModel, int32 faceNum)
{
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

    /*meshModel->indices[0 + (faceNum * 4)] = model->faces[faceNum].face1.x;
    meshModel->indices[1 + (faceNum * 4)] = model->faces[faceNum].face2.x;
    meshModel->indices[2 + (faceNum * 4)] = model->faces[faceNum].face3.x;*/
    
    meshModel->indices[0] = model->faces[faceNum].face1.x;
    meshModel->indices[1] = model->faces[faceNum].face2.x;
    meshModel->indices[2] = model->faces[faceNum].face3.x;  
    
    //meshModel->indices[3 + (faceNum * 4)] = model->faces[faceNum].face4.x;

    /*for (int i = 0; i < meshModel->indexCount; i++)
    {
        meshModel->indices[0 + (i * 4)] = model->faces[i].face1.x;
        meshModel->indices[1 + (i * 4)] = model->faces[i].face2.x;
        meshModel->indices[2 + (i * 4)] = model->faces[i].face3.x;
    }*/

    //meshModel->
    vec2 mousePos = Input->mousePosNormSigned;
    mousePos.x = mousePos.x * 8;
    mousePos.y = mousePos.y * 4.5f;

    vec3 pos = V3(mousePos.x, mousePos.y,-1.0f);
    vec2 scale = V2(1.0f, 1.0f);
    real32 angle = 0;
    vec4 color = V4(1.0f, 0.1f, 1.0f, 1.0f);
        
    //RenderOBJ()


    //AllocateQuad(meshModel);
    //InitMesh(meshModel);

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


    //glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (GLvoid*)0);

    //glDisableVertexAttribArray(vert);
    /*AllocateQuad(meshModel);
    InitMesh(meshModel);*/

    

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