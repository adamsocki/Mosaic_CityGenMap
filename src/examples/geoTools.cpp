
#define _ETC_MATH_H


real32 originShift = _PI * 6378137.0f;

// Convert WGS85 to XY in Spherical Mercator EPSG:900013
vec2 convertLatLonToMeters(real32 lat, real32 lon)
{
	vec2 returnValue = V2(0);
	real32 meter_X;
	real32 meter_Z;

	meter_Z = (lon * originShift) / 100.0f;
	meter_X = logf(tanf((90.0f + lat) * _PI / 360.0f)) / (_PI / 180.0f);
	meter_X = meter_X * originShift / 180.f;

	returnValue = V2(meter_X, meter_Z);

	return returnValue;
}

// set a sceneBox

// BBox convert from lat to Meter

void BBoxLatLonToMeter(BBox* bbox)
{
	vec2 bottomLeft = convertLatLonToMeters(bbox->bottom, bbox->left);
	vec2 topRight = convertLatLonToMeters(bbox->top, bbox->right);

	bbox->meterBottom = bottomLeft.x;
	bbox->meterLeft   = bottomLeft.y;
	bbox->meterTop    = topRight.x;
	bbox->meterRight  = topRight.y;
}

void BBoxCalculateSizeInMeters(BBox* bbox)
{
	bbox->lengthTop = bbox->meterTop - bbox->meterBottom;
	bbox->lengthRight = bbox->meterRight - bbox->meterLeft;
}

void setBBox(BBox* bbox, Bound bound)
{
	bbox->left   = bound.minlon;
	bbox->right  = bound.maxlon;
	bbox->top    = bound.maxlat;
	bbox->bottom = bound.minlat;
}

