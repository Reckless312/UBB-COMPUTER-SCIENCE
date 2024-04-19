#include "MultiMapIterator.h"
#include "MultiMap.h"


MultiMapIterator::MultiMapIterator(const MultiMap& c): col(c) {
	this->currentPosition = 0;
    if (this->col.size() > 0)
    {
        this->CurrentKeyNode = this->col.head;
        this->CurrentValueNode = this->CurrentKeyNode->Head;
    }
    else
    {
        this->CurrentKeyNode = nullptr;
        this->CurrentValueNode = nullptr;
    }
}
// BC = WC = OC = T(1)

TElem MultiMapIterator::getCurrent() const{
    if (!valid()) {
        throw std::exception();
    }
    return TElem(this->CurrentKeyNode->key, this->CurrentValueNode->value);
}
// BC = WC = OC = T(1)
bool MultiMapIterator::valid() const {
	return this->currentPosition < this->col.size();
}
// BC = WC = OC = T(1)

void MultiMapIterator::next() {
    if (!valid())
    {
        throw exception();
    }
    this->currentPosition++;
    if (this->CurrentKeyNode != nullptr && this->CurrentValueNode != nullptr)
    {
        if (this->CurrentValueNode->Next != nullptr)
        {
            this->CurrentValueNode = this->CurrentValueNode->Next;
            return;
        }
        else
        {
            this->CurrentKeyNode = this->CurrentKeyNode->Next;
            if (this->CurrentKeyNode != nullptr)
            {
                this->CurrentValueNode = this->CurrentKeyNode->Head;
                return;
            }
            else
            {
                this->CurrentValueNode = nullptr;
            }
        }
    }
}
// BC = WC = OC = T(1)

void MultiMapIterator::first() {
    this->currentPosition = 0;
    if (this->col.size() > 0)
    {
        this->CurrentKeyNode = this->col.head;
        this->CurrentValueNode = this->CurrentKeyNode->Head;
    }
    else
    {
        this->CurrentKeyNode = nullptr;
        this->CurrentValueNode = nullptr;
    }
}
// BC = WC = OC = T(1)

