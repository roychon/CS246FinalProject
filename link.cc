#include "link.h"

char Link::getId() {
    return id;
}

string Link::getType() {
    return type;
}

int Link::getStrength() {
    return strength;
}

int Link::getX() {
    return x;
}

int Link::getY() {
    return y;
}

Player &Link::getPlayer() {
    return *player;
}

// TODO: check if x is increment factor
void Link::setX(int x) {
    this->x += x;
}

// TODO: check if y is increment factor
void Link::setY(int y) {
    this->y += y;
}

void Link::setStrength(int strength) {
    this->strength = strength;
}

void Link::setType(string type) {
    this->type = type;
}

void Link::move(int x, int y) {
    this->x = x;
    this->y = y;
}

int Link::getMoveFactor() {
    return moveFactor;
}

bool Link::getIsRevealed() {
    return isRevealed;
}

void Link::revealLink() {
    isRevealed = true;
}
