/* W B Langdon at MUN 10 May 2007
 * Program to demonstarte use of OpenGL's glDrawPixels
 */

#include <GL/gl.h>
#include <GL/glut.h>

#include <math.h>
#include <iostream>
#include "Pixel.h"
#include "Canvas.h"
#include "Camera.h"
#include "Box.h"

Canvas *canvas;
Camera *camera;
Box *box;
unsigned int frame_count;

void init();


void display() {
	auto timebase = glutGet(GLUT_ELAPSED_TIME);
	while(1) {
		frame_count++;
		auto currenttime = glutGet(GLUT_ELAPSED_TIME);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		canvas->clear(0, 0.15, 0.5);
		canvas->update();

		glutSwapBuffers();

		//check if a second has passed
		if (currenttime - timebase > 1000)
		{
			std::cout << "fps: " << frame_count*1000.0/(currenttime - timebase) << std::endl;
			timebase = currenttime;
			frame_count = 0;
		}
	}
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);

	init();

	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(window_width, window_height);
	glutCreateWindow("netease startup");

	glutDisplayFunc(display);
	//glutReshapeFunc(reshape);
	//glutMouseFunc(mouse_button);
	//glutMotionFunc(mouse_motion);
	//glutKeyboardFunc(keyboard);
	//glutIdleFunc(idle);

	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	//glPointSize(2);

	glutMainLoop();

	return 0;
}



void init() {
	canvas = new Canvas(window_width, window_height);
	/*todo:*/
	camera = new Camera(Pos3D(400, 600, -400), Pos3D(0, 1, 0), 1);
	box = new Box(Pos3D(0, 0, 0), 300);

}