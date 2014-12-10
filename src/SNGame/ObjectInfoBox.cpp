#include "ObjectInfoBox.hpp"
#include "../SNCore/Player.hpp"
#include <qlocale.h>
#include <QPaintEvent>
#include <QPainter>
#include <QMenu>

ObjectInfoBox::ObjectInfoBox(QWidget *parent) : QWidget(parent), displayed_(0)
{
	hide();
	objectName_ = new StatDisplay(tr("Object"), this);
	playerName_ = new StatDisplay(tr("Player"), this);
	unitDamage_ = new StatDisplay(tr("Damage"), this);
	unitRange_ = new StatDisplay(tr("Range"), this);
	unitMoveRange_ = new StatDisplay(tr("Move"), this);
	
	for (ActionType type : ActionType::labels()) {
		ActionButton *button =  new ActionButton(type, this);
		actionButtons_.insert(type, button);
		connect(button, &ActionButton::clicked, this, &ObjectInfoBox::hideAll);
		connect(button, &ActionButton::performed, this, &ObjectInfoBox::actionPerformed);
	}
}

ObjectInfoBox::~ObjectInfoBox()
{
	
}

void ObjectInfoBox::setObject(const Object *object, const QVector<Action *> &actions)
{
	hideAll();
	objectName_->setValue(object->name());
	displayStat(objectName_);
	playerName_->setValue(object->owner()->name());
	displayStat(playerName_);
	if (object->type() == ObjectType::Town) {
		displayButton(actionButtons_[ActionType::CreateUnit]);
	} else if (object->type() == ObjectType::Unit) {
		const Unit *unit = dynamic_cast<const Unit *>(object);
		unitMoveRange_->setValue(unit->actionPointsLeft());
		displayStat(unitMoveRange_);
		
		if (unit->pType() ==  PrototypeType::Settler) {
			displayButton(actionButtons_[ActionType::Settle]);
		} else if (unit->pType() == PrototypeType::Infantry) {
		}
	}
	for (Action *action : actions) {
		ActionButton *actionButton = actionButtons_[action->type()];
		actionButton->addAction(action);
		actionButton->setDisabled(false);
	}
	show();
}

void ObjectInfoBox::displayStat(StatDisplay *stat)
{
	stat->show();
	stat->setGeometry(0, 50 * displayed_, size().width(), 50);
	++displayed_;
}

void ObjectInfoBox::displayButton(ActionButton *button)
{
	button->show();
	button->setGeometry(0, 50 * displayed_, size().width(), 50);
	++displayed_;
}

void ObjectInfoBox::hideAll()
{
	displayed_ = 0;
	unitDamage_->hide();
	unitRange_->hide();
	unitMoveRange_->hide();
	for (ActionButton *actionButton : actionButtons_)
		actionButton->clear();
}

QSize ObjectInfoBox::minimumSizeHint() const
{
	return ObjectInfoBox::sizeHint();
}

QSize ObjectInfoBox::sizeHint() const
{
	return QSize(200, 500);
}

void ObjectInfoBox::paintEvent(QPaintEvent *e)
{
	QPainter *painter = new QPainter(this);
	painter->fillRect(0,0, size().width(), size().height(), QBrush(Qt::darkGray));
}

void ObjectInfoBox::resizeEvent(QResizeEvent *e)
{
	QWidget::resizeEvent(e);
}


/*---------------StatDisplay---------------------*/


StatDisplay::StatDisplay(const QString &stat, QWidget *parent): QLabel(parent), stat_(stat)
{
	setValue(0);
	hide();
}


void StatDisplay::setValue(int v)
{
	setText(stat_ + " : " + QString::number(v));
}

void StatDisplay::setValue(const QString &text)
{
	setText(stat_ + " : " + text);
}



/*--------------ActionButton------------------*/

ActionButton::ActionButton(ActionType type, QWidget *parent): 
	QPushButton((QString)(type) ,parent), type_(type)
{
	clear();
	connect(this, &ActionButton::clicked, this, &ActionButton::perform);
}

void ActionButton::perform()
{
	if (actions_.empty())
		return;
	
	if (actions_.size() == 1) {
		actions_.first()->perform();
		emit performed();
	}
}

void ActionButton::addAction(Action *action)
{
	if (action->type() != type_)
		return;
	
	actions_.push_back(action);
	
	if (actions_.size() <= 1)
		return;
	
	if (menu() == nullptr) {
		setMenu(new QMenu((QString)(type_), this));
		QAction *menuAction = menu()->addAction((QString)(type_));
		connect(menuAction, &QAction::triggered, [this](){actions_.first()->perform();});
		connect(menuAction, &QAction::triggered, this, &ActionButton::performed);
	}
	
	QAction *menuAction = menu()->addAction((QString)(type_));
	connect(menuAction, &QAction::triggered, [action](){action->perform();});
	connect(menuAction, &QAction::triggered, this, &ActionButton::performed);
}

void ActionButton::clear()
{
	actions_.clear();
	hide();
	setDisabled(true);
	if (menu() != nullptr) {
		delete menu();
		setMenu(nullptr);
	}
}


