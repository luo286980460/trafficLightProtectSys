#include "screen.h"

Screen::Screen(QObject *parent)
    : QObject{parent}
{}

int Screen::getId()
{
    return m_id;
}
