//
// Created by alhric on 30-Oct-15.
//

#include "AbstractItem.h"



string AbstractItem::getName() {
    return name;
}

string AbstractItem::use() {
    return "abstract item";
}


AbstractItem::~AbstractItem() {

}

itemType AbstractItem::getType() {
    return type;
}

AbstractItem::AbstractItem() {

}

AbstractItem::AbstractItem(string name) {

}
