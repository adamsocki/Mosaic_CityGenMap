
bool isLetter(char c)
{
	return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');	
}
bool isSpaceWithinLetters(char c)
{
	return true;
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
bool isLeftAngleBracket(char c)
{
    return c == '<';
}
bool isRightAngleBracket(char c)
{
    return c == '>';
}
bool isEquals(char c)
{
    return c == '=';
}
bool isforwardSlash(char c)
{
    return c == '/';
}
bool isDoubleQuoteMarks(char c)
{
    return c == '"';
}
bool isNegative(char c)
{
    return c == '-';
}
bool isQuestionMark(char c)
{
	return c == '?';
}


void ParseOSM()
{
    DynamicArray<TokenVal> tokens = MakeDynamicArray<TokenVal>(&tokenArena, 100000);
	 
    DynamicArray<Bound> boundList = MakeDynamicArray<Bound>(&boundArena, 1000); 
    DynamicArray<Node> nodeList = MakeDynamicArray<Node>(&nodeArena, 1000);

    FileHandle file;

    char* path[] =
	{
	   "data/map.osm",
	   "data/levelEditor/level1.txt",
	   "data/levelEditor/level2.txt",
	   "data/levelEditor/level3.txt",
	   "data/levelEditor/level4.txt",
	   "data/levelEditor/level5.txt",
	   "data/levelEditor/level6.txt",
	   "data/levelEditor/level7.txt"
	};

    if (OpenFileForRead(path[0], &file, &Game->frameMem))
    {
        TokenVal t = {};
		//bool readingText = false;
		//bool readingFloat = false;

		while (file.offset < file.size)
		{
			Print("val: %d", file.offset);
			t = {};
            char c = ReadChar(&file);
            while (c == ' ' || c == '\n' || c == '\r') {
				/* if (!readingText || !readingFloat)
				{
					
				} */
				goto Advance;
			}
            if (isLeftAngleBracket(c))
            {
                t.start = (char*)&file.data[file.offset - 1];
				t.length = 1;
				t.type = TokenType_LeftAngleBracket;
				goto AddToken;
            }
            if (isRightAngleBracket(c))
            {
                t.start = (char*)&file.data[file.offset - 1];
				t.length = 1;
				t.type = TokenType_RightAngleBracket;
				goto AddToken;
            }
			if (isforwardSlash(c))
			{
				t.start = (char*)&file.data[file.offset - 1];
				t.length = 1;
				t.type = TokenType_ForwardSlash;
				goto AddToken;
			}
            if (isNegative(c))
            {
                char nextChar = file.data[file.offset];
				if (isDigit(nextChar))
				{
					t.start = (char*)&file.data[file.offset - 1];
					// need something here...
				}
            }
			if (isDoubleQuoteMarks(c))
			{	
				if (t.start == NULL)
				{
					t.start = (char*)&file.data[file.offset];
					t.type = TokenType_DoubleQuoteMark;
					t.length = 1;
					PushBack(&tokens, t);
				}
				c = ReadChar(&file);
				while (!isDoubleQuoteMarks(c))
				{
					if (t.start == NULL)
					{
						t.start = (char*)&file.data[file.offset];
						t.type = TokenType_Value;
					}
					t.length++;
					c = ReadChar(&file);
				}
				goto AddToken;
			}
            /* while (isDigit(c))
			{
				if (t.start == NULL)
				{
					t.type = TokenType_Real32;
					t.start = (char*)&file.data[file.offset - 1];
				}
				t.length++;
				char nextChar = file.data[file.offset];
				if (!isLetter(nextChar))
				{
					char nextNextChar = file.data[file.offset + 1];
					if (!isDoubleQuoteMarks(nextNextChar))
					{
						c = ReadChar(&file);
					}
					else
					{
						goto AddToken;
						break;
					}
				}
			} */
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
					
					/* char nextNextChar = file.data[file.offset + 1];
					if (!isDoubleQuoteMarks(nextNextChar))
					{
						c = ReadChar(&file);
					}
					else
					{
						 
					*/
				}
				else
				{
					c = ReadChar(&file);
				}
			}
			if (isQuestionMark(c))
			{
				t.start = (char*)&file.data[file.offset - 1];
				t.length = 1;
				t.type = TokenType_QuestionMark;
				goto AddToken;
			}
        AddToken:
            PushBack(&tokens, t);
        Advance:
            int32 baba = 0;
        }
		CloseFile(&file);
    }
	
	// READ DEM TOKES
	int32 tokenIndex = 0;

	while(tokenIndex < tokens.count)
	{
		TokenVal t = tokens[tokenIndex];

		if (t.type == TokenType_LeftAngleBracket)
		{
			tokenIndex++;
			t = tokens[tokenIndex];
			if (t.type == TokenType_QuestionMark)
			{	// skips first line with XML Label
				tokenIndex++;
				t = tokens[tokenIndex];

				while(t.type != TokenType_QuestionMark)
				{
					tokenIndex++;
					t = tokens[tokenIndex];
				}
				tokenIndex++;
				t = tokens[tokenIndex];
			}
			else
			{ 
				if (t.type == TokenType_Identifier)
				{
					if (strncmp(t.start, "bounds", t.length) == 0)
					{	// start of current bounds
						tokenIndex++;
						t = tokens[tokenIndex];

						Bound b = {};

						if (strncmp(t.start, "minlat", t.length) == 0)
						{
							tokenIndex += 2;
							b.minlat = strtoll(t.start,NULL, 10);
							tokenIndex++;
							t = tokens[tokenIndex];
						}
						if (strncmp(t.start, "minlon", t.length) == 0)
						{
tokenIndex += 2;
b.minlat = strtoll(t.start, NULL, 10);
tokenIndex++;
t = tokens[tokenIndex];
						}
						if (strncmp(t.start, "maxlat", t.length) == 0)
						{
							tokenIndex += 2;
							b.minlat = strtoll(t.start, NULL, 10);
							tokenIndex++;
							t = tokens[tokenIndex];
						}
						if (strncmp(t.start, "maxlon", t.length) == 0)
						{
							tokenIndex += 2;
							b.minlat = strtoll(t.start, NULL, 10);
							tokenIndex++;
							t = tokens[tokenIndex];
						}

						if (t.type == TokenType_ForwardSlash)
						{
							tokenIndex++;
							t = tokens[tokenIndex];
						}
						if (t.type == TokenType_RightAngleBracket)
						{
							tokenIndex++;
							t = tokens[tokenIndex];
						}
						PushBack(&boundList, b);
					}
					if (strncmp(t.start, "node", t.length) == 0)
					{
						tokenIndex++;
						t = tokens[tokenIndex];

						Node n = {};
						n.tagList = MakeDynamicArray<Tag>(&tagArena, 500);

						while (t.type != TokenType_ForwardSlash)
						{
							if (strncmp(t.start, "id", t.length) == 0)
							{
								tokenIndex++;
								t = tokens[tokenIndex];
								if (t.type = TokenType_EqualSymb)
								{

								}
							}
							if (strncmp(t.start, "visible", t.length) == 0)
							{

							}
							if (strncmp(t.start, "version", t.length) == 0)
							{

							}
							if (strncmp(t.start, "changeset", t.length) == 0)
							{

							}
							if (strncmp(t.start, "timestamp", t.length) == 0)
							{

							}
							if (strncmp(t.start, "user", t.length) == 0)
							{

							}
							if (strncmp(t.start, "uid", t.length) == 0)
							{

							}
							if (strncmp(t.start, "lat", t.length) == 0)
							{

							}
							if (strncmp(t.start, "lon", t.length) == 0)
							{

							}
						}
						PushBack(&nodeList, n);
					}

				}





			}





		}
		else
		{
			tokenIndex++;
			t = tokens[tokenIndex];
		}




		/* while (t.type == TokenType_LeftAngleBracket)
		{
			tokenIndex++;
			t = tokens[tokenIndex];

			if (t.type == TokenType_QuestionMark)
			{
				tokenIndex++;
				t = tokens[tokenIndex];
			}

			if (t.type == TokenType_Identifier)
			{
				if (strncmp(t.start, "xml", t.length) == 0)
				{	// start of XML doc
					tokenIndex++;

				}
				if (strncmp(t.start, "way", t.length) == 0)
				{

				}
				if (strncmp(t.start, "osm", t.length) == 0)
				{
					// continue until /> ?

				}
			}


		}
	 */
	}
}

