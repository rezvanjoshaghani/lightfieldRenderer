#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec4 cameraIndex;

out vec2 v_texCoord; //varing
out vec4 v_camIndex; //varing
out vec2 v_uv; //varing
out vec2 v_st; //varing
out int  v_numberOfCameras;

out float s1;
out float s2;
out float t1;
out float t2;


uniform mat4 u_MVP;

uniform vec3 u_cameraPlaneCenter;
uniform vec3 u_cameraPlaneNormal;
uniform int u_cameraPlaneSize;


uniform vec3 u_focalPlaneCenter;
uniform vec3 u_focalPlaneNormal;
uniform int u_focalPlaneSize;


uniform int  u_numberOfCameras;
uniform vec3 u_cameraPosition;
uniform float u_cameraPlaneDist;

uniform float u_imagePlaneSize;


vec3 rayPlaneIntersect(vec3 origin, vec3 dir, vec3 planeOrigin, vec3 planeNormal);
bool pointOnPlaneXY(vec3 point, int planeSize, vec3 planeCenter);
vec2 getUV(vec3 intersectionPoint);
vec2 getST(vec3 intersectionPoint);


void main() {
	v_numberOfCameras = u_numberOfCameras;
	gl_Position = u_MVP * position;

	vec3 targetPoint;
	targetPoint.x =gl_Position.x;
	targetPoint.y = gl_Position.y;
	targetPoint.z = gl_Position.z;

	vec4 cameraPosW;
	cameraPosW = u_MVP * vec4(u_cameraPosition,1);

	vec3 cameraPos;
	cameraPos.x = cameraPosW.x;
	cameraPos.y = cameraPosW.y;
	cameraPos.z = cameraPosW.z;

	v_texCoord.x = texCoord.x;
	v_texCoord.y = texCoord.y;


	vec3 intersectionPoint = rayPlaneIntersect(u_cameraPosition, normalize( targetPoint- u_cameraPosition), u_cameraPlaneCenter, u_cameraPlaneNormal);
	


	if (pointOnPlaneXY(intersectionPoint, u_cameraPlaneSize, u_cameraPlaneCenter)) {
		v_uv=getUV(intersectionPoint);
	}
	else {
		v_uv.x = -1;
		v_uv.y = -1;
	}

	vec3 focalIntersectionPoint = rayPlaneIntersect(u_cameraPosition, normalize(targetPoint - u_cameraPosition), u_focalPlaneCenter, u_focalPlaneNormal);

	if (pointOnPlaneXY(focalIntersectionPoint, u_focalPlaneSize, u_focalPlaneCenter)) {
		v_st = getST(focalIntersectionPoint);
		s1 = floor(v_st.x) / u_focalPlaneSize;
		s2 = ceil(v_st.x) / u_focalPlaneSize;
		t1 = floor(v_st.y) / u_focalPlaneSize;
		t2 = ceil(v_st.y) / u_focalPlaneSize;

		v_st.x= v_st.x / u_focalPlaneSize;
		v_st.y= v_st.y / u_focalPlaneSize;

	}
	else {
		v_st.x = -1;
		v_st.y = -1;
	}
};

vec3 rayPlaneIntersect(vec3 origin, vec3 dir, vec3 planeOrigin, vec3 planeNormal)
{
	float denom = dot(planeNormal, dir);
	if (abs(denom) > 1e-6)
	{
		float t = dot((planeOrigin - origin), planeNormal) / denom;
		if (t >= 0)
		{
			return origin + t * normalize(dir);
		}
	}

	return vec3(-9999.0f);
}

bool pointOnPlaneXY(vec3 point, int planeSize, vec3 planeCenter)
{

	float planeMinX = planeCenter.x - planeSize / 2;
	float planeMinY = planeCenter.y - planeSize / 2;

	float planeMaxX = planeCenter.x + planeSize / 2;
	float planeMaxY = planeCenter.y + planeSize / 2;

	bool xDirWithin = point.x <= planeMaxX && point.x >= planeMinX;
	bool yDirWithin = point.y <= planeMaxY && point.y >= planeMinY;

	return xDirWithin && yDirWithin;
}

vec2 getUV(vec3 intersectionPoint) {
	vec2 uvIdx;
	float relativeXpos = 0;
	float relativeYpos = 0;
	float cameraPlaneMinX = u_cameraPlaneCenter.x - u_cameraPlaneSize / 2;
	float cameraPlaneMinY = u_cameraPlaneCenter.y - u_cameraPlaneSize / 2;

	relativeXpos = intersectionPoint.x - cameraPlaneMinX;
	relativeYpos = intersectionPoint.y - cameraPlaneMinY;

	float subApertureSize = u_cameraPlaneSize / u_numberOfCameras;

	uvIdx.x = relativeXpos / subApertureSize;
	uvIdx.y = relativeYpos / subApertureSize;

	return uvIdx;
}


