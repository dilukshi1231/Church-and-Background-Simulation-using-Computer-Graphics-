#include <GL/glut.h>
#include <math.h>
#include <SOIL2.h>
#include <stdio.h>

constexpr float PI = 3.14159265358979323846;
float an = 0;
float increment = 0.4;
int width;
int height;
static float dRot1 = 0;
static float dRot2 = 0;
float doorAngle = 0.0f;
float doorSpeed = 1.0f;
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

int gridOn = 0;
int axesOn = 0;


//Texture codes
GLuint tex;
GLuint tex1;
GLuint tex2;
GLuint tex3;
GLuint tex4;
GLuint tex5;
GLuint tex6;
GLuint tex7;
GLuint textureImage2;
GLuint window;
GLuint creamTexture;
GLuint door;
GLuint cone;
GLuint textureImage3;
GLuint roof1;
GLuint block;
GLuint bench;
GLuint grass;
GLuint glass;
GLuint nicewall;
GLuint foundation;
GLuint stones;


void loadTexture() {
    tex = SOIL_load_OGL_texture(
        "wallCream.jpg",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y
    );
    tex1 = SOIL_load_OGL_texture(
        "ground.jpg",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y
    );

    tex2 = SOIL_load_OGL_texture(
        "banner.jpg",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y
    );

    tex3 = SOIL_load_OGL_texture(
        "staircase.jpg",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y
    );

    tex4 = SOIL_load_OGL_texture(
        "sky.jpg",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y
    );
    textureImage2 = SOIL_load_OGL_texture(
        "sky.jpg",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y
    );
    tex5 = SOIL_load_OGL_texture(
        "roof.jpg",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y
    );
    tex6 = SOIL_load_OGL_texture(
        "brick.jpg",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y
    );

    window = SOIL_load_OGL_texture(
        "brick.jpg",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y
    );

    creamTexture = SOIL_load_OGL_texture(
        "creamtexture.jpg",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y
    );

    door = SOIL_load_OGL_texture(
        "door.jpg",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y
    );

    cone = SOIL_load_OGL_texture(
        "cone.jpg",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y
    );

    textureImage3 = SOIL_load_OGL_texture(
        "wall2.jpg",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y
    );
    roof1 = SOIL_load_OGL_texture(
        "roof2.jpg",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y
    );

    bench = SOIL_load_OGL_texture(
        "bench.jpg",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y
    );

    block = SOIL_load_OGL_texture(
        "block1.jpg",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y
    );

    grass = SOIL_load_OGL_texture(
        "grass.jpg",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y
    );

    glass = SOIL_load_OGL_texture(
        "glass.jpg",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y
    );

    nicewall = SOIL_load_OGL_texture(
        "nicewall.jpg",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y
    );
    stones = SOIL_load_OGL_texture(
        "stones.jpg",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y
    );
    foundation = SOIL_load_OGL_texture(
        "foundation.jpg",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y
    );
    if (!tex) {
        printf("Texture loading failed: %s\n", SOIL_last_result());
    }
    // Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}


// Texture image rows and columns
#define IMAGE_ROWS 64    
#define IMAGE_COLS 64
//variables to move the camera

GLfloat camX = 0.0; GLfloat camY = 0.0; GLfloat camZ = 0.0;
//variables to move the scene
GLfloat sceRX = 0.0; GLfloat sceRY = 0.0; GLfloat sceRZ = 0.0;
GLfloat sceTX = 0.0; GLfloat sceTY = 0.0; GLfloat sceTZ = 0.0;
////variables to  move the objects
GLfloat objRX = 0.0; GLfloat objRY = 0.0; GLfloat objRZ = 0.0;
GLfloat objTX = 0.0; GLfloat objTY = 0.0; GLfloat objTZ = 0.0;

GLuint textureImage;


void drawGrid() {
    GLfloat step = 1.0f;
    GLint line;
    glBegin(GL_LINES);
    for (line = -20; line <= 20; line += step) {
        glVertex3f(line, -0.4, 20);
        glVertex3f(line, -0.4, -20);
        glVertex3f(20, -0.4, line);
        glVertex3f(-20, -0.4, line);
    }
    glEnd();

}

void drawAxes() {

    glBegin(GL_LINES);
    glLineWidth(1.5);
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(-200, 0, 0);
    glVertex3f(200, 0, 0);
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(0, -200, 0);
    glVertex3f(0, 200, 0);
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(0, 0, -200);
    glVertex3f(0, 0, 200);
    glEnd();

}
void init(void) {

    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClearDepth(1.0);
    glEnable(GL_DEPTH_TEST);
    //Enabling texture
    loadTexture();
    glEnable(GL_TEXTURE_2D);
}


//draw cube
//Vertices of the objects

float vertices[][3] = {

      {1,1,-1},{-1,1,-1},{-1,1,1},{1,1,1}, //Cube coordinates
      {1,-1,-1},{1,-1,1},{-1,-1,1},{-1,-1,-1},
      {0,1,0},                              //Pyramid apex
      {1,0,-1},{0,1,-1},{-1,0,-1},{0,-1,-1},//3D octagon coordinates
      {-1,1,0},{-1,0,1},{-1,-1,0},
      {0,-1,1},{1,0,1},{0,1,1},
      {1,1,0},{1,-1,0}
};
//Draw a quandrangle surface

void surface4(int v1, int v2, int v3, int v4) {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureImage3);

    // Begin drawing the face as a polygon
    glBegin(GL_POLYGON);

    // Top-left vertex of the face
    glTexCoord2f(0.0f, 1.0f); glVertex3fv(vertices[v1]);

    // Top-right vertex of the face
    glTexCoord2f(1.0f, 1.0f); glVertex3fv(vertices[v2]);

    // Bottom-right vertex of the face
    glTexCoord2f(1.0f, 0.0f); glVertex3fv(vertices[v3]);

    // Bottom-left vertex of the face
    glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertices[v4]);

    glEnd();
    glDisable(GL_TEXTURE_2D);
}
//Draw a triangle surface
void surface3(int v1, int v2, int v3) {
    //glEnable(GL_TEXTURE_2D);
   //glBindTexture(GL_TEXTURE_2D, tex);

    glBegin(GL_POLYGON);
    // Apply texture coordinates and vertices
    glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertices[v1]);
    glTexCoord2f(1.0f, 0.0f); glVertex3fv(vertices[v2]);
    glTexCoord2f(0.5f, 1.0f); glVertex3fv(vertices[v3]);
    glEnd();

    // glDisable(GL_TEXTURE_2D);
}
//3D Cube

void cube() {


    glColor3f(1.0f, 1.0f, 1.0f);
    surface4(0, 1, 2, 3);
    glColor3f(1.0f, 1.0f, 1.0f);
    surface4(4, 7, 6, 5);

    glColor3f(1.0f, 1.0f, 1.0f);
    surface4(3, 2, 6, 5);

    glColor3f(1.0f, 1.0f, 1.0f);
    surface4(0, 1, 7, 4);


    glColor3f(1.0f, 1.0f, 1.0f);
    surface4(1, 2, 6, 7);

    glColor3f(1.0f, 1.0f, 1.0f);
    surface4(0, 3, 5, 4);
}



void roof() {
    glColor3f(1.0, 0, 0);
    glTranslatef(0, 2.2, 0);
    glScalef(0.9, 1.1, 2);
    glRotatef(45, 0, 0, 1);
    cube();
}
//house slanted rectangle
void houseTriangle() {
    glColor3f(1.0, 1.0, 1.0);
    glScalef(1.7, 1.4, 1.7);
    glTranslatef(0, 0.1, 0);
    glRotatef(45, 0, 0, 1);
    glBegin(GL_QUADS);
    glVertex2f(-0.20f, -0.20f);
    glVertex2f(-0.20f, 0.20f);
    glVertex2f(0.20f, 0.20f);
    glVertex2f(0.20f, -0.20f);
    glEnd();
}
void longWindow() {
    glEnable(GL_TEXTURE_2D);


    glBindTexture(GL_TEXTURE_2D, tex);

    glColor3f(1.0, 1.0, 1.0);
    glScalef(1.7, 1.4, 1.7);
    glTranslatef(0, 0.1, 0);

    // triangular part of the window
    glBegin(GL_TRIANGLES);
    // Define texture coordinates for each vertex
    glTexCoord2f(0.0f, 0.0f); glVertex2f(-0.20f, -0.60f);  // Bottom-left
    glTexCoord2f(0.5f, 1.0f); glVertex2f(0.0f, -0.40f);    // Top-center
    glTexCoord2f(1.0f, 0.0f); glVertex2f(0.20f, -0.60f);   // Bottom-right
    glEnd();

    // rectangular part of the window
    glBegin(GL_QUADS);

    glTexCoord2f(0.0f, 0.0f); glVertex2f(-0.20f, -1.20f);  // Bottom-left
    glTexCoord2f(0.0f, 1.0f); glVertex2f(-0.20f, -0.60f);  // Top-left
    glTexCoord2f(1.0f, 1.0f); glVertex2f(0.20f, -0.60f);   // Top-right
    glTexCoord2f(1.0f, 0.0f); glVertex2f(0.20f, -1.20f);   // Bottom-right
    glEnd();

    glDisable(GL_TEXTURE_2D);
}


