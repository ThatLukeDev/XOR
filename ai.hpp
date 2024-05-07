#ifndef ai
#define ai

#include <vector>

#include "matrix.hpp"

template <typename T, unsigned int size>
class input {
public:
	matrix<T, 1, size> data = matrix<T, 1, size>();

	input() { }
	input(std::vector<T> in) {
		for (unsigned int i = 0; i < size; i++) {
			data[0][i] = in[i];
		}
	}

	void norm() {
		for (unsigned int i = 0; i < size; i++) {
			if (data[0][i] < 0) {
				data[0][i] = 0;
			}
		}
	}
};

template <unsigned int size>
class bias {
public:
	matrix<double, 1, size> data = matrix<double, 1, size>();

	bias() {
		for (unsigned int y = 0; y < size; y++) {
			data[0][y] = 1 - 2 * (double(rand()) / RAND_MAX);
		}
	}

	void tweak(double lr) {
		for (unsigned int y = 0; y < size; y++) {
			data[0][y] += lr * (1 - 2 * (double(rand()) / RAND_MAX));
		}
	}
};

template <unsigned int size, unsigned int depth>
class dense {
public:
	matrix<double, depth, size> data = matrix<double, depth, size>();

	dense() {
		for (unsigned int x = 0; x < depth; x++) {
			for (unsigned int y = 0; y < size; y++) {
				data[x][y] = 1 - 2 * (double(rand()) / RAND_MAX);
			}
		}
	}

	void tweak(double lr) {
		for (unsigned int x = 0; x < depth; x++) {
			for (unsigned int y = 0; y < size; y++) {
				data[x][y] += lr * (1 - 2 * (double(rand()) / RAND_MAX));
			}
		}
	}
};

template <typename T, unsigned int insize, unsigned int depth, unsigned int outsize>
void compute(input<T, outsize>* out, input<T, insize> in, dense<insize, depth> l, bias<insize> b) {
	input<T, insize> working = input<T, insize>();
	working.data = in.data;

	working.data = l.data * working.data;
	working.norm();
	working.data = working.data + b.data;

	out->data = working.data;
}

#endif
