int main (){
	float cos, x, n, term, eps, alt;
	// compute the cosine of x to within tolerance eps
	// use an alternating series
	x = 3.14159;
	eps = 0.1;
	n = 1;
	cos = 1;
	term = 1;
	alt = -1;
	while(term > eps){
		term = term * x * x / n / (n+1);
		cos = cos + alt * term;
		alt = -alt;
		n = n + 2;
	}
}