void postWindowLikeWall() {
    glEnable(GL_TEXTURE_2D);


    glBindTexture(GL_TEXTURE_2D, window);

    // triangular part of the wall
    glBegin(GL_TRIANGLES);


    glTexCoord2f(0.0f, 0.0f); glVertex2f(-0.20f, -0.60f);  // Bottom-left
    glTexCoord2f(0.5f, 1.0f); glVertex2f(0.0f, -0.40f);    // Top-center
    glTexCoord2f(1.0f, 0.0f); glVertex2f(0.20f, -0.60f);   // Bottom-right

    glEnd();

    //  rectangular part of the wall
    glBegin(GL_QUADS);


    glTexCoord2f(0.0f, 0.0f); glVertex2f(-0.20f, -1.20f);  // Bottom-left
    glTexCoord2f(0.0f, 1.0f); glVertex2f(-0.20f, -0.60f);  // Top-left
    glTexCoord2f(1.0f, 1.0f); glVertex2f(0.20f, -0.60f);   // Top-right
    glTexCoord2f(1.0f, 0.0f); glVertex2f(0.20f, -1.20f);   // Bottom-right

    glEnd();

    glDisable(GL_TEXTURE_2D);
}

void fourPostWindowLikeWalls() {
    for (int i = 0; i < 4; ++i)
    {
        glPushMatrix();
        // Rotate around the center by 90 degrees each iteration
        glRotatef(i * 90.0f, 0.0f, 1.0f, 0.0f);

        glTranslatef(0.0f, 1.7f, 0.3f);

        glScalef(1.5, 1.5, 1.5);
        postWindowLikeWall();
        glScalef(0.3, 0.3, 0.3);

        glTranslatef(0.0f, -2.0f, 0.1f);
        longWindow();
        glPopMatrix();
    }
}

void post() {
    glScalef(2, 2, 2);

    fourPostWindowLikeWalls();
    glColor3f(1.0, 1.0, 1.0);
    glTranslatef(0.0f, 0.9f, 0.0f);
    glScalef(0.6, 0.8, 0.6);
    fourPostWindowLikeWalls();
    glScalef(0.6, 1, 0.6);
    glTranslatef(0.0f, 1.0f, 0.0f);

    fourPostWindowLikeWalls();
}


void drawStep1(float width, float height, float depth, float x, float y, float z) {
    glPushMatrix();
    glTranslatef(x, y, z);
    glScalef(width, height, depth);


    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, tex3);

    glBegin(GL_QUADS);

    // Front face
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, 0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.5f, -0.5f, 0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.5f, 0.5f, 0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, 0.5f, 0.5f);

    // Back face
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, -0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.5f, -0.5f, -0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.5f, 0.5f, -0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, 0.5f, -0.5f);

    // Top face
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, 0.5f, -0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.5f, 0.5f, -0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.5f, 0.5f, 0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, 0.5f, 0.5f);

    // Bottom face
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, -0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.5f, -0.5f, -0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.5f, -0.5f, 0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, -0.5f, 0.5f);

    // Left face
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, -0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.5f, -0.5f, 0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.5f, 0.5f, 0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, 0.5f, -0.5f);

    // Right face
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0.5f, -0.5f, -0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.5f, -0.5f, 0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.5f, 0.5f, 0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(0.5f, 0.5f, -0.5f);

    glEnd();

    glDisable(GL_TEXTURE_2D);

    glPopMatrix();
}




void drawdoor(float width, float height, float depth, float x, float y, float z) {
    glPushMatrix();

    glTranslatef(x, y, z);

    glRotatef(doorAngle, 0.0f, 1.0f, 0.0f);

    glScalef(width, height, depth);

    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, door);

    glBegin(GL_QUADS);

    // Front face
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, 0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.5f, -0.5f, 0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.5f, 0.5f, 0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, 0.5f, 0.5f);

    // Back face
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, -0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.5f, -0.5f, -0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.5f, 0.5f, -0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, 0.5f, -0.5f);

    // Top face
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, 0.5f, -0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.5f, 0.5f, -0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.5f, 0.5f, 0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, 0.5f, 0.5f);

    // Bottom face
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, -0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.5f, -0.5f, -0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.5f, -0.5f, 0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, -0.5f, 0.5f);

    // Left face
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, -0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.5f, -0.5f, 0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.5f, 0.5f, 0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, 0.5f, -0.5f);

    // Right face
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0.5f, -0.5f, -0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.5f, -0.5f, 0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.5f, 0.5f, 0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(0.5f, 0.5f, -0.5f);

    glEnd();

    glDisable(GL_TEXTURE_2D);

    glPopMatrix();
}
float doorAngleLeft = 0.0f; // Angle for the left door

void drawdoorLeft(float width, float height, float depth, float x, float y, float z) {
    glPushMatrix();


    glTranslatef(x, y, z - (width / 2.0f));

    glRotatef(-doorAngleLeft, 1.0f, 0.0f, 0.0f);

    glScalef(width, height, depth);


    glEnable(GL_TEXTURE_2D);


    glBindTexture(GL_TEXTURE_2D, door);


    glBegin(GL_QUADS);

    // Front face
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, 0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.5f, -0.5f, 0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.5f, 0.5f, 0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, 0.5f, 0.5f);

    // Back face
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, -0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.5f, -0.5f, -0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.5f, 0.5f, -0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, 0.5f, -0.5f);

    // Top face
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, 0.5f, -0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.5f, 0.5f, -0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.5f, 0.5f, 0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, 0.5f, 0.5f);

    // Bottom face
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, -0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.5f, -0.5f, -0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.5f, -0.5f, 0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, -0.5f, 0.5f);

    // Left face
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, -0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.5f, -0.5f, 0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.5f, 0.5f, 0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, 0.5f, -0.5f);

    // Right face
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0.5f, -0.5f, -0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.5f, -0.5f, 0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.5f, 0.5f, 0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(0.5f, 0.5f, -0.5f);

    glEnd();

    glDisable(GL_TEXTURE_2D);

    glPopMatrix();
}




void drawStep(float width, float height, float depth, float x, float y, float z) {
    glPushMatrix();
    glTranslatef(x, y, z);
    glScalef(width, height, depth);
    glutSolidCube(1.0f);
    glPopMatrix();
}

void drawDecreasingStaircase(int stepCount, float baseWidth, float stepHeight, float stepDepth, float widthDecrement) {
    for (int i = 0; i < stepCount; i++) {
        float stepWidth = baseWidth - i * widthDecrement;
        if (stepWidth <= 0.0f) break;
        float x = 0.0f;
        float y = i * stepHeight;
        float z = -i * stepDepth;
        drawStep1(stepWidth, stepHeight, stepDepth, x, y, z);
    }
}
void drawSolidRectangle(float width, float height) {
    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    glVertex2f(-width / 2, -height / 2); // Bottom-left corner
    glVertex2f(width / 2, -height / 2);  // Bottom-right corner
    glVertex2f(width / 2, height / 2);   // Top-right corner
    glVertex2f(-width / 2, height / 2);  // Top-left corner
    glEnd();
}
void oneHouse() {
    //cube
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glTranslatef(0, 1, 0);
    glScalef(1, 1.2, 2);
    cube();
    glPopMatrix();
    //roof
    roof();
    //triangle
    glPushMatrix();

    glTranslatef(0, 0, 1.1);
    //  glScalef(1.3, 1.3, 1);
    glRotatef(-45, 0, 0, 1);
    houseTriangle();
    glPopMatrix();

    glPushMatrix();
    glScalef(1.3, 1.3, 1);
    glTranslatef(0, 0, 1.1);
    glRotatef(-45, 0, 0, 1);
    longWindow();
    glPopMatrix();

}
void base() { // connect with each house
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glTranslatef(0, 2, 0);
    glScalef(6, 0.2, 2);
    cube();
    glPopMatrix();
}
void allHouses() {

    // Draw multiple houses in a
    const int NUM_HOUSES = 5;  // Number of houses to draw
    const float SPACING = 3.2;
    float startX = -(NUM_HOUSES - 1) * SPACING / 2;
    for (int i = 0; i < NUM_HOUSES; i++) {
        glPushMatrix();
        glTranslatef(startX + (i * SPACING), 0.0, 0.0);
        oneHouse();
        glPopMatrix();
    }
    base();


}


