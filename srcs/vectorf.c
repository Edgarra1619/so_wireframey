#include <vector.h>

t_vecf3	sum_vecf3(const t_vecf3 a, const t_vecf3 b)
{
	return ((t_vecf3) {a.x + b.x, a.y + b.y, a.z + b.z});
}

t_vecf2	sum_vecf2(const t_vecf2 a, const t_vecf2 b)
{
	return ((t_vecf2) {a.x + b.x, a.y + b.y});
}

t_vecf3 mult_vecf3i(const t_vecf3 a, const float b)
{
	return ((t_vecf3) {a.x * b, a.y * b, a.z * b});
}
