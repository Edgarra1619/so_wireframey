int	clamp(int num, int min, int max)
{
	if (num <= min)
		return (min);
	if (num >= max)
		return (max);
	return (num);
}

float	clampf(float num, float min, float max)
{
	if (num <= min)
		return (min);
	if (num >= max)
		return (max);
	return (num);
}

int	lerp(int a, int b, float t)
{
	t = clampf(t, 0, 1);
	return (a * (1 - t) + b * t);
}
