#include <iostream>
#define BIT(x) (1 << x) 
enum class type {
	etype1 = BIT(1),
	etype2 = BIT(1),
	etype3 = BIT(1),
	etype4 = BIT(1)


};

type operator ^= (const type& t1, const type& t2) {
	int ret = int(t2);
	ret ^= int(t2);
	return t1;
}

auto some(int a, int b) {
	return a + b;
}

int main() {
	type t = type::etype1;

	t ^= type::etype2;

}