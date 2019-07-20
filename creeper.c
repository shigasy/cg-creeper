[200~/*  p4-RotateTeaPot.c
 *  Rotating tea pot
 */
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

double	 theta = 0.0;						// angular of tea pot

void myKeyboard( unsigned char key, int x, int y )
{
    if ( key == 27 ) exit( 0 );
}

void myFloor()
{
	int i, j, idx, range = 100;
	double x, z, d = 0.05;

	for (i = -range; i <= range; i++) {
		x = i * d;
		for (j = -range; j <= range; j++) {
			z = j * d;
			idx = 0;
			if ( (abs(i) % 2) == (abs(j) % 2) ) idx = 1;
			glBegin(GL_QUADS);
			if (idx) glColor3d(0.0, 0.2, 0.0);
			// else glColor3d(0.0, 0.5, 0.0);
			glNormal3b(0.0, 1.0, 0.0);
			glVertex3d(x, 0.0, z);
			glVertex3d(x, 0.0, z + d);
			glVertex3d(x + d, 0.0, z + d);
			glVertex3d(x + d, 0.0, z);
			glEnd();
		}
	}
}

void myDisplay(void)
{

	glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();
		glTranslated(0.0, -3.0, 0.0);
		myFloor();
	glPopMatrix();


	glRotated(theta, 0.0, 1.0, 0.0);

	glPushMatrix();

	// head
	glPushMatrix();
		glColor3d(1.0, 1.0, 1.0);
		glutWireCube(1.0);
		//glutWireTeapot(1.0);
	glPopMatrix();
	// body
	glTranslated(0.0, -1.5, 0.0);
	glPushMatrix();
		glColor3d(1.0, 1.0, 1.0);
		glScaled(0.9, 2.0, 0.5);
		glutSolidCube(1.0);
	glPopMatrix();
	// foot1
	glTranslated(0.0, -1.5, 0.0);
	glPushMatrix();
		glColor3d(1.0, 1.0, 1.0);
		glTranslated(0.0, 0.0, 0.5);
		glScaled(0.9, 1.0, 0.5);
		glutWireCube(1.0);
	glPopMatrix();
	// foot2
		glPushMatrix();
		glColor3d(1.0, 1.0, 1.0);
		glTranslated(0.0, 0.0, -0.5);
		glScaled(0.9, 1.0, 0.5);
		glutWireCube(1.0);
	glPopMatrix();


	glPopMatrix();


    glutSwapBuffers(); 

}

void myIdle(void)
{
	theta = fmod(theta + 0.001, 360.0);
	glutPostRedisplay();
}

void myInit (char *progname)
{
    int width = 500, height = 500;

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize( width, height);
	glutInitWindowPosition(0, 0); 
	glutCreateWindow(progname);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.0, (double)width/(double)height, 0.1, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 1.0, 3.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv); 
	myInit(argv[0]);
	glutKeyboardFunc(myKeyboard);
	glutIdleFunc(myIdle);
	glutDisplayFunc(myDisplay);
	glutMainLoop(); 
	return 0;
}
