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
	N *a;
	N *b;

	if (argc < 2) {
		exit(1);
	}
	a = new N(5);
	b = new N(6);
	a->setAnnotation(argv[1]);
	return ( (b->*(b->func))(*a) );
}
