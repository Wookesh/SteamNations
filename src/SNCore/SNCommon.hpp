#ifndef SNCOMMON_HPP
#define SNCOMMON_HPP

namespace SN {
	
	enum class ActionType {
		Move,
		Attack,
		Capture,
		Settle
	};
	
	/**
	 * TODO
	 * klasa, która będzie reprezentować akcję obiektu na innym obiekcie.
	 * GameManager powinna umieć podać dla objektu listę akcji, które objekt może wykonać
	 * na objekcie znajdującym się na docelowym tile'u. gdzie docelowe tile'e są w zasięgu ruchu objektu.
	 * 
	 * Chcemy aby z Action, dało się wyciągnąć tile ostatniego pola,
	 * albo, żeby dostać od gry listę par Tile - Akcja
	 * 
	 * Z Poziomu grafiki nie interesuje nas żaden objekt
	 * bo jeśli to jest miasto, to i tak poleci sygnał, że zmienił się owner,
	 * podobnie, jesli jednostka, to że otrzymała lub zadała obrażenia.
	 * Więc i tak to wyanimujemy w jakis sposób.
	 * 
	 * bool preform() powinno wykonać akcję, jeśli jest ona prawidłowa.
	 * Jeśli została wykonana zwrócić true, wpp false
	 * 
	 * i najlepiej w oddzielny pliku poza namespace'em.
	 */
	class Action {
	public:
		const ActionType action;
		//const Object *first;
		//const Object *second;
		//const Tile *finalTile;
		
		bool perform() {
			//TODO
			return false;
		}
	};
}

#endif
