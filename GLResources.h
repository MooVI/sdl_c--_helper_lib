/* 
 * File:   GLResources.h
 * Author: qfeuille
 *
 * Created on 31 July 2012, 00:49
 */

#ifndef GLRESOURCES_H
#define	GLRESOURCES_H
#include <GL/glew.h>
#include <glm/glm.hpp>

#include<vector>
#include <iostream>

struct Material {
        glm::vec4 colour; 
        glm::vec4 specular; 
        GLfloat shininess;      
    };

class GLResources {
    //Store vertex, element buffers, textures, and program IDs
   std::vector<GLint> vbuffers, ebuffers;
   std::vector<GLint> textures;
   std::vector<GLint> shaders;
   std::vector<GLint> programs;
   //Helper Function for makeProgram
   int makeProgramBody ();
public:
    //Make functions return index of storage in vector
    int makevBuffer (GLenum target,
    const void *buffer_data,
    GLsizei buffer_size);
    int makeeBuffer (GLenum target,
    const void *buffer_data,
    GLsizei buffer_size);
    int makeShader(GLenum type, const char* filename);
    //Make program using shaders with given IDs
    int makeProgram(std::vector<GLuint> inshaders);
    //Make program using shaders with given indices
    int makeProgram(std::vector<int> inshaders);
    //Make program using all shaders in memory (most common usage)
    int makeProgram ();
    //Make 2D texture, leaving it bound ready to be filled by image etc.
    int make2DTexture (int textureunit=0);
    // Given an index, get functions return ID
    GLuint getProgram (const int ID=0){return programs [ID];}
    GLuint getvBuffer (const int ID=0){return vbuffers [ID];}
    GLuint geteBuffer (const int ID=0){return ebuffers [ID];}
    GLuint getTexture (const int ID=0){return textures [ID];}
    // Given an ID, add it to storage
    int addTexture(const GLuint texture) {
        textures.push_back(texture);
        return textures.size() - 1;
    }
    int addProgram (const GLuint program){
        programs.push_back(program);
        return textures.size() - 1;
    }
    GLuint bindAttribute (const char * name, int programID=0);
    GLuint bindUniform(const char* name, int programID=0);
};

#endif	/* GLRESOURCES_H */