vec2 getST(vec3 intersectionPoint) {
	vec2 stCoord;

	float relativeXpos = 0;
	float relativeYpos = 0;

	float planeMinX = u_focalPlaneCenter.x - u_focalPlaneSize / 2;
	float planeMinY = u_focalPlaneCenter.y - u_focalPlaneSize / 2;

	relativeXpos = intersectionPoint.x - planeMinX;
	relativeYpos = intersectionPoint.y - planeMinY;

	//stCoord.x = relativeXpos / u_focalPlaneSize;
	//stCoord.y = relativeYpos / u_focalPlaneSize;

	stCoord.x = relativeXpos;
	stCoord.y = relativeYpos;

	return stCoord;
}


#shader fragment
#version 330 core

layout(location = 0) out vec4 color;


in vec2 v_texCoord;
in vec4 v_camIndex;
in vec2 v_uv;
in vec2 v_st;
in int  v_numberOfCameras;


in float s1;
in float s2;
in float t1;
in float t2;

//uniform vec4 u_color;
uniform sampler2D u_texture0;
uniform sampler2D u_texture1;
uniform sampler2D u_texture2;
uniform sampler2D u_texture3;


uniform int tn;
uniform int  u_numberOfCameras;



vec4 bilienarInterpolationFactor(float x, float y, float x1, float x2, float y1, float y2)
{
	float denom = (x2 - x1) * (y2 - y1);
	float b11 = (x2 - x) * (y2 - y) / denom;
	float b21 = (x - x1) * (y2 - y) / denom;
	float b12 = (x2 - x) * (y - y1) / denom;
	float b22 = (x - x1) * (y - y1) / denom;
	return vec4(b11, b12, b21, b22);
}

vec4 getColorOnST(vec2 stCoords)
{
	int cn = u_numberOfCameras;
	//Binlinear interpolation.
	//Define f(x, y) = b11f(Q11) + b12f(Q12) + b21f(Q21)+b22f(Q22)
	//Q11 is floor u floor v;
	//Q12 is floor u ceil v;
	//Q21 is ceil u floor v;
	//Q22 is ceil u ceil v;
	//We want to solve for b11 b12 b21 b22 by linear system.
	float u1 = floor(v_uv.x);
	float u2 = ceil(v_uv.x);
	float v1 = floor(v_uv.y);
	float v2 = ceil(v_uv.y);

	//Get the color of Q11 Q12 Q21 Q22;
	vec4 Q11 = texture(u_texture0, vec2((stCoords.x + u1) / cn, (stCoords.y + v1) / cn));
	vec4 Q12 = texture(u_texture0, vec2((stCoords.x + u1) / cn, (stCoords.y + v2) / cn));
	vec4 Q21 = texture(u_texture0, vec2((stCoords.x + u2) / cn, (stCoords.y + v1) / cn));
	vec4 Q22 = texture(u_texture0, vec2((stCoords.x + u2) / cn, (stCoords.y + v2) / cn));

	//Interpolate the color using bilienar interpolation factors.
	vec4 b = bilienarInterpolationFactor(v_uv.x, v_uv.y, u1, u2, v1, v2);
	float b11 = b.x; 
	float b12 = b.y; 
	float b21 = b.z; 
	float b22 = b.w;
	
	switch (tn) {
		case 1: return Q11;
		case 2: return Q12;
		case 3: return Q21;
		case 4: return Q22;
		case 5: return b11 * Q11 + b12 * Q12 + b21 * Q21 + b22 * Q22;
	}

	return b;

}


//Get the image to use in the array.
float getCameraIndex(float u, float v)
{
	//return u*num_of_cams + v;
	return v * v_numberOfCameras + u;
}


void main() {

	vec2 texpos;

	float u_floor = floor(v_uv.x);
	float u_ceil = ceil(v_uv.x);
	float v_floor = floor(v_uv.y);
	float v_ceil = ceil(v_uv.y);

	color = vec4(0, 0, 1, 1);

	if (v_uv.x == -1 && v_uv.y == -1) {
		color = vec4(0, 0, 0, 1);
	}
	else {
		if (v_st.x == -1 && v_st.y == -1)
		{
			color = vec4(0, 0, 0, 1);
		}
		else {
			

			//Interpolate the color using bilienar interpolation factors.
			vec4 b_st = bilienarInterpolationFactor(v_st.x, v_st.y, s1, s2, t1, t2);
			float b_st11 = b_st.x;
			float b_st12 = b_st.y;
			float b_st21 = b_st.z;
			float b_st22 = b_st.w;

			color = getColorOnST(v_texCoord);

			/*vec4 Q11 = getColorOnST(vec2(s1, t1));
			vec4 Q12 = getColorOnST(vec2(s1, t2));
			vec4 Q21 = getColorOnST(vec2(s2, t1));
			vec4 Q22 = getColorOnST(vec2(s2, t2));
			color = b_st11 * Q11 + b_st12 * Q12 + b_st21 * Q21 + b_st22 * Q22;*/
		}
	}

	//color = texture(u_texture0, v_texCoord);;
};