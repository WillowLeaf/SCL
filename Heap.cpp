const int MAX_HEAP_SIZE = 1024;
int heap[MAX_HEAP_SIZE],result[MAX_HEAP_SIZE];
int heapSize;

void heapify(int i)
{
	int l = i << 1, r = i << 1 | 1;
	int m = i;
	if(l <= heapSize && heap[m] < heap[l]) 
		m = l;
	if(r <= heapSize && heap[m] < heap[r])
		m = r;
	if(m != i) {
		swap(heap[m],heap[i]);
		heapify(m);
	}
}

void DecreaseKey(int i,int key)
{
	heap[i] = key;
	while(i != 1 && heap[i >> 1] > key) {
		swap(heap[i],heap[i >> 1]);
		i = i >> 1;
	}
}

void IncreaseKey(int i, int key)
{
	if(heap[i] != key) {
		heap[i] = key;
		heapify(i)
	}
}

void UpdateKey(int i, int key)
{
	if(heap[i] <= key) {
		IncreaseKey(i, key)
	} else {
		DecreaseKey(i, key)
	}
}

void HeapPush(int key)
{
	heap[++heapSize] = INF;
	DecreaseKey(heapSize,key);
}

int HeapPop() {
	int tmp = heap[1];
	heap[1] = heap[heapSize--];
	heapify(1);
	return tmp;
}

void MakeHeap()
{
	for(int i = heapSize >> 1; i >= 1; --i)
		heapify(i);
}

void HeapSort()
{
	for(int i = 1; i <= heapSize; ++i) {
		result[i] = heap[1];
		swap(heap[1],heap[heapSize--]);
		heapify(1);
	}
}
