#include "unit.h"

Unit::Unit(GameObject & obj, int hp)
	:GameObject(obj){
	this->hp = hp;
	focus = nullptr;
	group = nullptr;
	type = "unit";
}

Unit::Unit(GameObject & obj, UnitGroup & group, int hp)
	:GameObject(obj){
	this->group = &group;
	this->hp = hp;
	type = "unit";
}

Unit::Unit()
	:GameObject(){
	hp = 100;
	focus = nullptr;
	group = nullptr;
	type = "unit";
}

Unit & Unit::operator=(Canvas & obj){
	Canvas::operator=(obj);
	return *this;
}

Unit & Unit::operator=(Subject & obj){
	Subject::operator=(obj);
	return *this;
}

Unit & Unit::operator=(GameObject & obj){
	GameObject::operator=(obj);
	return *this;
}

Unit & Unit::operator=(Unit & obj){
	GameObject::operator=(obj);
	hp = obj.hp;
	focus = obj.focus;
	group = obj.group;
	return *this;
}

void Unit::setGroup(UnitGroup & g) {
	group = &g;
}

void Unit::exitGroup() {
	group = nullptr;
}

UnitGroup * Unit::getGroup() {
	return group;
}

string Unit::getType() {
	return type;
}

UnitGroup::UnitGroup(){
	// Nothing :)
}

UnitGroup::UnitGroup(UnitContainer & container){
	push(container);
}

void UnitGroup::push(Unit& unit, bool linkGroup) {
	if (linkGroup) unit.setGroup(*this);
	units.push_back(&unit);
}

void UnitGroup::push(UnitContainer & container){
	auto iter = container.begin();
	while (iter != container.end()) {
		push(*iter++);
	}
}

bool UnitGroup::erase(Unit& unit){
	auto iter = units.begin();
	while (iter != units.end()) {
		if (&unit == *iter) {
			units.erase(iter);
			return true;
		}
		iter++;
	}
	return false;
}

void UnitGroup::clear(){
	units.clear();
}

list<Unit*>::iterator UnitGroup::begin(){
	return units.begin();
}

list<Unit*>::iterator UnitGroup::end(){
	return units.end();
}

void UnitGroup::iterateAll(){
	auto iter = units.begin();
	while (iter != units.end()) {
		(**iter++).iteration();
	}
}

void UnitGroup::blitAll(Canvas & canv){
	auto iter = units.begin();
	while (iter != units.end()) {
		Unit &unit = (**iter);
		canv.blit(unit.subject(), unit.getX(), unit.getY());
		iter++;
	}
}

void UnitGroup::foreach(void_unit_func func) {
	auto iter = begin();
	while (iter != end()) {
		func(**iter);
		iter++;
	}
}

list<Unit*> UnitGroup::find(bool_unit_func func) {
	list<Unit*> find_units;
	auto iter = begin();
	while (iter != end()) {
		if (func(**iter)) find_units.push_back(*iter);
		iter++;
	}
	return find_units;
}

bool UnitGroup::iterate(){
	iterateAll();
	return true;
}

void UnitContainer::push(Unit& unit){
	units.push_back(unit);
}

bool UnitContainer::erase(list<Unit>::iterator& iter){
	if (iter == units.end()) return false;
	units.erase(iter);
	return true;

}

void UnitContainer::clear(){
	units.clear();
}

list<Unit>::iterator UnitContainer::begin(){
	return units.begin();
}

list<Unit>::iterator UnitContainer::end()
{
	return units.end();
}
