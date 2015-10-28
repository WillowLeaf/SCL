
const int maxn = 1000050;
int prime[maxn],nPrime;
bool isPrime[maxn];
void getPrimes(int N)
{
	memset(isPrime,true,sizeof(isPrime));
	nPrime = 0;
	for(int i = 2; i <= N; ++i) {
		if(isPrime[i]) prime[nPrime++] = i;
		for(int j = 0; j < nPrime && i * prime[j] <= N; ++j) {
			isPrime[i*prime[j]] = false;
			if(i%prime[j] == 0) break;
		}
	}
}