void building() {

    glTranslatef(7, 0, 0);
    glRotatef(90, 0.0f, 1.0f, 0.0f);
    allHouses();

    glTranslatef(0, 0, -14);
    glRotatef(-180, 0.0f, 1.0f, 0.0f);
    allHouses();



}

void sideOne() {

    glTranslatef(7, 0, 0);
    // glRotatef(90, 0.0f, 1.0f, 0.0f);
    allHouses();

}

void drawFoundation(float length, float width, float height) {
    glPushMatrix();

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, foundation);

    // Move and scale the foundation
    glTranslatef(0.0f, -height / 2.0f, 0.0f); // Center it properly
    glScalef(length, height, width);

    glBegin(GL_QUADS);

    // Front face
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, 0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.5f, -0.5f, 0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.5f, 0.5f, 0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, 0.5f, 0.5f);

    // Back face
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, -0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.5f, -0.5f, -0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.5f, 0.5f, -0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, 0.5f, -0.5f);

    // Top face
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, 0.5f, -0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.5f, 0.5f, -0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.5f, 0.5f, 0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, 0.5f, 0.5f);

    // Bottom face
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, -0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.5f, -0.5f, -0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.5f, -0.5f, 0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, -0.5f, 0.5f);

    // Left face
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, -0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.5f, -0.5f, 0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.5f, 0.5f, 0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, 0.5f, -0.5f);

    // Right face
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0.5f, -0.5f, -0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.5f, -0.5f, 0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.5f, 0.5f, 0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(0.5f, 0.5f, -0.5f);

    glEnd();

    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}
void mainRoof() {
    // Draw the gable roof
    glColor3f(1.0f, 1.0f, 1.0f); // Red color

    glPushMatrix();
    glTranslatef(0.0f, 0.5f, 0.0f); // Position roof above the building

    // Front triangular face
    glBegin(GL_TRIANGLES);
    glVertex3f(-2.0f, 0.0f, 2.0f); // Bottom-left
    glVertex3f(2.0f, 0.0f, 2.0f);  // Bottom-right
    glVertex3f(0.0f, 2.0f, 0.0f);  // Top
    glEnd();

    // Back triangular face
    glBegin(GL_TRIANGLES);
    glVertex3f(-2.0f, 0.0f, -2.0f); // Bottom-left
    glVertex3f(2.0f, 0.0f, -2.0f);  // Bottom-right
    glVertex3f(0.0f, 2.0f, 0.0f);   // Top
    glEnd();

    // Left slanted rectangular face
    glBegin(GL_QUADS);
    glVertex3f(-2.0f, 0.0f, -2.0f); // Bottom-left
    glVertex3f(-2.0f, 0.0f, 2.0f);  // Bottom-right
    glVertex3f(0.0f, 2.0f, 0.0f);   // Top-right
    glVertex3f(0.0f, 2.0f, 0.0f);   // Top-left
    glEnd();

    // Right slanted rectangular face
    glBegin(GL_QUADS);
    glVertex3f(2.0f, 0.0f, -2.0f); // Bottom-left
    glVertex3f(2.0f, 0.0f, 2.0f);  // Bottom-right
    glVertex3f(0.0f, 2.0f, 0.0f);  // Top-right
    glVertex3f(0.0f, 2.0f, 0.0f);  // Top-left
    glEnd();

    glPopMatrix();
}

void mainRoof1() {

    glEnable(GL_TEXTURE_2D);


    glPushMatrix();
    glTranslatef(0.0f, 0.5f, 0.0f);

    // Front triangular face
    glBegin(GL_TRIANGLES);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-2.0f, 0.0f, 2.0f); // Bottom-left
    glTexCoord2f(1.0f, 0.0f); glVertex3f(2.0f, 0.0f, 2.0f);  // Bottom-right
    glTexCoord2f(0.5f, 1.0f); glVertex3f(0.0f, 2.0f, 0.0f);  // Top
    glEnd();

    // Back triangular face
    glBegin(GL_TRIANGLES);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-2.0f, 0.0f, -2.0f); // Bottom-left
    glTexCoord2f(1.0f, 0.0f); glVertex3f(2.0f, 0.0f, -2.0f);  // Bottom-right
    glTexCoord2f(0.5f, 1.0f); glVertex3f(0.0f, 2.0f, 0.0f);   // Top
    glEnd();

    // Left slanted rectangular face
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-2.0f, 0.0f, -2.0f); // Bottom-left
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-2.0f, 0.0f, 2.0f);  // Bottom-right
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0f, 2.0f, 0.0f);   // Top-right
    glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f, 2.0f, 0.0f);   // Top-left
    glEnd();

    // Right slanted rectangular face
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(2.0f, 0.0f, -2.0f); // Bottom-left
    glTexCoord2f(1.0f, 0.0f); glVertex3f(2.0f, 0.0f, 2.0f);  // Bottom-right
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0f, 2.0f, 0.0f);  // Top-right
    glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f, 2.0f, 0.0f);  // Top-left
    glEnd();

    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
}


void drawFrontWallAndDoor() {
    // Middle side of the front wall
    glColor3f(1.0, 1.0, 1.0);
    glPushMatrix();
    glTranslated(0.0, 0.75, 0.5); // Centered position
    glScaled(0.4, 0.5, 0.02);
    glutSolidCube(1.0);
    glPopMatrix();
    // Left side of the front wall
    glColor3f(1.0, 1.0, 1.0);
    glPushMatrix();
    glTranslated(-0.35, 0.5, 0.5);
    glScaled(0.5, 1.0, 0.02);
    glutSolidCube(1.0);
    glPopMatrix();
    // Right side of the front wall
    glPushMatrix();
    glTranslated(0.35, 0.5, 0.5);
    glScaled(0.5, 1.0, 0.02);
    glutSolidCube(1.0);
    glPopMatrix();


    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glTranslatef(-0.07, 0.25, 0.50);
    glRotatef(dRot1, 0, 1, 0);
    glTranslatef(0.05, 0.0, 0.0);
    glScaled(0.23, 0.5, 0.03);
    glutSolidCube(1.0);
    glPopMatrix();
}

void drawRectangularWall(float width, float height, float depth) {
    glBegin(GL_QUADS);

    // Front face
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(width, 0.0f, 0.0f);
    glVertex3f(width, height, 0.0f);
    glVertex3f(0.0f, height, 0.0f);

    // Back face
    glVertex3f(0.0f, 0.0f, -depth);
    glVertex3f(width, 0.0f, -depth);
    glVertex3f(width, height, -depth);
    glVertex3f(0.0f, height, -depth);

    // Left face
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, height, 0.0f);
    glVertex3f(0.0f, height, -depth);
    glVertex3f(0.0f, 0.0f, -depth);

    // Right face
    glVertex3f(width, 0.0f, 0.0f);
    glVertex3f(width, height, 0.0f);
    glVertex3f(width, height, -depth);
    glVertex3f(width, 0.0f, -depth);

    // Top face
    glVertex3f(0.0f, height, 0.0f);
    glVertex3f(width, height, 0.0f);
    glVertex3f(width, height, -depth);
    glVertex3f(0.0f, height, -depth);

    // Bottom face
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(width, 0.0f, 0.0f);
    glVertex3f(width, 0.0f, -depth);
    glVertex3f(0.0f, 0.0f, -depth);

    glEnd();
}

void drawRightAngledTriangle(float base, float height) {
    glBegin(GL_TRIANGLES);

    // Set color for the triangle
    glColor3f(1.0, 1.0, 1.0);

    // Vertex 1 (origin)
    glVertex3f(0.0f, 0.0f, 0.0f);

    // Vertex 2 (base)
    glVertex3f(base, 0.0f, 0.0f);

    // Vertex 3 (height)
    glVertex3f(0.0f, height, 0.0f);

    glEnd();
}

void drawCombinedStructure() {

    glPushMatrix();
    glTranslatef(4.0f, 0.0f, 0.0f);
    glPopMatrix();
}

void drawTexturedSphere(float radius, int slices, int stacks, float x, float y, float z) {

    GLUquadric* quad = gluNewQuadric();
    glPushMatrix();
    glTranslatef(x, y, z);  // Position the sphere


    gluQuadricTexture(quad, GL_TRUE);
    glEnable(GL_TEXTURE_2D);


    glBindTexture(GL_TEXTURE_2D, tex4);
    glColor3f(1.0f, 1.0f, 1.0f);
    gluSphere(quad, 100, 100, 100);
    glDisable(GL_TEXTURE_2D);

    glPopMatrix();
};
void drawSolidDisk(GLfloat innerRadius, GLfloat outerRadius, GLfloat height, GLint slices, GLint loops) {
    GLUquadric* quad = gluNewQuadric();

    //  top face
    glPushMatrix();
    glTranslatef(0.0f, height / 2, 0.0f);
    gluDisk(quad, innerRadius, outerRadius, slices, loops);
    glPopMatrix();

    //  bottom face
    glPushMatrix();
    glTranslatef(0.0f, -height / 2, 0.0f);
    gluDisk(quad, innerRadius, outerRadius, slices, loops);
    glPopMatrix();

    //side of the disk  cylinder
    glPushMatrix();
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    gluCylinder(quad, outerRadius, outerRadius, height, slices, loops);
    glPopMatrix();

    gluDeleteQuadric(quad);
}


