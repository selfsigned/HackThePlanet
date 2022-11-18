#include <cstdlib>
#include <cstring>
#include <cstdio>

class N;
typedef int (N::*t_func)(N &param);

class N {
	public:
	char annotation[100];
	int x;
	t_func func = N::operator+;

	public:
	N(int param) {
		this->x = param;
	}
	void*	setAnnotation(const char *param) {
		return (memcpy(this->annotation, param, strlen(param)));
	}
	int		operator+(N& param) {
		return (this->x + param.x);
	}
	int		operator-(N& param) {
		return (this->x - param.x);
	}
};

int main(int argc, const char **argv, const char **envp)
{
	N *n_1;
	N *n_2;

	if (argc < 2) {
		exit(1);
	}
	n_1 = new N(5);
	n_2 = new N(6);
	n_1->setAnnotation(argv[1]);
	return ((n_2->func)(n_1)); // wont compile yet
}
