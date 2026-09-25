#include "robo.h"
#include <math.h>

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
    glColor3f(R, G, B);
    glPointSize(2.0f);

    glBegin(GL_POINTS);
    for (GLint angle = 0; angle <= 360; angle += 20)
    {
        const GLfloat radians = angle * PI / 180.0f;
        glVertex2f(radius * cos(radians), radius * sin(radians));
    }
    glEnd();
}

void Robo::DesenhaRoda(GLfloat x, GLfloat y, GLfloat thetaWheel, GLfloat R, GLfloat G, GLfloat B)
{
    glPushMatrix();

    glTranslatef(x, y, 0.0f);
    glRotatef(thetaWheel, 0.0f, 0.0f, 1.0f);
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

    DesenhaRoda(-baseWidth / 2, 0.0f, thetaWheel, 0.0f, 1.0f, 1.0f);
    DesenhaRoda(baseWidth / 2, 0.0f, thetaWheel, 0.0f, 1.0f, 1.0f);

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
    Robo::gThetaWheel -= dx * 180.0f / (PI * radiusWheel);
}

// Funcao auxiliar de rotacao
void RotatePoint(GLfloat x, GLfloat y, GLfloat angle, GLfloat &xOut, GLfloat &yOut)
{
    const GLfloat radians = angle * PI / 180.0f;
    xOut = x * cos(radians) - y * sin(radians);
    yOut = x * sin(radians) + y * cos(radians);
}

Tiro *Robo::Atira()
{
    GLfloat baseX = 0.0f;
    GLfloat baseY = 0.0f;

    GLfloat pontaX = 0.0f;
    GLfloat pontaY = paddleHeight;

    // Transforma a base e a ponta da terceira haste de coordenadas
    // locais para coordenadas do mundo, na mesma ordem do desenho.
    RotatePoint(baseX, baseY, gTheta3, baseX, baseY);
    RotatePoint(pontaX, pontaY, gTheta3, pontaX, pontaY);

    baseY += paddleHeight;
    pontaY += paddleHeight;

    RotatePoint(baseX, baseY, gTheta2, baseX, baseY);
    RotatePoint(pontaX, pontaY, gTheta2, pontaX, pontaY);

    baseY += paddleHeight;
    pontaY += paddleHeight;

    RotatePoint(baseX, baseY, gTheta1, baseX, baseY);
    RotatePoint(pontaX, pontaY, gTheta1, pontaX, pontaY);

    baseY += baseHeight;
    pontaY += baseHeight;

    baseX += gX;
    baseY += gY;
    pontaX += gX;
    pontaY += gY;

    direction = atan2(pontaY - baseY, pontaX - baseX);

    return new Tiro(pontaX, pontaY, direction);
}
