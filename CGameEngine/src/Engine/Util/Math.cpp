#include "Math.h"

glm::mat4 ENGINE::UTIL::shearMatrix(float a, float b, float c, float d, float e, float f)
{

	glm::mat4 res = glm::mat4(0);

	res[0][0] = 1;
	res[1][1] = 1;
	res[2][2] = 1;
	res[3][3] = 1;

	res[0][1] = a;
	res[0][2] = b;

	res[1][0] = c;
	res[1][2] = d;

	res[2][0] = e;
	res[2][1] = f;


	return res;
}