void drawSolidRightTrapezium() {
    //vertices of the right trapezium
    GLfloat vertices[][3] = {
        {0.0f, -0.5f, -0.5f},  // Bottom face - Left
        {1.0f, -0.5f, -0.5f},  // Bottom face - Right
        {0.7f,  0.5f, -0.5f},  // Top face - Right
        {0.0f,  0.5f, -0.5f},  // Top face - Left
        {0.0f, -0.5f,  0.5f},  // Bottom face - Left Front
        {1.0f, -0.5f,  0.5f},  // Bottom face - Right Front
        {0.7f,  0.5f,  0.5f},  // Top face - Right Front
        {0.0f,  0.5f,  0.5f}   // Top face - Left Front
    };

    // faces of the right trapezium using indices
    GLubyte indices[][4] = {
        {0, 1, 5, 4}, // Bottom face
        {3, 2, 6, 7}, // Top face
        {0, 4, 7, 3}, // Left face
        {1, 5, 6, 2}, // Right face
        {4, 5, 6, 7}, // Front face
        {0, 1, 2, 3}  // Back face
    };


    glColor3f(0.5f, 0.3f, 0.8f);
    glBegin(GL_QUADS);
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 4; ++j) {
            glVertex3fv(vertices[indices[i][j]]);
        }
    }
    glEnd();
}


void drawCuboid(float length, float width, float height) {
    // Vertices of the cuboid
    GLfloat vertices[][3] = {
        {-length / 2, -width / 2, -height / 2}, // 0 - Front bottom left
        { length / 2, -width / 2, -height / 2}, // 1 - Front bottom right
        { length / 2,  width / 2, -height / 2}, // 2 - Front top right
        {-length / 2,  width / 2, -height / 2}, // 3 - Front top left
        {-length / 2, -width / 2,  height / 2}, // 4 - Back bottom left
        { length / 2, -width / 2,  height / 2}, // 5 - Back bottom right
        { length / 2,  width / 2,  height / 2}, // 6 - Back top right
        {-length / 2,  width / 2,  height / 2}  // 7 - Back top left
    };


    GLfloat texCoords[][2] = {
        {0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f}, // Front
        {0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f}, // Back
        {0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f}, // Top
        {0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f}, // Bottom
        {0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f}, // Left
        {0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f}  // Right
    };


    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, creamTexture); // Assuming 'tex' is your loaded texture

    glBegin(GL_QUADS);
    // Front face
    glTexCoord2fv(texCoords[0]); glVertex3fv(vertices[0]);
    glTexCoord2fv(texCoords[1]); glVertex3fv(vertices[1]);
    glTexCoord2fv(texCoords[2]); glVertex3fv(vertices[2]);
    glTexCoord2fv(texCoords[3]); glVertex3fv(vertices[3]);

    // Back face
    glTexCoord2fv(texCoords[4]); glVertex3fv(vertices[4]);
    glTexCoord2fv(texCoords[5]); glVertex3fv(vertices[5]);
    glTexCoord2fv(texCoords[6]); glVertex3fv(vertices[6]);
    glTexCoord2fv(texCoords[7]); glVertex3fv(vertices[7]);

    // Top face
    glTexCoord2fv(texCoords[8]); glVertex3fv(vertices[3]);
    glTexCoord2fv(texCoords[9]); glVertex3fv(vertices[2]);
    glTexCoord2fv(texCoords[10]); glVertex3fv(vertices[6]);
    glTexCoord2fv(texCoords[11]); glVertex3fv(vertices[7]);

    // Bottom face
    glTexCoord2fv(texCoords[12]); glVertex3fv(vertices[0]);
    glTexCoord2fv(texCoords[13]); glVertex3fv(vertices[1]);
    glTexCoord2fv(texCoords[14]); glVertex3fv(vertices[5]);
    glTexCoord2fv(texCoords[15]); glVertex3fv(vertices[4]);

    // Left face
    glTexCoord2fv(texCoords[16]); glVertex3fv(vertices[0]);
    glTexCoord2fv(texCoords[17]); glVertex3fv(vertices[3]);
    glTexCoord2fv(texCoords[18]); glVertex3fv(vertices[7]);
    glTexCoord2fv(texCoords[19]); glVertex3fv(vertices[4]);

    // Right face
    glTexCoord2fv(texCoords[20]); glVertex3fv(vertices[1]);
    glTexCoord2fv(texCoords[21]); glVertex3fv(vertices[2]);
    glTexCoord2fv(texCoords[22]); glVertex3fv(vertices[6]);
    glTexCoord2fv(texCoords[23]); glVertex3fv(vertices[5]);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}
void topBanner(float length, float width, float height) {
    // Vertices of the cuboid based on the parameters
    GLfloat vertices[][3] = {
        {-length / 2, -width / 2, -height / 2}, // 0 - Front bottom left
        { length / 2, -width / 2, -height / 2}, // 1 - Front bottom right
        { length / 2,  width / 2, -height / 2}, // 2 - Front top right
        {-length / 2,  width / 2, -height / 2}, // 3 - Front top left
        {-length / 2, -width / 2,  height / 2}, // 4 - Back bottom left
        { length / 2, -width / 2,  height / 2}, // 5 - Back bottom right
        { length / 2,  width / 2,  height / 2}, // 6 - Back top right
        {-length / 2,  width / 2,  height / 2}  // 7 - Back top left
    };

    // Texture coordinates for each face of the cuboid
    GLfloat texCoords[][2] = {
        {0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f}, // Front
        {0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f}, // Back
        {0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f}, // Top
        {0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f}, // Bottom
        {0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f}, // Left
        {0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f}  // Right
    };

    //texture to each face of the cuboid
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, tex); // Assuming 'tex' is your loaded texture

    glBegin(GL_QUADS);
    // Front face
    glTexCoord2fv(texCoords[0]); glVertex3fv(vertices[0]);
    glTexCoord2fv(texCoords[1]); glVertex3fv(vertices[1]);
    glTexCoord2fv(texCoords[2]); glVertex3fv(vertices[2]);
    glTexCoord2fv(texCoords[3]); glVertex3fv(vertices[3]);

    // Back face
    glTexCoord2fv(texCoords[4]); glVertex3fv(vertices[4]);
    glTexCoord2fv(texCoords[5]); glVertex3fv(vertices[5]);
    glTexCoord2fv(texCoords[6]); glVertex3fv(vertices[6]);
    glTexCoord2fv(texCoords[7]); glVertex3fv(vertices[7]);

    // Top face
    glTexCoord2fv(texCoords[8]); glVertex3fv(vertices[3]);
    glTexCoord2fv(texCoords[9]); glVertex3fv(vertices[2]);
    glTexCoord2fv(texCoords[10]); glVertex3fv(vertices[6]);
    glTexCoord2fv(texCoords[11]); glVertex3fv(vertices[7]);

    // Bottom face
    glTexCoord2fv(texCoords[12]); glVertex3fv(vertices[0]);
    glTexCoord2fv(texCoords[13]); glVertex3fv(vertices[1]);
    glTexCoord2fv(texCoords[14]); glVertex3fv(vertices[5]);
    glTexCoord2fv(texCoords[15]); glVertex3fv(vertices[4]);

    // Left face
    glTexCoord2fv(texCoords[16]); glVertex3fv(vertices[0]);
    glTexCoord2fv(texCoords[17]); glVertex3fv(vertices[3]);
    glTexCoord2fv(texCoords[18]); glVertex3fv(vertices[7]);
    glTexCoord2fv(texCoords[19]); glVertex3fv(vertices[4]);

    // Right face
    glTexCoord2fv(texCoords[20]); glVertex3fv(vertices[1]);
    glTexCoord2fv(texCoords[21]); glVertex3fv(vertices[2]);
    glTexCoord2fv(texCoords[22]); glVertex3fv(vertices[6]);
    glTexCoord2fv(texCoords[23]); glVertex3fv(vertices[5]);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}

