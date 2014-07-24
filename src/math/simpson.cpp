inline double f(double x)
{ ... }

double simpson(double a, double b, int N)
{
	// N must be EVEN!
	double h = (b-a)/N;
	double ans = f(a) + f(b);
	for (int j=1; j<N/2; j++)
		ans += 2*f(a+2*j*h);
	for (int j=1; j<=N/2; j++)
		ans += 4*f(a+(2*j-1)*h);
	return ans * h / 3;
}
