int	clamp(const int num, const int min, const int max)
{
	if (num <= min)
		return (min);
	if (num >= max)
		return (max);
	return (num);
}

inline float	clampf(float num, float min, float max)
{
	if (num <= min)
		return (min);
	if (num >= max)
		return (max);
	return (num);
}

int	lerp(const int a, const int b, const float t)
{
	if (t >= 1)
		return (b);
	if (t <= 0)
		return (a);
	return (a * (1 - t) + b * t);
}