void banner(float length, float width, float height) {
    // Vertices of the cuboid based on the parameters
    GLfloat vertices[][3] = {
        {-length / 2, -width / 2, -height / 2}, // 0 - Front bottom left
        { length / 2, -width / 2, -height / 2}, // 1 - Front bottom right
        { length / 2,  width / 2, -height / 2}, // 2 - Front top right
        {-length / 2,  width / 2, -height / 2}, // 3 - Front top left
        {-length / 2, -width / 2,  height / 2}, // 4 - Back bottom left
        { length / 2, -width / 2,  height / 2}, // 5 - Back bottom right
        { length / 2,  width / 2,  height / 2}, // 6 - Back top right
        {-length / 2,  width / 2,  height / 2}  // 7 - Back top left
    };

    // Texture coordinates for each face of the cuboid
    GLfloat texCoords[][2] = {
        {0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f}, // Front
        {0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f}, // Back
        {0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f}, // Top
        {0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f}, // Bottom
        {0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f}, // Left
        {0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f}  // Right
    };

    //  texture to each face of the cuboid
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, tex2); // Assuming 'tex' is your loaded texture

    glBegin(GL_QUADS);
    // Front face
    glTexCoord2fv(texCoords[0]); glVertex3fv(vertices[0]);
    glTexCoord2fv(texCoords[1]); glVertex3fv(vertices[1]);
    glTexCoord2fv(texCoords[2]); glVertex3fv(vertices[2]);
    glTexCoord2fv(texCoords[3]); glVertex3fv(vertices[3]);

    // Back face
    glTexCoord2fv(texCoords[4]); glVertex3fv(vertices[4]);
    glTexCoord2fv(texCoords[5]); glVertex3fv(vertices[5]);
    glTexCoord2fv(texCoords[6]); glVertex3fv(vertices[6]);
    glTexCoord2fv(texCoords[7]); glVertex3fv(vertices[7]);

    // Top face
    glTexCoord2fv(texCoords[8]); glVertex3fv(vertices[3]);
    glTexCoord2fv(texCoords[9]); glVertex3fv(vertices[2]);
    glTexCoord2fv(texCoords[10]); glVertex3fv(vertices[6]);
    glTexCoord2fv(texCoords[11]); glVertex3fv(vertices[7]);

    // Bottom face
    glTexCoord2fv(texCoords[12]); glVertex3fv(vertices[0]);
    glTexCoord2fv(texCoords[13]); glVertex3fv(vertices[1]);
    glTexCoord2fv(texCoords[14]); glVertex3fv(vertices[5]);
    glTexCoord2fv(texCoords[15]); glVertex3fv(vertices[4]);

    // Left face
    glTexCoord2fv(texCoords[16]); glVertex3fv(vertices[0]);
    glTexCoord2fv(texCoords[17]); glVertex3fv(vertices[3]);
    glTexCoord2fv(texCoords[18]); glVertex3fv(vertices[7]);
    glTexCoord2fv(texCoords[19]); glVertex3fv(vertices[4]);

    // Right face
    glTexCoord2fv(texCoords[20]); glVertex3fv(vertices[1]);
    glTexCoord2fv(texCoords[21]); glVertex3fv(vertices[2]);
    glTexCoord2fv(texCoords[22]); glVertex3fv(vertices[6]);
    glTexCoord2fv(texCoords[23]); glVertex3fv(vertices[5]);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}


void ground(float length, float width, float height) {
    // Vertices of the cuboid
    GLfloat vertices[][3] = {
        {-length / 2, -width / 2, -height / 2}, // 0 - Front bottom left
        { length / 2, -width / 2, -height / 2}, // 1 - Front bottom right
        { length / 2,  width / 2, -height / 2}, // 2 - Front top right
        {-length / 2,  width / 2, -height / 2}, // 3 - Front top left
        {-length / 2, -width / 2,  height / 2}, // 4 - Back bottom left
        { length / 2, -width / 2,  height / 2}, // 5 - Back bottom right
        { length / 2,  width / 2,  height / 2}, // 6 - Back top right
        {-length / 2,  width / 2,  height / 2}  // 7 - Back top left
    };

    // Texture coordinates for each face of the cuboid
    GLfloat texCoords[][2] = {
        {0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f}, // Front
        {0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f}, // Back
        {0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f}, // Top
        {0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f}, // Bottom
        {0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f}, // Left
        {0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f}  // Right
    };


    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, tex1);

    glBegin(GL_QUADS);
    // Front face
    glTexCoord2fv(texCoords[0]); glVertex3fv(vertices[0]);
    glTexCoord2fv(texCoords[1]); glVertex3fv(vertices[1]);
    glTexCoord2fv(texCoords[2]); glVertex3fv(vertices[2]);
    glTexCoord2fv(texCoords[3]); glVertex3fv(vertices[3]);

    // Back face
    glTexCoord2fv(texCoords[4]); glVertex3fv(vertices[4]);
    glTexCoord2fv(texCoords[5]); glVertex3fv(vertices[5]);
    glTexCoord2fv(texCoords[6]); glVertex3fv(vertices[6]);
    glTexCoord2fv(texCoords[7]); glVertex3fv(vertices[7]);

    // Top face
    glTexCoord2fv(texCoords[8]); glVertex3fv(vertices[3]);
    glTexCoord2fv(texCoords[9]); glVertex3fv(vertices[2]);
    glTexCoord2fv(texCoords[10]); glVertex3fv(vertices[6]);
    glTexCoord2fv(texCoords[11]); glVertex3fv(vertices[7]);

    // Bottom face
    glTexCoord2fv(texCoords[12]); glVertex3fv(vertices[0]);
    glTexCoord2fv(texCoords[13]); glVertex3fv(vertices[1]);
    glTexCoord2fv(texCoords[14]); glVertex3fv(vertices[5]);
    glTexCoord2fv(texCoords[15]); glVertex3fv(vertices[4]);

    // Left face
    glTexCoord2fv(texCoords[16]); glVertex3fv(vertices[0]);
    glTexCoord2fv(texCoords[17]); glVertex3fv(vertices[3]);
    glTexCoord2fv(texCoords[18]); glVertex3fv(vertices[7]);
    glTexCoord2fv(texCoords[19]); glVertex3fv(vertices[4]);

    // Right face
    glTexCoord2fv(texCoords[20]); glVertex3fv(vertices[1]);
    glTexCoord2fv(texCoords[21]); glVertex3fv(vertices[2]);
    glTexCoord2fv(texCoords[22]); glVertex3fv(vertices[6]);
    glTexCoord2fv(texCoords[23]); glVertex3fv(vertices[5]);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}


void drawCuboid(float length, float width, float height, GLuint textureID) {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glBegin(GL_QUADS);

    // Front face
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-length / 2, -height / 2, width / 2); // Bottom-left
    glTexCoord2f(1.0f, 0.0f); glVertex3f(length / 2, -height / 2, width / 2);  // Bottom-right
    glTexCoord2f(1.0f, 1.0f); glVertex3f(length / 2, height / 2, width / 2);   // Top-right
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-length / 2, height / 2, width / 2);  // Top-left

    // Back face
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-length / 2, -height / 2, -width / 2);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(length / 2, -height / 2, -width / 2);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(length / 2, height / 2, -width / 2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-length / 2, height / 2, -width / 2);

    // Top face
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-length / 2, height / 2, -width / 2);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(length / 2, height / 2, -width / 2);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(length / 2, height / 2, width / 2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-length / 2, height / 2, width / 2);

    // Bottom face
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-length / 2, -height / 2, -width / 2);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(length / 2, -height / 2, -width / 2);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(length / 2, -height / 2, width / 2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-length / 2, -height / 2, width / 2);

    // Left face
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-length / 2, -height / 2, -width / 2);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-length / 2, height / 2, -width / 2);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-length / 2, height / 2, width / 2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-length / 2, -height / 2, width / 2);

    // Right face
    glTexCoord2f(0.0f, 0.0f); glVertex3f(length / 2, -height / 2, -width / 2);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(length / 2, height / 2, -width / 2);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(length / 2, height / 2, width / 2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(length / 2, -height / 2, width / 2);

    glEnd();

    glDisable(GL_TEXTURE_2D);
}


