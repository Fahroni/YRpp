/*
	A helper to randomly select from many weighted items.

	Add one or more items with a weight of 0 or higher you want to select from.
	The instance is able to select values if there is at least one item with a
	with a weight of 1 or higher.

	You can select multiple items using the same instance of this class, the
	probabilities of items to be selected will not change. Valid values for
	selection are 1..GetTotalWeight(). The select function will return true if and
	only if the instance is set up correctly and an item could be selected. The
	out parameter is written to if and only if an item could be selected.
*/

#ifndef DISCRETEDISTRIBUTION_H
#define DISCRETEDISTRIBUTION_H

#include <ArrayClasses.h>

template <typename T>
class DiscreteDistributionClass
{
public:
	template <typename T>
	struct DistributionObject {
		DistributionObject() : Value(T()), Weight(0U) {}
		DistributionObject(T value, unsigned int weight=1U) : Value(value), Weight(weight) {}

		bool operator ==(const DistributionObject<T> &rhs) { return false; }

		T Value;
		unsigned int Weight;
	};

	DiscreteDistributionClass() : Items(), TotalWeight(0U) {}

	void Add(DistributionObject<T> &item) {
		this->Items.AddItem(item);
		this->TotalWeight += item.Weight;
	}

	void Add(T value, unsigned int weight=1U) {
		DistributionObject<T> item(value, weight);
		this->Add(item);
	}

	void Clear() {
		this->TotalWeight = 0U;
		this->Items.Clear();
	}

	unsigned int GetTotalWeight() const {
		return this->TotalWeight;
	}

	int GetCount() const {
		return this->Items.Count;
	}

	bool IsValid() const {
		return this->TotalWeight > 0U && this->Items.Count > 0;
	}

	bool Select(unsigned int value, T* pOut) const {
		if(this->IsValid() && value && value <= this->TotalWeight) {
			unsigned int acc = 0U;
			for(auto i=this->Items.start(); i<this->Items.end(); ++i) {
				acc += i->Weight;

				if(acc >= value) {
					if(pOut) {
						*pOut = i->Value;
					}
					return true;
				}
			}
		}

		return false;
	}

	bool Select(Randomizer &random, T* pOut) const {
		if(!this->TotalWeight) {
			return false;
		}

		int value = random.RandomRanged(1, this->TotalWeight);
		return this->Select(value, pOut);
	}

private:
	DynamicVectorClass<DistributionObject<T>> Items;
	unsigned int TotalWeight;
};

#endif
