/* 
 * File:   GLResources.cpp
 * Author: qfeuille
 *
 * Created on 31 July 2012, 00:51
 */


#include "GLResources.h"
#include <fstream>
#include <streambuf>
#include <string>


const int textureunitconstant (const int textureunit){
    switch (textureunit) {
           case 0:
return GL_TEXTURE0;
 case 1:
return GL_TEXTURE1;
 case 2:
return GL_TEXTURE2;
 case 3:
return GL_TEXTURE3;
 case 4:
return GL_TEXTURE4;
 case 5:
return GL_TEXTURE5;
 case 6:
return GL_TEXTURE6;
 case 7:
return GL_TEXTURE7;
 case 8:
return GL_TEXTURE8;
 case 9:
return GL_TEXTURE9;
 case 10:
return GL_TEXTURE10;
 case 11:
return GL_TEXTURE11;
 case 12:
return GL_TEXTURE12;
 case 13:
return GL_TEXTURE13;
 case 14:
return GL_TEXTURE14;
 case 15:
return GL_TEXTURE15;
 case 16:
return GL_TEXTURE16;
 case 17:
return GL_TEXTURE17;
 case 18:
return GL_TEXTURE18;
 case 19:
return GL_TEXTURE19;
 case 20:
return GL_TEXTURE20;
 case 21:
return GL_TEXTURE21;
 case 22:
return GL_TEXTURE22;
 case 23:
return GL_TEXTURE23;
 case 24:
return GL_TEXTURE24;
 case 25:
return GL_TEXTURE25;
 case 26:
return GL_TEXTURE26;
 case 27:
return GL_TEXTURE27;
 case 28:
return GL_TEXTURE28;
 case 29:
return GL_TEXTURE29;
 case 30:
return GL_TEXTURE30;
 case 31:
return GL_TEXTURE31;  
        default:
            std::cerr<<"Texture unit specified too large\n";
            return GL_TEXTURE0;
    }
}

std::string fileContents (const char* filename) {
    std::ifstream file(filename, std::ifstream::in);
    return std::string ((std::istreambuf_iterator<char>(file)),
                 std::istreambuf_iterator<char>());
}

void showInfoLog(
        GLuint object,
        PFNGLGETSHADERIVPROC glGet__iv,
        PFNGLGETSHADERINFOLOGPROC glGet__InfoLog
        ) {
    GLint log_length;
    char *log;

    glGet__iv(object, GL_INFO_LOG_LENGTH, &log_length);
    log = new char (log_length);
    glGet__InfoLog(object, log_length, NULL, log);
    std::cerr<< log;
    delete log;
}



int GLResources::makevBuffer (GLenum target,
    const void *buffer_data,
    GLsizei buffer_size)
{
    GLuint buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(target, buffer);
    glBufferData(target, buffer_size, buffer_data, GL_STATIC_DRAW);
    vbuffers.push_back(buffer); 
    return vbuffers.size()-1;
 }

int GLResources::makeeBuffer (GLenum target,
    const void *buffer_data,
    GLsizei buffer_size)
{
    GLuint buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(target, buffer);
    glBufferData(target, buffer_size, buffer_data, GL_STATIC_DRAW);
    ebuffers.push_back(buffer); 
    return ebuffers.size()-1;
 }


int GLResources::makeShader(GLenum type, const char *filename)
{
   
    std::string source = fileContents(filename);
    GLint length = source.size();
    const GLchar* text = source.c_str();
    GLuint shader;
    GLint shader_ok;

    if (source.size()== 0)
        return 0;
    shader = glCreateShader(type);
    glShaderSource(shader, 1, &text, &length);
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &shader_ok);
    if (!shader_ok) {
        fprintf(stderr, "Failed to compile %s:\n", filename);
        showInfoLog(shader, glGetShaderiv, glGetShaderInfoLog);
        glDeleteShader(shader);
        return 0;
    }
    shaders.push_back(shader);
    return shaders.size();
}
int GLResources::makeProgramBody(){
    GLint program_ok;
    glLinkProgram(programs.back());
    glGetProgramiv(programs.back(), GL_LINK_STATUS, &program_ok);
    if (!program_ok) {
        std::cerr << "Failed to link shader program:\n";
        showInfoLog(programs.back(), glGetProgramiv, glGetProgramInfoLog);
        glDeleteProgram(programs.back());
        programs.erase(programs.end());
        return -1;
    }
    return programs.size()-1;
}

int GLResources::makeProgram(std::vector<GLuint> inshaders)
{
    programs.push_back(glCreateProgram());
    for (GLuint shader : inshaders )
        glAttachShader(programs.back(), shader);
    return makeProgramBody();
    
}

int GLResources::makeProgram(std::vector<int> inshaders)
{
    GLint program_ok;

    programs.push_back(glCreateProgram());
    for (int shaderID : inshaders )
        glAttachShader(programs.back(), shaders[shaderID]);
    return makeProgramBody();
}

int GLResources::makeProgram()
{
    GLint program_ok=GL_FALSE;
    programs.push_back(glCreateProgram());
    for (GLuint shader : shaders )
        glAttachShader(programs.back(), shader);
    return makeProgramBody();
}

int GLResources::make2DTexture(const int textureunit){
    GLuint texture;
    glActiveTexture(textureunitconstant(textureunit));
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    textures.push_back(texture);
    return textures.size()-1;
}

GLuint GLResources::bindAttribute(const char* name, int programID){
    GLuint attr = glGetAttribLocation(programs[programID],name);
        if (attr == -1)
            std::cerr<<"Failed to bind attribute "<<name<<std::endl;
    return attr;
} 

GLuint GLResources::bindUniform(const char* name, int programID){
    GLuint uni = glGetUniformLocation(programs[programID],name);
        if (uni == -1)
            std::cerr<<"Failed to bind uniform "<<name<<std::endl;
    return uni;
} 