#include <memory>
#include <iostream>
#include <vector>
using namespace std;
 
class foo {
public:
	~foo() {
		cout << "destruct" << endl;
	}
};

void some(shared_ptr<foo> v) {
	cout << "Some" << endl;
}

int main() {

	shared_ptr<foo> ptr = make_shared<foo>();
	vector<shared_ptr<foo>> v;

	some(nullptr);


	cout << "hi " << endl;


}