#include"Header.h"

CGPoint MakePoint(float x, float y)
{
	CGPoint pos;
	pos.x = x;
	pos.y = y;
	return pos;
}

VectorInfo Distance(CGPoint p1, CGPoint p2)
{
	VectorInfo v1;
	v1.vector = MakePoint(p2.x - p1.x, p2.y - p1.y);
	v1.distance = sqrtf((v1.vector.x * v1.vector.x)
		+ (v1.vector.y * v1.vector.y)); 
	return v1;
}

int RandomRange(int min, int max)
{
	return rand() % (max-min) + min;
}

float Clamp(float value, float min, float max)
{
	if(value < min ) value = min;
	if(value > max ) value = max;
	return value;
}

CGPoint IsoTo2D(CGPoint pos)
{
	CGPoint tpos = MakePoint(0.f, 0.f);
	tpos.x = (2 * pos.y + pos.x) / 2;
	tpos.y = (2 * pos.y - pos.x) / 2;
	return tpos;
}
CGPoint twoDToIso(CGPoint pos)
{
	CGPoint tpos = MakePoint(0.f, 0.f);
	tpos.x = pos.x - pos.y;
	tpos.y = (pos.x + pos.y) / 2;
	return tpos;
}

