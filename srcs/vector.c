#include <vector.h>

t_vec3	sum_vec3(const t_vec3 a, const t_vec3 b)
{
	return ((t_vec3) {a.x + b.x, a.y + b.y, a.z + b.z});
}
t_vec2	sum_vec2(const t_vec2 a, const t_vec2 b)
{
	return ((t_vec2) {a.x + b.x, a.y + b.y});
}
t_vec3 mult_vec3i(const t_vec3 a, const int b)
{
	return ((t_vec3) {a.x * b, a.y * b, a.z * b});
}
