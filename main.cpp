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
	int epochs = 100;
	double lr = 1;

	dense<2, 100> denselayer = dense<2,100>();
	bias<2> biaslayer = bias<2>();
	dense<2, 100> denselayer2 = dense<2,100>();
	bias<2> biaslayer2 = bias<2>();

	double lastmse = 2147483647;

	for (int epoch = 0; epoch < epochs; epoch++) {
		auto newdense = denselayer;
		auto newbias = biaslayer;
		newdense.tweak(lr);
		newbias.tweak(lr);
		auto newdense2 = denselayer2;
		auto newbias2 = biaslayer2;
		newdense2.tweak(lr);
		newbias2.tweak(lr);

		double mse = 0;

		for (int i = 0; i < datasize; i++) {
			input<double, 2> out = input<double, 2>();
			compute<double, 2, 100, 2>(&out, indata[i], newdense, newbias);
			compute<double, 2, 100, 2>(&out, out, newdense2, newbias2);
			if (out.data[0][0] > 1) {
				out.data[0][0] = 1;
			}
			else {
				out.data[0][0] = 0;
			}
			double mselocal = outdata[i] - out.data[0][0];
			mselocal *= mselocal;
			mse += mselocal;
		}

		if (mse < lastmse) {
			denselayer = newdense;
			biaslayer = newbias;
			denselayer2 = newdense2;
			biaslayer2 = newbias2;
			lastmse = mse;
		}

		if (epoch % (epochs / 10) == 0) {
			std::cout << "Training... MSE: " << lastmse << std::endl;
		}
	}

	for (int i = 0; i < datasize; i++) {
		input<double, 2> out = input<double, 2>();
		compute<double, 2, 100, 2>(&out, indata[i], denselayer, biaslayer);
		compute<double, 2, 100, 2>(&out, out, denselayer2, biaslayer2);
		if (out.data[0][0] > 1) {
			out.data[0][0] = 1;
		}
		else {
			out.data[0][0] = 0;
		}
		std::cout << outdata[i] << " ";
		std::cout << out.data[0][0] << std::endl;
	}

	return 0;
}
