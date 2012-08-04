/* 
 * File:   GLQuaternion.h
 * Author: qfeuille
 *
 * Created on 04 August 2012, 19:40
 */

#ifndef GLQUATERNION_H
#define	GLQUATERNION_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//Inline for Efficiency + too much effort to take out of class
template<typename T>
class GL_Quaternion {
    T s;
    glm::vec3 v;
public:


    GL_Quaternion(glm::vec3 axis, double angle) {
        axis=glm::normalize(axis);
        v =  (float) sin(angle / 2)* axis;
        s = cos(angle / 2);
    }

    GL_Quaternion() {};
    
    glm::vec3 rotate (const glm::vec3 & w){
        return w+2.0f*glm::cross(v, glm::cross(v,w)+s*w);
    }

    void normalise() {
        double TOLERANCE = 0.0001;
        double mag = sqrt(s * s + glm::dot(v,v));
        if (mag != 0 && fabs(mag - 1) > TOLERANCE) {
            s = s / mag;
            v = v *(float) (1 / mag);
        }
    }

    GL_Quaternion getConjugate() {
        GL_Quaternion ret(s, v*-1.0f);
        return ret;
    };
		
glm::mat4x4 getMatrix (){
	double x2 = v.x * v.x;
	double y2 = v.y * v.y;
	double z2 = v.z * v.z;
	double xy = v.x * v.y;
	double xz = v.x * v.z;
	double yz = v.y * v.z;
	double wx = s * v.x;
	double wy = s * v.y;
	double wz = s * v.z;
 
	return glm::mat4x4 (1.0f - 2.0f * (y2 + z2), 2.0f * (xy - wz), 2.0f * (xz + wy), 0.0f,
			2.0f * (xy + wz), 1.0f - 2.0f * (x2 + z2), 2.0f * (yz - wx), 0.0f,
			2.0f * (xz - wy), 2.0f * (yz + wx), 1.0f - 2.0f * (x2 + y2), 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f);
	}

					
				
		GL_Quaternion operator *(const GL_Quaternion &param);
               

};
template<typename T>
inline GL_Quaternion<T> GL_Quaternion<T>::operator *(const GL_Quaternion<T> &param){
	GL_Quaternion<T> temp;
	temp.s=s*param.s-(glm::dot(v,param.v));
	temp.v=(v*param.s)+(param.v*s)+(glm::cross(v,param.v));
return temp;}

#endif	/* GLQUATERNION_H */

