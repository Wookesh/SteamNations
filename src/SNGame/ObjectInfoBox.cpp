#include "ObjectInfoBox.hpp"
#include <qlocale.h>
#include <QPaintEvent>
#include <QPainter>
#include <QMenu>

ObjectInfoBox::ObjectInfoBox(QWidget *parent) : QWidget(parent), displayed_(0)
{
	hide();
	nameDisplay_ = new QLabel(tr("Object Name"), this);
	nameDisplay_->setGeometry(0, 0, sizeHint().width(), 50);
	
	unitDamage_ = new StatDisplay(tr("Damage"), this);
	unitRange_ = new StatDisplay(tr("Range"), this);
	unitMoveRange_ = new StatDisplay(tr("Move"), this);
	
	for (Action::Type type : Action::types()) {
		ActionButton *button =  new ActionButton(type, this);
		actionButtons_.insert(type, button);
		connect(button, &ActionButton::clicked, this, &ObjectInfoBox::hideAll);
	}
}

ObjectInfoBox::~ObjectInfoBox()
{
	
}

void ObjectInfoBox::setObject(const Object *object, const QVector<Action *> &actions)
{
	hideAll();
	nameDisplay_->setText(object->name());
	switch (object->type()) {
		case Unit::Type::Town: {
			displayButton(actionButtons_[Action::Type::CreateUnit]);
			break;
		}
		case Unit::Type::Unit: {
			const Unit *unit = dynamic_cast<const Unit *>(object);
			unitMoveRange_->setValue(unit->currentMoveRange());
			displayStat(unitMoveRange_);
			switch (unit->pType()) {
				case Prototype::Type::Settler : {
					displayButton(actionButtons_[Action::Type::Settle]);
					break;
				}
				case Prototype::Type::Soldier : {
					break;
				}
			}
			break;
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
	stat->setGeometry(0, 50 * (displayed_ + 1), size().width(), 50);
	++displayed_;
}

void ObjectInfoBox::displayButton(ActionButton *button)
{
	button->show();
	button->setGeometry(0, 50 * (displayed_ + 1), size().width(), 50);
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
	val_ = v;
	setText(stat_ + " : " + QString::number(val_));
}


/*--------------ActionButton------------------*/

ActionButton::ActionButton(Action::Type type, QWidget *parent): 
	QPushButton(Action::name(type) ,parent), type_(type)
{
	clear();
	connect(this, &ActionButton::clicked, this, &ActionButton::perform);
}

void ActionButton::perform()
{
	if (actions_.empty())
		return;
	
	if (actions_.size() == 1)
		actions_.first()->perform();
}

void ActionButton::addAction(Action *action)
{
	if (action->type() != type_)
		return;
	
	actions_.push_back(action);
	
	if (actions_.size() <= 1)
		return;
	
	if (menu() == nullptr) {
		setMenu(new QMenu(Action::name(type_), this));
		QAction *menuAction = menu()->addAction(Action::name(type_));
		connect(menuAction, &QAction::triggered, [this](){actions_.first()->perform();});
	}
	
	QAction *menuAction = menu()->addAction(Action::name(type_));
	connect(menuAction, &QAction::triggered, [action](){action->perform();});
}

void ActionButton::clear()
{
	actions_.clear();
	hide();
	setDisabled(true);
}