void solidTriangle()
{
    glPushMatrix();
    glScalef(2.2f, 2.2f, 2.2f);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, tex);
    glColor3f(1.0, 1.0, 1.0);

    // front triangle with texture mapping
    glBegin(GL_TRIANGLES);
    glTexCoord2f(0.5f, 1.0f); glVertex3f(0.0f, 1.0f, 0.1f);   // Top vertex
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, 0.1f);  // Bottom-left vertex
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.5f, -0.5f, 0.1f);   // Bottom-right vertex
    glEnd();

    // back triangle with texture mapping
    glBegin(GL_TRIANGLES);
    glTexCoord2f(0.5f, 1.0f); glVertex3f(0.0f, 1.0f, -0.1f);  // Top vertex
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, -0.1f); // Bottom-left vertex
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.5f, -0.5f, -0.1f);  // Bottom-right vertex
    glEnd();

    //  sides connecting the front and back triangles with texture mapping
    glBegin(GL_QUADS);

    // Left side (between front and back)
    glTexCoord2f(0.0f, 0.5f); glVertex3f(0.0f, 1.0f, 0.1f);
    glTexCoord2f(0.0f, 0.5f); glVertex3f(0.0f, 1.0f, -0.1f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, -0.1f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, 0.1f);

    // Right side (between front and back)
    glTexCoord2f(1.0f, 0.5f); glVertex3f(0.5f, -0.5f, 0.1f);
    glTexCoord2f(1.0f, 0.5f); glVertex3f(0.5f, -0.5f, -0.1f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, 1.0f, -0.1f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, 1.0f, 0.1f);

    // Bottom side (between front and back)
    glTexCoord2f(0.0f, 0.5f); glVertex3f(-0.5f, -0.5f, 0.1f);
    glTexCoord2f(0.0f, 0.5f); glVertex3f(-0.5f, -0.5f, -0.1f);
    glTexCoord2f(1.0f, 0.5f); glVertex3f(0.5f, -0.5f, -0.1f);
    glTexCoord2f(1.0f, 0.5f); glVertex3f(0.5f, -0.5f, 0.1f);

    glEnd();

    glDisable(GL_TEXTURE_2D);

    glPopMatrix();
}



void drawFourTrianglesAroundObject()
{
    for (int i = 0; i < 4; ++i)
    {

        glRotatef(i * 90.0f, 0.0f, 1.0f, 0.0f);

        glTranslatef(0.0f, 0.0f, 1.00f);

        solidTriangle();

    }
}
void coneUsingTriangles(float baseRadius, float height, int numTriangles) {
    float angleStep = 1.0f * M_PI / numTriangles; // Angle between each triangle


    glEnable(GL_TEXTURE_2D);


    glBindTexture(GL_TEXTURE_2D, cone);

    glPushMatrix();
    glColor3f(1.0f, 1.0f, 1.0f);

    for (int i = 0; i < numTriangles; i++) {
        float angle = i * angleStep;
        float nextAngle = (i + 1) * angleStep;

        glBegin(GL_TRIANGLES);

        // Top vertex (cone tip)
        glTexCoord2f(0.5f, 1.0f);
        glVertex3f(0.0f, height, 0.0f);

        // Base vertices
        glTexCoord2f(cos(angle) * 0.5f + 0.5f, sin(angle) * 0.5f + 0.5f);
        glVertex3f(baseRadius * cos(angle), 0.0f, baseRadius * sin(angle)); // Current angle

        glTexCoord2f(cos(nextAngle) * 0.5f + 0.5f, sin(nextAngle) * 0.5f + 0.5f);
        glVertex3f(baseRadius * cos(nextAngle), 0.0f, baseRadius * sin(nextAngle)); // Next angle

        glEnd();
    }

    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void drawCross() {
    glEnable(GL_TEXTURE_2D);
    // Vertical part of the cross
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, tex6);
    glTranslatef(0.0f, 0.0f, 0.0f);
    glScalef(0.08f, 0.3f, 0.08f);
    glBegin(GL_QUADS);
    // Front face
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, 0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.5f, -0.5f, 0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.5f, 0.5f, 0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, 0.5f, 0.5f);

    glEnd();
    glPopMatrix();

    // Horizontal part of the cross
    glPushMatrix();

    glTranslatef(0.0f, 0.05f, 0.0f);
    glScalef(0.2f, 0.06f, 0.06f);
    glBegin(GL_QUADS);
    // Front face
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, 0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.5f, -0.5f, 0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.5f, 0.5f, 0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, 0.5f, 0.5f);

    glEnd();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
}

void drawCrosses() {
    for (int i = 0; i < 3; i++) {
        glPushMatrix();


        if (i == 0) {
            glTranslatef(-1.5f, 0.5f, -7.0f); // Left cross
        }
        else if (i == 1) {
            glTranslatef(0.0f, 0.7f, -7.0f); // Middle cross (higher)
        }
        else if (i == 2) {
            glTranslatef(1.5f, 0.5f, -7.0f); // Right cross
        }

        drawCross();
        glPopMatrix();
    }
}




void setLighting() {


    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
    glEnable(GL_LIGHTING);


    // Set lighting intensity and color - light 0
    GLfloat qaAmbientLight[] = { 0.2, 0.2, 0.2, 1.0 };
    GLfloat qaDiffuseLight[] = { 0.8, 0.8, 0.8, 1.0 };
    GLfloat qaSpecularLight[] = { 1.0, 1.0, 1.0, 1.0 };
    glLightfv(GL_LIGHT0, GL_AMBIENT, qaAmbientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, qaDiffuseLight);
    glLightfv(GL_LIGHT0, GL_SPECULAR, qaSpecularLight);

    // Set the light position - light 0
    GLfloat qaLightPosition[] = { -10.0, 1.0, -.5, 1.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, qaLightPosition);

    // Set lighting intensity and color - light 1
    GLfloat qaAmbientLight1[] = { 0.2, 0.2, 0.2, 1.0 };
    GLfloat qaDiffuseLight1[] = { 0.8, 0.8, 0.8, 1.0 };
    GLfloat qaSpecularLight1[] = { 1.0, 1.0, 1.0, 1.0 };
    glLightfv(GL_LIGHT1, GL_AMBIENT, qaAmbientLight1);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, qaDiffuseLight1);
    glLightfv(GL_LIGHT1, GL_SPECULAR, qaSpecularLight1);

    // Set the light position - light 1
    GLfloat qaLightPosition1[] = { 10.0, 1.0, 0.5, 1.0 };
    glLightfv(GL_LIGHT1, GL_POSITION, qaLightPosition1);

    GLfloat SpecRef[] = { 0.7,0.7,0.7,1.0 };
    GLint Shine = 128;
    glShadeModel(GL_SMOOTH);
    glEnable(GL_COLOR_MATERIAL);                   //Enable color tracking
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);//Set material to follow
    glMaterialfv(GL_FRONT, GL_SPECULAR, SpecRef);//Set specular reflectivity and shine
    glMateriali(GL_FRONT, GL_SHININESS, Shine);
}

void drawGround() {

    GLUquadric* quad = gluNewQuadric();

    glPushMatrix();

    gluQuadricTexture(quad, GL_TRUE);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, tex1);

    gluDisk(quad, 0, 100, 100, 100);
    glDisable(GL_TEXTURE_2D);

    glPopMatrix();
    gluDeleteQuadric(quad);
}

void drawGrass1() {

    GLUquadric* quad = gluNewQuadric();

    glPushMatrix();

    gluQuadricTexture(quad, GL_TRUE);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, grass);
    gluDisk(quad, 0, 5, 100, 100);
    glDisable(GL_TEXTURE_2D);

    glPopMatrix();
    gluDeleteQuadric(quad);
}
// Vertices of the triangular prism
GLfloat verticess[][3] = {
    {-1.0f, 0.0f, -0.5f},  // 0 - Bottom-left of triangle
    {1.0f, 0.0f, -0.5f},   // 1 - Bottom-right of triangle
    {0.0f, sqrt(3.0f), -0.5f}, // 2 - Top of triangle at one end 60-degree

    {-1.0f, 0.0f, 0.5f},  // 3 - Bottom-left of triangle at other end
    {1.0f, 0.0f, 0.5f},   // 4 - Bottom-right of triangle at other end
    {0.0f, sqrt(3.0f), 0.5f}  // 5 - Top of triangle at other end
};


GLfloat texCoords[][2] = {
    {0.0f, 0.0f},  // Bottom-left
    {1.0f, 0.0f},  // Bottom-right
    {1.0f, 1.0f},  // Top-right
    {0.0f, 1.0f}   // Top-left
};


