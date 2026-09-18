#include "robo.h"
#include <math.h>

#define PI 3.14159265358979323846

void Robo::DesenhaRect(GLint height, GLint width, GLfloat R, GLfloat G, GLfloat B)
{
    glColor3f(R, G, B);

    glBegin(GL_POLYGON);

    glVertex2i(-width / 2, 0);
    glVertex2i(width / 2, 0);
    glVertex2i(width / 2, height);
    glVertex2i(-width / 2, height);

    glEnd();
}

void Robo::DesenhaCirc(GLint radius, GLfloat R, GLfloat G, GLfloat B)
{
    int PONTOS = 100;
    float angulo;
    
    glBegin(GL_POLYGON);

    glColor3f(1.0f, 0.0f, 0.0f); // Cor vermelha

    for (int i = 0; i < PONTOS; i++)
    {
        angulo = (2.0 * PI * i) / PONTOS;
        glVertex2f(
            radius * cos(angulo),
            radius * sin(angulo));
    }
    glEnd();
}

void Robo::DesenhaRoda(GLfloat x, GLfloat y, GLfloat thetaWheel, GLfloat R, GLfloat G, GLfloat B)
{
    glPushMatrix();

    glTranslatef(x, y, 0);

    DesenhaRect(baseHeight, baseWidth, 0, 0, GL_BLUE);

    glRotatef(thetaWheel, 0, 0, 1);

    DesenhaCirc(radiusWheel, R, G, B);
    
    glPopMatrix();
}

void Robo::DesenhaBraco(GLfloat x, GLfloat y, GLfloat theta1, GLfloat theta2, GLfloat theta3)
{
    glPushMatrix();

    /* ----- DESENHA PRIMEIRA HASTE ----- */
    glTranslatef(x, y, 0);
    glRotatef(theta1, 0, 0, 1);
    DesenhaRect(paddleHeight, paddleWidth, 0.0, 0.0, GL_BLUE);
    /* ---------------------------------- */

    /* ----- DESENHA SEGUNDA HASTE ----- */
    glTranslatef(0.0, paddleHeight, 0.0);
    glRotatef(theta2, 0, 0, 1);
    DesenhaRect(paddleHeight, paddleWidth, GL_RED, GL_GREEN, 0);
    /* -------------------------------- */

    /* ----- DESENHA TERCEIRA HASTE ----- */
    glTranslatef(0.0, paddleHeight, 0.0);
    glRotatef(theta3, 0, 0, 1);
    DesenhaRect(paddleHeight, paddleWidth, 0, GL_GREEN, 0);
    /* ---------------------------------- */

    glPopMatrix();
}

void Robo::DesenhaRobo(GLfloat x, GLfloat y, GLfloat thetaWheel, GLfloat theta1, GLfloat theta2, GLfloat theta3)
{
    glPushMatrix();

    glTranslatef(x, y, 0.0);
    DesenhaRect(baseHeight, baseWidth, GL_RED, 0.0, 0.0);

    DesenhaBraco(0.0, baseHeight, theta1, theta2, theta3);

    /* ---- DESENHA RODA ESQUERDA ---- */
    DesenhaRoda(-baseWidth/2, 0.0, thetaWheel, 0.0, GL_GREEN, GL_BLUE);
    /* ------------------------------ */

    /* ---- DESENHA RODA DIREITA ---- */
    DesenhaRoda(baseWidth/2, 0.0, thetaWheel, 0.0, GL_GREEN, GL_BLUE);
    /* ------------------------------ */

    glPopMatrix();
}

void Robo::RodaBraco1(GLfloat inc)
{
    Robo::gTheta1 += inc;
}

void Robo::RodaBraco2(GLfloat inc)
{
    Robo::gTheta2 += inc;
}

void Robo::RodaBraco3(GLfloat inc)
{
    Robo::gTheta3 += inc;
}

void Robo::MoveEmX(GLfloat dx)
{
    Robo::gX += dx;
}

// Funcao auxiliar de rotacao
void RotatePoint(GLfloat x, GLfloat y, GLfloat angle, GLfloat &xOut, GLfloat &yOut)
{
}

Tiro *Robo::Atira()
{
}
