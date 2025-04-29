int	clamp(int num, int max, int min)
{
	if (num <= min)
		return (min);
	if (num >= max)
		return (max);
	return (num);
}

int	lerp(int a, int b, float t)
{
	return (a * (1 - t) + b * t);
}