void drawTexturedTriangularPrism() {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, roof1);

    // Front face (Triangle)
    glBegin(GL_TRIANGLES);
    glTexCoord2f(texCoords[0][0], texCoords[0][1]); glVertex3fv(verticess[0]);
    glTexCoord2f(texCoords[1][0], texCoords[1][1]); glVertex3fv(verticess[1]);
    glTexCoord2f(texCoords[2][0], texCoords[2][1]); glVertex3fv(verticess[2]);
    glEnd();

    // Back face (Triangle)
    glBegin(GL_TRIANGLES);
    glTexCoord2f(texCoords[0][0], texCoords[0][1]); glVertex3fv(verticess[3]);
    glTexCoord2f(texCoords[1][0], texCoords[1][1]); glVertex3fv(verticess[4]);
    glTexCoord2f(texCoords[2][0], texCoords[2][1]); glVertex3fv(verticess[5]);
    glEnd();

    // Left face (Rectangle)
    glBegin(GL_QUADS);
    glTexCoord2f(texCoords[0][0], texCoords[0][1]); glVertex3fv(verticess[0]); // Bottom-left-back
    glTexCoord2f(texCoords[1][0], texCoords[1][1]); glVertex3fv(verticess[3]); // Bottom-left-front
    glTexCoord2f(texCoords[2][0], texCoords[2][1]); glVertex3fv(verticess[5]); // Top-front
    glTexCoord2f(texCoords[3][0], texCoords[3][1]); glVertex3fv(verticess[2]); // Top-back
    glEnd();

    // Right face (Rectangle)
    glBegin(GL_QUADS);
    glTexCoord2f(texCoords[0][0], texCoords[0][1]); glVertex3fv(verticess[1]); // Bottom-right-back
    glTexCoord2f(texCoords[1][0], texCoords[1][1]); glVertex3fv(verticess[4]); // Bottom-right-front
    glTexCoord2f(texCoords[2][0], texCoords[2][1]); glVertex3fv(verticess[5]); // Top-front
    glTexCoord2f(texCoords[3][0], texCoords[3][1]); glVertex3fv(verticess[2]); // Top-back
    glEnd();

    // Bottom face (Rectangle)
    glBegin(GL_QUADS);
    glTexCoord2f(texCoords[0][0], texCoords[0][1]); glVertex3fv(verticess[0]); // Bottom-left-back
    glTexCoord2f(texCoords[1][0], texCoords[1][1]); glVertex3fv(verticess[1]); // Bottom-right-back
    glTexCoord2f(texCoords[2][0], texCoords[2][1]); glVertex3fv(verticess[4]); // Bottom-right-front
    glTexCoord2f(texCoords[3][0], texCoords[3][1]); glVertex3fv(verticess[3]); // Bottom-left-front
    glEnd();

    glDisable(GL_TEXTURE_2D);
}


void cube(float height, float half_top_width, float half_bottom_width) {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, block);

    glPushMatrix();
    glBegin(GL_QUADS);

    // Front Face
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-half_bottom_width, 0.0f, half_bottom_width);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(half_bottom_width, 0.0f, half_bottom_width);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(half_top_width, height, half_top_width);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-half_top_width, height, half_top_width);

    // Back Face
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-half_bottom_width, 0.0f, -half_bottom_width);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(half_bottom_width, 0.0f, -half_bottom_width);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(half_top_width, height, -half_top_width);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-half_top_width, height, -half_top_width);

    // Top Face
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-half_top_width, height, -half_top_width);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-half_top_width, height, half_top_width);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(half_top_width, height, half_top_width);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(half_top_width, height, -half_top_width);

    // Bottom Face
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-half_bottom_width, 0.0f, -half_bottom_width);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(half_bottom_width, 0.0f, -half_bottom_width);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(half_bottom_width, 0.0f, half_bottom_width);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-half_bottom_width, 0.0f, half_bottom_width);

    // Right Face
    glTexCoord2f(0.0f, 0.0f); glVertex3f(half_bottom_width, 0.0f, -half_bottom_width);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(half_top_width, height, -half_top_width);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(half_top_width, height, half_top_width);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(half_bottom_width, 0.0f, half_bottom_width);

    // Left Face
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-half_bottom_width, 0.0f, -half_bottom_width);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-half_bottom_width, 0.0f, half_bottom_width);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-half_top_width, height, half_top_width);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-half_top_width, height, -half_top_width);

    glEnd();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
}

void createWindowFrame(float x, float y, float z) {
    float half_width = 0.5;
    float height = 2;

    glPushMatrix();
    glTranslatef(x, y, z);
    glPushMatrix();
    glTranslatef(half_width, 0, 0);
    cube(height + 0.05, 0.05, 0.05);
    glTranslatef(-2 * half_width, 0, 0);
    cube(height + 0.05, 0.05, 0.05);
    glPopMatrix();

    glPushMatrix();
    glRotatef(90, 0, 0, 1);
    glTranslatef(0.05, -half_width, 0);
    cube(2 * half_width, 0.05, 0.05);
    glTranslatef(height - 0.05, 0, 0);
    cube(2 * half_width, 0.05, 0.05);
    cube(half_width, 0.05, 0.05);
    glPopMatrix();

    glPushMatrix();
    glScalef(1, 1, 0.05);
    cube(height - 0.05, half_width, half_width);
    glPopMatrix();

    glPopMatrix();
}

void buildingBlock() {
    glPushMatrix();
    cube(3, 1.5, 1.5);
    glTranslatef(0, 3, 0);
    cube(0.25, 1.55, 1.5);
    glTranslatef(0, 0.25, 0);
    cube(0.75, 0.55, 1.1);
    glTranslatef(0, 0.75, 0);
    cube(1.5, 0.1, 0.55);
    glPopMatrix();
}

void displayUnits() {
    buildingBlock();
    createWindowFrame(0, 0, 1.55);
}



float frameWidth = 10.0f;
float frameHeight = 10.0f;
float fenceHeight = 2.0f;


// Function to draw the bench with applied texture
void drawBench() {
    glPushMatrix();


    glBindTexture(GL_TEXTURE_2D, bench);
    glEnable(GL_TEXTURE_2D);
    // Draw the top surface of the bench (seat)
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0, 3, 0.0);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0, 3, 5.0);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.5, 3, 5.0);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(1.5, 3, 0);
    glEnd();

    // Draw the side panels (backrest)
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0, 3, 0.0);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.5, 5, 0.0);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.5, 5, 5.0);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(0, 3, 5.0);
    glEnd();

    // Draw the legs
    // Front left leg
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0, 3, 5.0);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0, 0.2, 5.0);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.1, 0.2, 5.0);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(0.1, 3, 5.0);
    glEnd();

    // Front right leg
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0.9, 3, 5.0);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.9, 0.2, 5.0);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1, 0.2, 5.0);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(1, 3, 5.0);
    glEnd();

    // Back left leg
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0, 3, 0.0);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0, 0.2, 0.0);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.1, 0.2, 0.0);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(0.1, 3, 0.0);
    glEnd();

    // Back right leg
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0.9, 3, 0.0);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.9, 0.2, 0.0);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1, 0.2, 0.0);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(1, 3, 0.0);
    glEnd();

    // Seat back
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0, 3, 5.0);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0, 3, 0.0);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.5, 3, 0.0);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(1.5, 3, 5.0);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}
void drawGrass() {
    glPushMatrix();
    glTranslatef(-50, 0.1, 42.0);

    glBegin(GL_QUADS);

    glTexCoord2f(0, 1);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glTexCoord2f(1, 1);
    glVertex3f(0.0f, 0.0f, 14.0f);
    glTexCoord2f(1, 0);
    glVertex3f(100.0f, 0.0f, 14.0f);
    glTexCoord2f(0, 0);
    glVertex3f(100.0f, 0.00f, 0.0f);

    glEnd();


    glPopMatrix();
}


