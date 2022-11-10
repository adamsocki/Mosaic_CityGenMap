
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



void ParseOSM()
{
    DynamicArray<TokenVal> tokens = MakeDynamicArray<TokenVal>(&tokenArena, 100000);    
    DynamicArray<Node> nodeList = MakeDynamicArray<Node>(&nodeArena, 1000);
	

    FileHandle file;

    char* path[] =
	{
	   "data/levelEditor/level0.txt",
	   "data/levelEditor/level1.txt",
	   "data/levelEditor/level2.txt",
	   "data/levelEditor/level3.txt",
	   "data/levelEditor/level4.txt",
	   "data/levelEditor/level5.txt",
	   "data/levelEditor/level6.txt",
	   "data/levelEditor/level7.txt"
	};

    if (OpenFileForRead(path[1], &file, &Game->frameMem))
    {
        TokenVal t = {};
		while (file.offset < file.size)
		{
            char c = ReadChar(&file);
            while (c == ' ' || c == '\n' || c == '\r') {
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

            if (isNegative(c))
            {
               /*  char nextChar = file.data[file.offset];
				if (isDigit(nextChar))
				{
					t.start = (char*)&file.data[file.offset - 1];

				} */
            }
			if (isDoubleQuoteMarks(c))
			{
				
 				t.start = (char*)&file.data[file.offset - 1];
				t.length = 1;
				t.type = TokenType_DoubleQuoteMark;
				goto AddToken;
			}
            while (isDigit(c))
			{

                // TODO: add 
				/* if (t.start == NULL)
				{
					t.type = TokenType_Real32;
					t.start = (char*)&file.data[file.offset - 1];
				}
				t.length++;
				char nextChar = file.data[file.offset];
				//if (!isDigit(nextChar))
				//{
				//	goto AddToken;
				//	break;
				//}                
				else
				{
					c = ReadChar(&file);
					if (isPeriod(c))
					{
						t.length++;
						c = ReadChar(&file);
					}
				} 
				
				if (isDoubleQuoteMarks(c))
				{
					goto AddToken;
					break;
				}
				
				
				*/
			}
			while (isLetter(c))
			{
				if (t.start == NULL)
				{
					t.type = TokenType_Identifier;
					t.start = (char*)&file.data[file.offset - 1];
				}
			}

        AddToken:
            PushBack(&tokens, t);
        Advance:
            int32 baba = 0;
        }
    }

}