


bool isLetter(char c)
{
	return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');	
}
bool isDigit(char c)
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

void LoadModelParse()
{


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
                char nextChar = file.data[file.offset - 1 + t.length];
                if (isPeriod(c))
                {
                    c = ReadChar(&file);
                }
                else if (isSpace(c))
                {
                    goto AddToken;
                    break;
                }
            }

        
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

                OBJVertex objVertex = {};

                objVertex.vectorArray = (vec3*)malloc(sizeof(vec3) * 1000);
				memset(objVertex.vectorArray, 0, sizeof(vec3) * 1000);
                objVertex.vertexCount = 0;

                vec3 vertexValue;
               

                if (strncmp(t.start, "v", t.length) == 0)
                {
                    bool continueVertexCollection = true;

                    if (continueVertexCollection)
                    {
                        objVertexArray[objVertex.vertexCount].x = strtod(t.start, NULL);
                        tokenIndex++;
					    t = tokens[tokenIndex];
                        objVertexArray[objVertex.vertexCount].y = strtod(t.start, NULL);
                        tokenIndex++;
					    t = tokens[tokenIndex];
                        objVertexArray[objVertex.vertexCount].z = strtod(t.start, NULL);
                        tokenIndex++;
					    t = tokens[tokenIndex];
    
                        if (strncmp(t.start, "v", t.length) != 0)
                        {
                            continueVertexCollection = false;
                        }
                    }
                    

                }

                if (strncmp(t.start, "vt", t.length) == 0)
                {
                    boo
                    tokenIndex++;
                    t = tokens[tokenIndex];
                

                
                }

                if (strncmp(t.start, "vn", t.length) == 0)
                {
                    tokenIndex++;
                    t = tokens[tokenIndex];



                }
               
                if (strncmp(t.start, "f", t.length) == 0)
                {
                    tokenIndex++;
                    t = tokens[tokenIndex];



                }
            }
        }
    }

}