void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    // camera orientation (eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ)
    gluLookAt(0.0, 0.0 + camY, 13.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);


    // move the scene (all the rendered environment) using keyboard keys
    glTranslatef(sceTX, sceTY, sceTZ);
    glRotatef(sceRY, 0.0, 1.0, 0.0);
    setLighting();

    //Draw a grid on the xz plane
    glColor3f(1, 1, 1);
    if (gridOn == 1)
        drawGrid();
    //draw the three axes
    if (axesOn == 1)
        drawAxes();
    building();

    // expanding staircase
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glTranslatef(14, 0, -7);
    glRotatef(90, 0.0f, 1.0f, 0.0f);
    drawDecreasingStaircase(7, 2.0f, 0.5f, 1.0f, 0.2f);
    glPopMatrix();

    //foundation
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glTranslatef(0, 0.8, -7);
    drawFoundation(16.0f, 10.0f, 2.0f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(8.8, 0.0, -4);
    glScalef(1.2, 1.8, 1.2);
    post();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(8.8, 0.0, -10.0);
    glScalef(1.2, 1.8, 1.2);
    post();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(8.9, 0.0, 0.0);
    glScalef(1.2, 1.6, 1.2);
    post();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(8.9, 0.0, -14.0);
    glScalef(1.2, 1.6, 1.2);
    post();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0, 6.4, -7.0);
    glScalef(3.6, 4.0, 2.5);
    // mainRoof1();
    glPopMatrix();

    //not used
    //back wall of the church
    glPushMatrix();
    glTranslatef(-8.0, 4.0, -7.0);
    glRotatef(90, 0.0f, 0.0f, 1.0f);
    glColor3f(1.0, 1.0, 1.0);
    drawFoundation(5.0f, 10.0f, 0.5f);
    glPopMatrix();



    glPushMatrix();
    glScalef(3.4, 2.9, 3.5);
    glTranslatef(2.0, 3.4, -2.0);
    coneUsingTriangles(0.2f, 2.0f, 8);
    glPopMatrix();

    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glScalef(1.0, 1.0, 1.0);
    glTranslatef(6.4, 9.3, -7.8);
    drawFourTrianglesAroundObject();
    glPopMatrix();


    glPushMatrix();
    drawFrontWallAndDoor();
    glPopMatrix();


    //to draw the ground applying th e cuboid
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glScalef(20, 3, 27); // Scale to the desired
    glTranslatef(0, -0.2, -0.25);
    glRotatef(90, 1.0f, 0.0f, 0.0f);
    //length,width,height

    GLfloat innerRadius = 0.0f;
    GLfloat outerRadius = 20.0f;
    GLfloat height = 0.0f;
    GLint slices = 36;
    GLint loops = 10;
    drawGround();

    glPopMatrix();


    //FRONT right
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glScalef(7, 5.4, 2);
    glTranslatef(0, 0.8, -5.0);
    glRotatef(90, 1.0f, 0.0f, 0.0f);

    //length,width,height
    drawCuboid(2.0f, 1.7f, 1.5f);
    glPopMatrix();


    //front left
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glScalef(-7, 5.4, 2);
    glTranslatef(0, 0.8, -2.0);
    glRotatef(90, 1.0f, 0.0f, 0.0f);
    drawCuboid(2.0f, 1.7f, 1.5f);
    glPopMatrix();


    //right cross
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glScalef(1.9, 1.9, 1.9);
    glTranslatef(4.0, 5, -3.8);
    glRotatef(90, 0.0f, 1.0f, 0.0f);
    drawCross();
    glPopMatrix();

    //left cross
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glScalef(1.9, 1.9, 1.9);
    glTranslatef(4.0, 5, -3.5);
    glRotatef(90, 0.0f, 1.0f, 0.0f);
    drawCross();
    glPopMatrix();

    //center cross
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glScalef(1.9, 1.9, 1.9);
    glTranslatef(4.0, 5.5, -3.6);
    glRotatef(90, 0.0f, 2.0f, 0.0f);
    drawCross();
    glPopMatrix();

    //toop of banner

    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glScalef(7, 5.4, 2);
    glTranslatef(0, 1.4, -3.5);
    glRotatef(90, 1.0f, 0.0f, 0.0f);
    //length,width,height
    topBanner(2.0f, 1.2f, 0.3f);
    glPopMatrix();

    //banner

    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glScalef(7, 5.4, 2);
    glTranslatef(0, 1.1, -3.5);
    glRotatef(90, 1.0f, 0.0f, 0.0f);
    //length,width,height
    banner(2.0f, 1.2f, 0.3f);
    glPopMatrix();


    //sphere
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    drawTexturedSphere(100.0f, 20, 20, 0.0f, 0.0f, 0.0f);
    glPopMatrix();

    //right door
    glPushMatrix();
    glRotatef(dRot2, 0, 1, 0);
    glTranslatef(8, 2.5, -8.5);
    glRotatef(90, 0.0f, 0.0f, 1.0f);
    //height,length,width
    //drawdoor(3.1, 0.5, 1.5, 1, 1, 1);
    glPopMatrix();

    //left door
    glPushMatrix();
    glRotatef(dRot1, 0, 1, 0);
    //glTranslatef(8, 2.5, -7.5);
    glTranslatef(5, 2.5, -7.5);
    glRotatef(90, 0.0f, 0.0f, 1.0f);
    drawdoorLeft(3.4, 0.8, 4.5, 1, 1, 1);
    glPopMatrix();

    //front glass like
    glPushMatrix();
    glScalef(1.2, 1.2, 1.2);
    glTranslatef(6.1, 6.7, -5.8);
    glRotatef(90, 0.0f, 1.0f, 0.0f);
    postWindowLikeWall();
    glPopMatrix();

    //large roof
    glPushMatrix();
    //z,y,x
    glScalef(14.2, 2.2, 6.1);
    glTranslatef(-0.1, 3.7, -1.1);
    glRotatef(90, 0.0f, 1.0f, 0.0f);
    drawTexturedTriangularPrism();
    glPopMatrix();


    glPushMatrix();
    glScalef(1.0, 0.6, 1.0);
    glRotatef(90, 0.0f, 1.0f, 0.0f);
    glTranslatef(-7.0, 0, 2);
    drawBench();
    glPopMatrix();

    glPushMatrix();
    glScalef(1.0, 0.6, 1.0);
    glRotatef(90, 0.0f, 1.0f, 0.0f);
    glTranslatef(-7.0, 0, -6);
    drawBench();
    glPopMatrix();

    glPushMatrix();
    glScalef(1.0, 1.0, 1.0);
    glTranslatef(0.0, 0, -22);
    glRotatef(270, 0.0f, 1.0f, 0.0f);
    drawBench();
    glPopMatrix();

    glPushMatrix();
    glScalef(1.0, 1.0, 1.0);
    glTranslatef(8.0, 0, -22);
    glRotatef(270, 0.0f, 1.0f, 0.0f);
    drawBench();
    glPopMatrix();

    //left margin
    glPushMatrix();
    glScalef(2.2, 3.2, 2.1);
    glTranslatef(0, 2, 6);
    drawCuboid(18, 0.5, 5, foundation);
    glPopMatrix();


    //right margin
    glPushMatrix();
    glScalef(2.2, 3.2, 2.1);
    glTranslatef(0, 2, -13);
    drawCuboid(18, 0.5, 5, foundation);
    glPopMatrix();

    //back margin
    glPushMatrix();
    glScalef(2.3, 3.2, 2.3);
    glTranslatef(-9, 2, -3.0);
    glRotatef(90, 0.0f, 1.0f, 0.0f);
    drawCuboid(18, 0.5, 5, foundation);
    glPopMatrix();

    //grass
    glPushMatrix();
    // glScalef(2.3, 3.2, 2.3);
    glTranslatef(9.5, 0, -7);
    glRotatef(90, 1.0f, 0.0f, 0.0f);
    drawGrass1();
    glPopMatrix();

    //glass left
    glPushMatrix();
    glScalef(0.5, 0.6, 0.3);
    glTranslatef(12, 10, -16);
    drawCuboid(5, 5, 5, glass);
    glPopMatrix();

    //glass right
    glPushMatrix();
    glScalef(0.5, 0.6, 0.3);
    glTranslatef(12, 10, -32);
    drawCuboid(5, 5, 5, glass);
    glPopMatrix();





    //right side back blocks
    glPushMatrix();
    //z,y,x
    glScalef(2.2, 3.2, 2.1);
    //  glTranslatef(-15, 0, 9);
    glTranslatef(-6, 0, -3);
    displayUnits();
    glPopMatrix();

    glPopMatrix();
    glutSwapBuffers();
}


void reshape(GLsizei w, GLsizei h) {
    glViewport(0, 0, w, h);
    GLfloat aspect_ratio = h == 0 ? w / 1 : (GLfloat)w / (GLfloat)h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(120.0, aspect_ratio, 1.0, 100.0);
}


void keyboardSpecial(int key, int x, int y) {
    if (key == GLUT_KEY_UP)
        camY += 1;
    if (key == GLUT_KEY_DOWN)
        camY -= 1;
    if (key == GLUT_KEY_RIGHT)
        sceTX += 1;
    if (key == GLUT_KEY_LEFT)
        sceTX -= 1;
    glutPostRedisplay();
}
void keyboard(unsigned char key, int x, int y) {


    if (key == 'O' || key == 'o') {
        if (doorAngleLeft < 90.0f) {
            doorAngleLeft += 5.0f;
        }
    }
    else if (key == 'C' || key == 'c') {
        if (doorAngleLeft > 0.0f) {
            doorAngleLeft -= 5.0f;
        }
    }


    if (key == 'l')
        objRY += 1;
    if (key == 'r')
        objRY -= 1;
    if (key == 'Z')
        sceTZ += 1;
    if (key == 'z')
        sceTZ -= 1;
    if (key == 'w')
        sceTX += 1;
    if (key == 's')
        sceTX -= 1;
    if (key == 'y')
        sceRY += 1;
    if (key == 'Y')
        sceRY -= 1;
    if (key == '!')
        glDisable(GL_LIGHT0); // Light at -x
    if (key == '1')
        glEnable(GL_LIGHT0);
    if (key == '@')
        glDisable(GL_LIGHT1); // Light at +x

    if (key == '2')
        glEnable(GL_LIGHT1);
    //Grids and axes
    if (key == 'G')
        gridOn = 1;
    if (key == 'g')
        gridOn = 0;
    if (key == 'A')
        axesOn = 1;
    if (key == 'a')
        axesOn = 0;
    glutPostRedisplay();
}



void main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(400, 400);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Texture Mapping-Defined pattern");
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(keyboardSpecial);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    init();
    glutMainLoop();
}

