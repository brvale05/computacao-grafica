#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#define TAMANHO_JANELA 500

// Pontos de controle da Spline
GLfloat ctrlpoints[4][3] = {
    {0.1, 0.1, 0.0},
    {0.3, 0.9, 0.0},
    {0.7, 0.1, 0.0},
    {0.9, 0.9, 0.0}};

int ponto_pressionado = -1;

int n = 30;

void mouse(int button, int state, int x, int y)
{
   // Ajeita a coordenada do y para o canto inferior esquerdo ser o (0,0)
   y = TAMANHO_JANELA - y;

   if (button == GLUT_LEFT_BUTTON)
   {
      if (state == GLUT_DOWN)
      {
         // Ajusta o raio de 30 pixels para o intervalo que estamos utilizando de 0.0 a 1.0
         float raio = 30.0 / (float)TAMANHO_JANELA;

         // Ajusta as coordenadas do X e do Y
         float newX = x / (float)TAMANHO_JANELA;
         float newY = y / (float)TAMANHO_JANELA;

         for (int i = 0; i < 4; i++)
         {
            float distX = newX - ctrlpoints[i][0];
            float distY = newY - ctrlpoints[i][1];

            float dist = sqrt(distX * distX + distY * distY);

            if (dist <= raio)
            {
               ponto_pressionado = i;
               break;
            }
         }
      }
      else if (state == GLUT_UP)
      {
         ponto_pressionado = -1;
      }
   }
}

void mouse_motion(int x, int y)
{
   if (ponto_pressionado != -1)
   {
      y = TAMANHO_JANELA - y;      
      ctrlpoints[ponto_pressionado][0] = x / (float)TAMANHO_JANELA;
      ctrlpoints[ponto_pressionado][1] = y / (float)TAMANHO_JANELA;
      glutPostRedisplay();
   }
}

void keyboard(unsigned char key, int x, int y)
{
   if (key == '+' || key == '=')
   {
      if (n < 100)
      {
         n++;
         glutPostRedisplay();
      }
   }
   else if (key == '-' || key == '_')
   {
      if (n > 2)
      {
         n--;
         glutPostRedisplay();
      }
   }
}


void init(void)
{
   glClearColor(0.0, 0.0, 0.0, 0.0);
   glShadeModel(GL_FLAT);
   glEnable(GL_MAP1_VERTEX_3);

   // Definicao do polinomio com os pontos de controle
   glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, &ctrlpoints[0][0]);

   // Muda para a matriz de projecao (aulas futuras)
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   // Define a area/volume de visualizacao. Os objetos desenhados devem estar dentro desta area
   glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
}

void display(void)
{
   int i;

   glClear(GL_COLOR_BUFFER_BIT);

   // Recalcula o polinômio
   glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, &ctrlpoints[0][0]);

   /* Desenha a curva aproximada por n+1 pontos. */
   glColor3f(1.0, 1.0, 1.0);
   glBegin(GL_LINE_STRIP);
   for (i = 0; i <= n; i++)
   {
      // Avaliacao do polinomio, retorna um vertice (equivalente a um glVertex3fv)
      glEvalCoord1f((GLfloat)i / (GLfloat)n);
   }
   glEnd();

   /* Desenha os pontos de controle. */
   glPointSize(5.0);
   glColor3f(1.0, 1.0, 0.0);
   glBegin(GL_POINTS);
   for (i = 0; i < 4; i++)
      glVertex3fv(&ctrlpoints[i][0]);
   glEnd();

   glutSwapBuffers();
}

int main(int argc, char **argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize(TAMANHO_JANELA, TAMANHO_JANELA);
   glutInitWindowPosition(100, 100);
   glutCreateWindow(argv[0]);
   init();

   glutDisplayFunc(display);

   glutMouseFunc(mouse);

   glutMotionFunc(mouse_motion);

   glutKeyboardFunc(keyboard);

   glutMainLoop();
   return 0;
}
