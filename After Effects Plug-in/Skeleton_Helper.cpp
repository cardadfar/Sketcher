#include "Skeleton_Helper.h"
#include <assert.h>
#include <windows.h>
#include <glew.h>
#include <glut.h>
#include <glfw3.h>
#include <iostream>
#include <vector>
#include <string>
#include <math.h>

static PF_Pixel *getPixelXY(PF_ParamDef checkout, int x, int y) {
    return (PF_Pixel*)((char*)(checkout.u.ld).data + (y * (checkout.u.ld).rowbytes) + (x * sizeof(PF_Pixel)));
}

static void setPixelXY(PF_EffectWorld *def, int x , int y){

    PF_Pixel *p = (PF_Pixel*)((char*)def->data + (y * def->rowbytes) + (x * sizeof(PF_Pixel)));
    p->red = (A_u_char)255.0;
    p->green = (A_u_char)255.0;
    p->blue = (A_u_char)255.0;
    p->alpha = (A_u_char)255.0;
    return;
    
}

static float dist(float x1, float y1, float x2, float y2) {

    float x = (x2 - x1) * (x2 - x1);
    float y = (y2 - y1) * (y2 - y1);

    return sqrt(x + y);

}

static bool gap(float x1, float y1, float x2, float y2, float wth, float hgt, PF_Pixel inp, PF_ParamDef checkout) {

    float range = 10.0;

    float x = (x1 + x2) / 2.0;
    float y = (y1 + y2) / 2.0;

    x = (x + 1) * (wth / 2.0);
    y = (y + 1) * (hgt / 2.0);

    PF_Pixel *p = getPixelXY( checkout, x, y );

    bool r = (abs(p->red - inp.red)) < range;
    bool g = (abs(p->green - inp.green)) < range;
    bool b = (abs(p->blue - inp.blue)) < range;

    return (r && g && b);

}

static bool dir(float x1, float y1, float x2, float y2, float x3, float y3, float range) {

    float dx1 = (x2 - x1);
    float dy1 = (y2 - y1);

    float dx2 = (x3 - x2);
    float dy2 = (y3 - y2);


    float dir1;
    float dir2;

    if( abs(x2 - x1) < 0.0001 ) {

        dir1 = 90.0;

    }
    else {

        dir1 = atan(dy1 / dx1) * (180.0 / 3.14);

    }

    if( abs(x3 - x2) < 0.0001 ) {

        dir2 = 90.0;

    }
    else {

        dir2 = atan(dy2 / dx2) * (180.0 / 3.14);

    }

    bool close = (abs(dir1 - dir2) < range);
    if(!close) {

        if( dir1 > (360.0 - range)) {

            close = ( dir2 < (range - 360.0 + dir1) );

        }

        else if( dir2 > (360.0 - range)) {

            close = ( dir1 < (range - 360.0 + dir2) );

        }

    }

    return close;

}


static GLFWwindow *glewSetup(float l_width, float l_height) {

    glfwInit();

    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);  
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); 

    GLFWwindow* offscreen_context = glfwCreateWindow(l_width, l_height, "", NULL, NULL);

    glfwMakeContextCurrent(offscreen_context);

    glewExperimental = GL_TRUE;

    return offscreen_context;

}

static void generateCanvas(float *points, 
                           float l_width, 
                           float l_height, 
                           PF_EffectWorld l_world, 
                           PF_Pixel8 *l_data,
                           PF_Pixel color, 
                           GLFWwindow *offscreen_context,
                           int count,
                           int step,
                           int mode) {

        
        unsigned int fbo;
        glGenFramebuffers(1, &fbo);
        glBindFramebuffer(GL_FRAMEBUFFER, fbo);
        
        unsigned int renderTex;
        glGenTextures(1, &renderTex);
        glBindTexture(GL_TEXTURE_2D, renderTex);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8 ,l_width, l_height, 0, GL_BGR, GL_UNSIGNED_BYTE, l_data);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,  GL_TEXTURE_2D, renderTex, 0);

        unsigned int vbo;
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, count * 2 * sizeof(float), points, GL_STATIC_DRAW);

        unsigned int vao;
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, NULL);

        const char* vertex_shader =
        "#version 330\n"
        "in vec2 vp;"
        "void main() {"
        "  gl_Position = vec4(vp, 1.0, 1.0);"
        "}";

        std::string r = std::to_string( (color.red / 255.0) );
        std::string g = std::to_string( (color.green / 255.0) );
        std::string b = std::to_string( (color.blue / 255.0) );
        std::string a = std::to_string( (color.alpha / 255.0) );

        std::string f_s =
        "#version 400\n"
        "out vec4 frag_colour;"
        "void main() {"
        "  frag_colour = vec4(" + b + ", " + g + ", " + r + ", " + a + ");"
        "}";

        const char* fragment_shader  = f_s.c_str();

        unsigned int vs;
        vs = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vs, 1, &vertex_shader, NULL);
        glCompileShader(vs);

        unsigned int fs;
        fs = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fs, 1, &fragment_shader, NULL);
        glCompileShader(fs);


        unsigned int shader_programme;
        shader_programme = glCreateProgram();
        glAttachShader(shader_programme, fs);
        glAttachShader(shader_programme, vs);
        glLinkProgram(shader_programme);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(shader_programme);
        
        glBindVertexArray(vao);

        for(int i = 0; i < count / step; i++) {

            switch (mode) {

                case MODE_LINES:
                    glDrawArrays(GL_LINE_STRIP, i * step, step);
                    break;

                case MODE_LINESLOOP:
                    glDrawArrays(GL_LINE_LOOP, i * step, step);
                    break;

                case MODE_POLYGONS:
                    glDrawArrays(GL_TRIANGLE_FAN, i * step, step);
                    break;

                case MODE_LINES_POLYGONS:
                    if( i % 2 == 0)
                        glDrawArrays(GL_TRIANGLE_FAN, i * step, step);
                    else
                        glDrawArrays(GL_LINE_STRIP, i * step, step);
                    break;

                case MODE_POINTS:
                    glDrawArrays(GL_POINTS, i * step, step);
                    break;

            }

        }

        
        glReadPixels(0, 0, l_width, l_height, GL_ABGR_EXT, GL_UNSIGNED_BYTE, (void*)(l_world.data));


        //delete all buffers
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glDeleteFramebuffers(1, &fbo);

        glBindTexture(GL_TEXTURE_2D, 0);
        glDeleteTextures(1, &renderTex);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glDeleteBuffers(1, &vbo);

        glBindVertexArray(0);
        glDeleteVertexArrays(1, &vao);

        glDeleteShader(vs);
        glDeleteShader(fs);

        glUseProgram(0);
        glDeleteProgram(shader_programme);
    
        glfwMakeContextCurrent(NULL);
        glfwDestroyWindow(offscreen_context);


}
