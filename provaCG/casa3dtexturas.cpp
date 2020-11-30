#include <GL\glut.h>
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
using namespace std;

GLuint texID[2];
float width = 10; 
float height = 10;


void telhado(float size, GLuint texid){
	glBindTexture(GL_TEXTURE_2D, texid);
	
	glBegin(GL_TRIANGLES);
		glColor3f(1.0f, 0.0f, 0.0f);
		glTexCoord2f(0,0);	glVertex3f(0, size*3, 0);
		glTexCoord2f(1,0);	glVertex3f(-size, size*2, size);
		glTexCoord2f(1,1);	glVertex3f(size,size*2,size);
	glEnd();
	
	glBindTexture(GL_TEXTURE_2D, texid);
	
	glBegin(GL_TRIANGLES);
		glColor3f(1.0f, 0.0f, 0.0f);
	glTexCoord2f(0,0);	glVertex3f(0,size*3,0);
	glTexCoord2f(1,0);	glVertex3f(size, size*2, -size);
	glTexCoord2f(1,1);	glVertex3f(size, size*2, -size);
	glEnd();
	
	glBindTexture(GL_TEXTURE_2D, texid);
	
	glBegin(GL_TRIANGLES);
		glColor3f(1.0f, 0.0f, 0.0f);
	glTexCoord2f(0,0);	glVertex3f(0,size*3,0);
	glTexCoord2f(1,0);	glVertex3f(-size, size*2, -size);
	glTexCoord2f(1,1);	glVertex3f(size, size*2, -size);
	glEnd();
	
	glBindTexture(GL_TEXTURE_2D, texid);
	
	glBegin(GL_TRIANGLES);
		glColor3f(1.0f, 0.0f, 0.0f);
	glTexCoord2f(0,0);	glVertex3f(0, size*3, 0);
	glTexCoord2f(1,0);	glVertex3f(-size, size*2, -size);
	glTexCoord2f(1,1);	glVertex3f(-size, size*2, size);
	glEnd();

}
void cubo(float size, GLuint texid){
	glBindTexture(GL_TEXTURE_2D, texid);
	glColor3f(1.0, 1.0,1.0);
	glBegin(GL_QUADS);		
	
	
	  	glTexCoord2f(0,0);	glVertex3f( -size,  0,  size );
	  	glTexCoord2f(1,0);	glVertex3f( -size, size*2,  size );
	  	glTexCoord2f(1,1);	glVertex3f(  size,  size*2,  size );
	  	glTexCoord2f(0,1);  glVertex3f(  size,  0,  size);

	  
	  	glTexCoord3f(0,1,0);	glVertex3f( -size,  0, -size );
	  	glTexCoord3f(1,1,1);	glVertex3f(  size,  0, -size );
	  	glTexCoord3f(1,0,1);	glVertex3f(  size,  size*2, -size );
	  	glTexCoord3f(0,0,0);	glVertex3f( -size,  size*2, -size );

	
	  		
	  	glTexCoord3f(0,1,0);	glVertex3f( -size,  0,  size );
	  	glTexCoord3f(1,1,1);	glVertex3f( -size,  size*2,  size );
	  	glTexCoord3f(1,0,1);	glVertex3f( -size,  size*2, -size );
	  	glTexCoord3f(0,0,0);	glVertex3f( -size,  0, -size );


	  	glTexCoord2f(0,0);	glVertex3f(  size,  0,  size );
	  	glTexCoord2f(1,0);	glVertex3f(  size,  0, -size );
	  	glTexCoord2f(1,1);	glVertex3f(  size,  size*2, -size );
	  	glTexCoord2f(0,1);	glVertex3f(  size,  size*2,  size );
	glEnd();

	
}

void desenho(){
	glClearColor(1,1,1,0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	telhado(height, texID[1]);
	cubo(width, texID[0]);
	glRotatef(2,0,1,0);
	glFlush();
	
}


void ajuste(int w, int h){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	gluPerspective(45, w/h, 0.4, 500);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	gluLookAt(50,0,150,0,0,0,0,1,0);
	
}

void anima(int value){
	glutPostRedisplay();
	glutTimerFunc(30, anima, 1);
}

void initLight(){
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_COLOR_MATERIAL);
	
	float luzAmbiente[4] = {0.1,0.1,0.1,1};
	float luzDifusa[4] = {0.7,0.7,0.7,1};
	float luzEspecular[4] = {1,1,1,1};
	float posicaoLuz0[4] = {500,20,0,1};
	float posicaoLuz1[4] = {-500,20,0,1};
	float especularidade[4] = {1,1,1,1};
	int especMaterial = 128;
	
	glMaterialfv(GL_FRONT, GL_SPECULAR, especularidade);
	glMaterialf(GL_FRONT, GL_SHININESS, especMaterial);
	
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);
	
	glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa);
	glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular);
	glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz0);
	
	glLightfv(GL_LIGHT1, GL_AMBIENT, luzAmbiente);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, luzDifusa);
	glLightfv(GL_LIGHT1, GL_SPECULAR, luzEspecular);
	glLightfv(GL_LIGHT1, GL_POSITION, posicaoLuz1);
	
	glEnable(GL_DEPTH_TEST);
}

void carregarTextura(GLuint tex_id, string filepath){
        unsigned char* imgData;
        int largura, altura, canais;
        
        stbi_set_flip_vertically_on_load(true);
        imgData = stbi_load(filepath.c_str(), &largura, &altura,&canais, 4);
       
        if(imgData){
                glBindTexture(GL_TEXTURE_2D, tex_id);
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, largura,
                altura, 0, GL_RGBA, GL_UNSIGNED_BYTE, imgData);
               
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
               
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
               
                stbi_image_free(imgData);
        }else{
                cout<<"ERRO!Não foi possível carregar a imagem "<<filepath.c_str()<<endl;
        }
}
 
 
void initializeTexture(){
        glGenTextures(3, texID);
        glEnable(GL_TEXTURE_2D);
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_ONE_MINUS_SRC_ALPHA);
        carregarTextura(texID[0], "images/tijolos.png");
        carregarTextura(texID[1], "images/madeira.png");
        //carregarTextura(texID[2], "images/painted_brick.png");
        
        glEnable(GL_DEPTH_TEST);
}

int main(){
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(200,100);
	glutInitWindowSize(800,800);
	glutCreateWindow("Casinha em 3D");
	glutDisplayFunc(desenho);
	glutReshapeFunc(ajuste);
	glEnable(GL_DEPTH_TEST);
	glutTimerFunc(30, anima, 1);
	initializeTexture();
	//initLight();
	glutMainLoop();
}
