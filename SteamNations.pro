TEMPLATE = app

QT += qml quick core opengl

CONFIG += c++11

INCLUDEPATH += . \
               src/SNCore \
					src/SNGame \
					src

SOURCES += src/SNCore/Board.cpp \
           src/SNCore/Console.cpp \
           src/SNCore/GameManager.cpp \
           src/SNCore/Player.cpp \
           src/SNCore/Tile.cpp \
           src/SNCore/Actions/Action.cpp \
           src/SNCore/Actions/AttackAction.cpp \
           src/SNCore/Actions/CaptureAction.cpp \
           src/SNCore/Actions/CreateTownAction.cpp \
           src/SNCore/Actions/CreateUnitAction.cpp \
           src/SNCore/Actions/MoveAction.cpp \
           src/SNCore/Actions/SettleAction.cpp \
           src/SNCore/Actions/SpawnUnitAction.cpp \
           src/SNCore/Bonuses/Bonus.cpp \
           src/SNCore/Bonuses/DefenseBonuses.cpp \
           src/SNCore/Bonuses/EconomyBonuses.cpp \
           src/SNCore/Bonuses/WarfareBonuses.cpp \
           src/SNCore/Objects/Object.cpp \
           src/SNCore/Objects/Settler.cpp \
           src/SNCore/Objects/Soldier.cpp \
           src/SNCore/Objects/Town.cpp \
           src/SNCore/Objects/Unit.cpp \
           src/SNCore/Objects/Prototypes/Prototype.cpp \
           src/SNCore/Objects/Prototypes/SettlerPrototype.cpp \
           src/SNCore/Objects/Prototypes/SoldierPrototype.cpp \
           src/SNGame/BoardField.cpp \
           src/SNGame/GameBoard.cpp \
           src/SNGame/InfoBox.cpp \
           src/SNGame/main.cpp \
           src/SNGame/TextureManager.cpp
RESOURCES += src/SNGame/images.qrc src/SNGame/qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += src/SNCore/Board.hpp \
           src/SNCore/Console.hpp \
           src/SNCore/EnumHelpers.hpp \
           src/SNCore/GameManager.hpp \
           src/SNCore/Player.hpp \
           src/SNCore/Resources.hpp \
           src/SNCore/Serial.hpp \
           src/SNCore/SNTypes.hpp \
           src/SNCore/Tile.hpp \
           src/SNCore/Actions/Action.hpp \
           src/SNCore/Actions/Actions.hpp \
           src/SNCore/Actions/AttackAction.hpp \
           src/SNCore/Actions/CaptureAction.hpp \
           src/SNCore/Actions/CreateTownAction.hpp \
           src/SNCore/Actions/CreateUnitAction.hpp \
           src/SNCore/Actions/MoveAction.hpp \
           src/SNCore/Actions/SettleAction.hpp \
           src/SNCore/Actions/SpawnUnitAction.hpp \
           src/SNCore/Bonuses/Bonus.hpp \
           src/SNCore/Bonuses/Bonuses.hpp \
           src/SNCore/Bonuses/DefenseBonuses.hpp \
           src/SNCore/Bonuses/EconomyBonuses.hpp \
           src/SNCore/Bonuses/WarfareBonuses.hpp \
           src/SNCore/Objects/Object.hpp \
           src/SNCore/Objects/Objects.hpp \
           src/SNCore/Objects/Settler.hpp \
           src/SNCore/Objects/Soldier.hpp \
           src/SNCore/Objects/Town.hpp \
           src/SNCore/Objects/Unit.hpp \
           src/SNCore/Objects/Prototypes/Prototype.hpp \
           src/SNCore/Objects/Prototypes/Prototypes.hpp \
           src/SNCore/Objects/Prototypes/SettlerPrototype.hpp \
           src/SNCore/Objects/Prototypes/SoldierPrototype.hpp \
           src/SNCore/Objects/Prototypes/SoldierStats.hpp \
           src/SNGame/BoardField.hpp \
           src/SNGame/GameBoard.hpp \
           src/SNGame/InfoBox.hpp \
           src/SNGame/SNHelpers.hpp \
           src/SNGame/TextureManager.hpp

OTHER_FILES += \
	 android/AndroidManifest.xml
