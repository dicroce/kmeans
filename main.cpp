
#include <stdio.h>
#include <vector>
#include <random>

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "kmeans.h"

#define PI 3.141592
#define NUM_POINTS 1000
#define WORLD_WIDTH 1000
#define WORLD_HEIGHT 1000

std::vector<std::vector<float>> points;
kmeans<float> km;
std::vector<std::vector<float>> clusters;

void display()
{
  /* set fill color to white */
  glColor3f(1.0, 1.0, 1.0);

  for( auto p : points )
  {
      float objX = -(WORLD_WIDTH/2) + p[0];
      float objY = -(WORLD_HEIGHT/2) + p[1];

            /* draw unit square polygon */
      glBegin( GL_POLYGON );
        glVertex2f(  objX+(-1.0),      objY+(-1.0) );
        glVertex2f(  objX+(1.0),       objY+(-1.0) );
        glVertex2f(  objX+(1.0),       objY+(1.0) );
        glVertex2f(  objX+(-1.0),      objY+(1.0) );
      glEnd();

  }

  glColor3f( 1.0, 0.0, 0.0 );

  auto centers = km.get_centers();

  for( auto c : centers )
  {
      float clusterAX = -(WORLD_WIDTH/2) + c[0];
      float clusterAY = -(WORLD_HEIGHT/2) + c[1];

      glBegin( GL_POLYGON );
        glVertex2f(  clusterAX+(-10.0),      clusterAY+(-10.0) );
        glVertex2f(  clusterAX+(10.0),       clusterAY+(-10.0) );
        glVertex2f(  clusterAX+(10.0),       clusterAY+(10.0) );
        glVertex2f(  clusterAX+(-10.0),      clusterAY+(10.0) );
      glEnd();
  }

  glFlush();

  glutSwapBuffers();
}

void populate_data_points( int numClusters = 2 )
{
    points.clear();
    km.clear();

    int pointsPerCluster = (NUM_POINTS / numClusters);

    for( int i = 0; i < numClusters; i++ )
    {
        float clusterX = random() % WORLD_WIDTH;
        float clusterY = random() % WORLD_HEIGHT;

        float magCurve = 0;

        for( int ii = 0; ii < pointsPerCluster; ii++ )
	{
            float direction = (random() % 360);
            float directionRadians = direction * PI / 180;
            float slope = tan( directionRadians );
            float magnitude = (random() % 200);
            float y = clusterY + (sin( directionRadians ) * magnitude);
            float x = clusterX + (cos( directionRadians) * magnitude);

            std::vector<float> row = { x, y };
            points.push_back( row );

            km.add_data_point( points.back().begin(), points.back().end() );
	}
    }

    km.add_center();
    km.add_center();
}

void do_kmeans( int value )
{
  glClear( GL_COLOR_BUFFER_BIT );

  // New k-means run, so regenerate a dataset...
  populate_data_points( 2 );

  while( km.cluster() );

  glutPostRedisplay();

  glutTimerFunc( 2000, do_kmeans, 0 );
}

void init()
{
  srand( time(0) );

  glClearColor (0.0, 0.0, 0.0, 0.0);

  /* set up standard orthogonal view with clipping */
  /* box as cube of side 2 centered at origin */
  /* This is default view and these statement could be removed */
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity ();
  glOrtho(-500.0, 500.0, -500.0, 500.0, -1.0, 1.0);

  glClear( GL_COLOR_BUFFER_BIT );
}

int main(int argc, char** argv)
{
  glutInit( &argc, argv );

  glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB );

  glutInitWindowSize( 800, 600 );

  glutInitWindowPosition( 0, 0 );

  glutCreateWindow( "kmeans" );

  glutDisplayFunc( display );

  init();

  do_kmeans( 0 );

  glutMainLoop();
}
