double x;

int plus(int a, int b) {
	int c;
	c = a + b;
	return c;
}

int main() {
	int y[2];
	y[0] = 3.0;
	y[1] = 4.0;
	x = plus(y[0], y[1]);
	if(x) {
		double a;
		a = 2;
	}
	else {
		float b;
		b = x;
	}

	print x;
}
