#include "tiro.h"
#include <math.h>
#define DISTANCIA_MAX 200

void Tiro::DesenhaCirc(GLint radius, GLfloat R, GLfloat G, GLfloat B)
{
    glColor3f(R, G, B);

    glBegin(GL_POLYGON);
    for (GLfloat angle = 0; angle <= 360; angle += 20)
    {
        const GLfloat radians = angle * PI / 180.f;
        glVertex2f(radius * cos(radians), radius * sin(radians));
    }
    glEnd();
}

void Tiro::DesenhaTiro(GLfloat x, GLfloat y)
{
    glPushMatrix();

    glTranslatef(x, y, 0.0f);
    DesenhaCirc(radiusTiro, 1.0f, 0.0f, 0.0f);

    glPopMatrix();
}

void Tiro::Move(GLdouble time)
{
    Tiro::gX += cos(gDirectionAng) * gVel * time;
    Tiro::gY += sin(gDirectionAng) * gVel * time;
}

bool Tiro::Valido()
{
    GLfloat dx = gX - gXInit;
    GLfloat dy = gY - gYInit;

    return dx * dx + dy * dy <= DISTANCIA_MAX * DISTANCIA_MAX;
}
