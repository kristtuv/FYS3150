#ifndef VEC3_H
#define VEC3_H

class vec3 {
public:
	double components[3];
	vec3();

	double lengthSquared();
	double length();
	double &operator()(int index){return components[index];}
	double &operator[](int index){return components[index];}
	vec3 &operator-=(vec3 rhs); //Componentwise subtraction with vector

};

inline vec3 operator-(vec3 lhs, vec3 rhs){
	lhs -= rhs;
	return lhs;
}
#endif //VEC3_H