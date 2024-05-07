#ifndef ai
#define ai

#include <vector>

#include "matrix.hpp"

namespace ai {
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
	};

	template <typename T, unsigned int size>
	class bias {
	public:
		matrix<T, 1, size> data = matrix<T, 1, size>();

		bias() { }
		bias(std::vector<T> in) {
			for (unsigned int i = 0; i < size; i++) {
				data[0][i] = in[i];
			}
		}
	};

	template <unsigned int size, unsigned int depth>
	class dense {
	public:
		matrix<double, size, depth> data = matrix<double, size, depth>();

		dense() {
			for (unsigned int x = 0; x < size; x++) {
				for (unsigned int y = 0; y < depth; y++) {
					data[x][y] = 1 - 2 * (double(rand()) / RAND_MAX);
				}
			}
		}
	};

	template <typename T, unsigned int insize, unsigned int depth, unsigned int outsize>
	void compute(input<T, outsize>* out, input<T, insize> in, dense<insize, depth> l, bias<T, insize> b) {
		input<T, insize> working = input<T, insize>();
		working.data = in.data;

		working.data = l.data * working.data;
		working.data = working.data + b.data;

		out.data = working.data;
	}
}

#endif
