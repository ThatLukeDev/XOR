#include <iostream>

#include "ai.hpp"

int main() {
	input<double, 2> indata[] = {
		input<double, 2>(std::vector<double>{0, 0}),
		input<double, 2>(std::vector<double>{0, 1}),
		input<double, 2>(std::vector<double>{1, 0}),
		input<double, 2>(std::vector<double>{1, 1})
	};
	double outdata[] = {
		0,
		1,
		1,
		0
	};
	int datasize = 4;
	int epochs = 500;
	double lr = 0.01;

	dense<2, 10> denselayer = dense<2,10>();
	bias<2> biaslayer = bias<2>();

	double lastmse = 2147483647;

	for (int epoch = 0; epoch < epochs; epoch++) {
		auto newdense = denselayer;
		auto newbias = biaslayer;
		newdense.tweak(lr);
		newbias.tweak(lr);

		double mse = 0;

		for (int i = 0; i < datasize; i++) {
			input<double, 2> out = input<double, 2>();
			compute<double, 2, 10, 2>(&out, indata[i], newdense, newbias);
			double mselocal = outdata[i] - out.data[0][0];
			mselocal *= mselocal;
			mse += mselocal;
		}

		if (mse < lastmse) {
			denselayer = newdense;
			biaslayer = newbias;
			lastmse = mse;
		}

		if (epoch % (epochs / 10) == 0) {
			std::cout << "Training... MSE: " << lastmse << std::endl;
		}
	}

	return 0;
}
