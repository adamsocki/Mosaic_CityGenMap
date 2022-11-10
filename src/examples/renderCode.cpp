

void RenderRoadwayGrid(vec2 startingPos, vec2 dim, vec2 gap, real32 laneWidth, vec4 color)
{

	for (int i = 0; i < dim.x; i++)
	{
		vec2 posLineStart = V2(startingPos.x + (i * gap.x), startingPos.y);
		vec2 posLineEnd = V2(posLineStart.x, posLineStart.y + dim.y);
		DrawLine(posLineStart, posLineEnd, laneWidth, color);
	}

	for (int i = 0; i < dim.y; i++)
	{
		vec2 posLineStart = V2(startingPos.x, startingPos.y + (i * gap.y));
		vec2 posLineEnd = V2(posLineStart.x + dim.x, posLineStart.y);
		DrawLine(posLineStart, posLineEnd, laneWidth, color);
	}


	

}


