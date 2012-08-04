/* 
 * File:   Physics.h
 * Author: qfeuille
 *
 * Created on 04 August 2012, 19:47
 */

#ifndef PHYSICS_H
#define	PHYSICS_H

template<typename T>
class NoAcceleration {
  std::vector <T> values;
  std::vector <T> velocities;

public:
    T getValue (int ID) {return values [ID];}
    void setValue (int ID, T value){values[ID]=value;}
    T getVel (int ID) {return velocities [ID];}
    void setVel (int ID, T vel){velocities[ID]=vel;}
    void addtoVel (int ID, T addvel){velocities[ID]+=addvel;}
    int addCoordinate (T initialvalue, T initialvelocity); 
    void update (T timestep);
    int getNumCoordinates (){return values.size();}
};


template<typename T>
void NoAcceleration<T>::update (T timeElapsed){
    for (typename std::vector<T>::size_type i = 0; i != values.size(); i++) {
        values[i]+=timeElapsed*velocities[i];
    }
}

template<typename T>
int NoAcceleration<T>::addCoordinate(T initialvalue, T initialvelocity)
{values.push_back(initialvalue);
velocities.push_back(initialvelocity);
return values.size()-1;
}

#endif	/* PHYSICS_H */

