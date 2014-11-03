#include "Player.hpp"

Player::Player(const QString &name) : name_(name)
{

}

QString Player::name() const
{
	return name_;
}

void Player::updateAfter()
{

}

Prototype *Player::prototype(Prototype::Type type)
{

}
