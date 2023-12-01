#include "link.h"

Link::Link(): strength{0}, isRevealed{false}, x{-1}, y{-1}, player{nullptr}, moveFactor{1} {}

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

int Link::getMoveFactor() {
    return moveFactor;
}

bool Link::getIsRevealed() {
    return isRevealed;
}

void Link::setId(char id) {
    this->id = id;
}

// TODO: check if x is increment factor
void Link::setX(int x) {
    this->x = x;
}

// TODO: check if y is increment factor
void Link::setY(int y) {
    this->y = y;
}

void Link::setStrength(int strength) {
    this->strength = strength;
}

void Link::setType(string type) {
    this->type = type;
}

void Link::setPlayer(Player *player) {
    this->player = player;
}

void Link::move(int x, int y) {
    this->x = x;
    this->y = y;
}

void Link::revealLink() {
    isRevealed = true;
}

void Link::setMoveFactor(int factor) {
    moveFactor += factor;
}
