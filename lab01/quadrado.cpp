#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h>
#define TAMANHO_JANELA 500

float gX = 0.0;
float gY = 0.0;

float offsetX = 0.0;
float offsetY = 0.0;

int arrastando = 0;

float MOVIMENTO = 0.001;

// pressionado = 1, não pressionado = 0
int keyStatus[256];

void keyPress(unsigned char key, int x, int y)
{
   keyStatus[(int)(key)] = 1;

   glutPostRedisplay();
}

void keyUp(unsigned char key, int x, int y)
{
   keyStatus[(int)(key)] = 0;

   glutPostRedisplay();
}

void mouse(int button, int state, int x, int y)
{
   y = TAMANHO_JANELA - y;

   float newX = x / (float)TAMANHO_JANELA;
   float newY = y / (float)TAMANHO_JANELA;

   if (button == GLUT_LEFT_BUTTON)
   {
      if (state == GLUT_DOWN)
      {
         if (newX >= (0.25 + gX) && newX <= (0.75 + gX) &&
             newY >= (0.25 + gY) && newY <= (0.75 + gY))
         {
            arrastando = 1;

            offsetX = newX - gX;
            offsetY = newY - gY;
         }
      }
      else if (state == GLUT_UP)
      {
         arrastando = 0;
      }
   }

}

void arrastar(int x, int y)
{
   if (arrastando)
   {
      y = TAMANHO_JANELA - y;
      float mouseX = x / (float)TAMANHO_JANELA;
      float mouseY = y / (float)TAMANHO_JANELA;
      // Atualiza a posição do quadrado mantendo o offset inicial
      gX = mouseX - offsetX;
      gY = mouseY - offsetY;
      glutPostRedisplay();
   }
}

void idle(void)
{
   if (keyStatus[(int)('w')])
      gY += MOVIMENTO;

   if (keyStatus[(int)('s')])
      gY -= MOVIMENTO;

   if (keyStatus[(int)('d')])
      gX += MOVIMENTO;

   if (keyStatus[(int)('a')])
      gX -= MOVIMENTO;

   glutPostRedisplay();
}

void display(void)
{
   /* Limpar todos os pixels  */
   glClear(GL_COLOR_BUFFER_BIT);

   /* Define cor dos vértices com os valores R, G e B variando de 0.0 a 1.0 */
   glColor3f(1.0, 0.0, 0.0);
   /* Desenhar um polígono branco (retângulo) */
   glBegin(GL_POLYGON);
   glVertex3f(0.25 + gX, 0.25 + gY, 0.0);
   glVertex3f(0.75 + gX, 0.25 + gY, 0.0);
   glVertex3f(0.75 + gX, 0.75 + gY, 0.0);
   glVertex3f(0.25 + gX, 0.75 + gY, 0.0);
   glEnd();

   /* Desenhar no frame buffer! */
   glutSwapBuffers(); // Funcao apropriada para janela double buffer
}

void init(void)
{
   /* selecionar cor de fundo (preto) */
   glClearColor(0.0, 0.0, 0.0, 0.0);

   /* inicializar sistema de visualizacao */
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
}

int main(int argc, char **argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize(TAMANHO_JANELA, TAMANHO_JANELA);
   glutInitWindowPosition(100, 100);
   glutCreateWindow("hello world");
   init();

   glutDisplayFunc(display);

   glutKeyboardFunc(keyPress);

   glutKeyboardUpFunc(keyUp);

   glutIdleFunc(idle);

   glutMouseFunc(mouse);

   glutMotionFunc(arrastar);

   glutMainLoop();

   return 0;
}
