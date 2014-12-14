#ifndef CREATETOWNACTION_HPP
#define CREATETOWNACTION_HPP

#include "Action.hpp"

class Player;

class CreateTownAction : public Action {
public:
	virtual bool perform() override;
protected:
	CreateTownAction(Player * player, Tile *tile, const QString &name = "BaseName");
	Player *player_;
	QString name_;
	
};

#endif
