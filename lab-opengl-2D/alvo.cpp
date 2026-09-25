#include "alvo.h"
#include <math.h>

void Alvo::DesenhaCirc(GLint radius, GLfloat R, GLfloat G, GLfloat B)
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

void Alvo::DesenhaAlvo(GLfloat x, GLfloat y)
{
    glPushMatrix();

    glTranslatef(x, y, 0);

    switch (gColor)
    {
    case 0:
        DesenhaCirc(radiusAlvo, 1.0f, 0.0f, 0.0f);
        break;
    case 1:
        DesenhaCirc(radiusAlvo, 0.0f, 1.0f, 0.0f);
        break;
    case 2:
        DesenhaCirc(radiusAlvo, 0.0f, 0.0f, 1.0f);
        break;
    default:
        break;
    }
    
    glPopMatrix();
}

void Alvo::Recria(GLfloat x, GLfloat y)
{
    Alvo::gX = x;
    Alvo::gY = y;

    Alvo::gColor = Alvo::gColor + 1 > 2 ? 0 : Alvo::gColor + 1;
}

bool Alvo::Atingido(Tiro *tiro)
{
    float tiroX, tiroY;
    tiro->GetPos(tiroX, tiroY);

    float distX = Alvo::gX - tiroX;
    float distY = Alvo::gY - tiroY;

    float dist = sqrt(distX * distX + distY * distY);

    if (dist <= radiusAlvo)
    {
        return true;
    }
    else
    {
        return false;
    }
}
