#include <math.h>
using namespace std;

struct Accident {
    double latitude = 0;
    double longitude = 0;
    double distance = 0;
    int severity = 0;
    Accident(double lat, double longi, int sev) {
        severity = sev;
        latitude = lat;
        longitude = longi;
    }

    Accident() {
        severity = 0;
        longitude = 0;
        latitude = 0;
        distance = 0;
    }
};

class MaxHeap {
    int Findex = 0;
    double Latitude = 0;
    double Longitude = 0;
    int capacity = 5;
    Accident* heap = new Accident[5];
    void Heapify();
    int parent(int i) { return ((i - 1) / 2); }
    int right(int i) { return (2 * i + 2); }
    int left(int i) { return (2 * i + 1); }
public:
    int size = 0;
    void Insert(Accident x);
    MaxHeap(double lat, double longi);
    void MaxPop();
    Accident MaxTop();
};

MaxHeap::MaxHeap(double lat, double longi) {
    Latitude = lat;
    Longitude = longi;
}

void MaxHeap::Insert(Accident x) {
    x.distance = sqrt(pow(x.latitude - Latitude, 2.0) + pow(x.longitude - Longitude, 2.0));
    size++;
    if (size == capacity / 2) {
        Accident* newHeap = new Accident[capacity * 2];
        for (int i = 0; i < size; i++) {
            newHeap[i] = heap[i - Findex];
        }
        delete heap;
        heap = newHeap;
    }
    heap[size - 1] = x;
    Heapify();
}
void MaxHeap::Heapify() {
    int i = size - 1;
    while ((i > 0) && (heap[parent(i)].distance < heap[i].distance)) {
        Accident temp = heap[parent(i)];
        heap[parent(i)] = heap[i];
        heap[i] = temp;
        i = parent(i);
    }
}

void MaxHeap::MaxPop() {
    Accident temp = heap[0];
    if (heap[1].distance > heap[2].distance) {
        heap[0] = heap[1];
        for (int i = 1; i < size;) {
            if (right(i) < size && left(i) < size) {
                if (heap[left(i)].distance < heap[right(i)].distance) {
                    heap[i] = heap[right(i)];
                    i = right(i);
                }
                else {
                    heap[i] = heap[left(i)];
                    i = left(i);
                }
            }
            else if (right(i) < size) {
                heap[i] = heap[right(i)];
                i = size;
            }
            else if (left(i) < size) {
                heap[i] = heap[left(i)];
                i = size;
            }
            else {
                i = size;
            }
        }

    }
    else {
        heap[0] = heap[2];
        for (int i = 2; i < size;) {
            if (right(i) < size && left(i) < size) {
                if (heap[left(i)].distance < heap[right(i)].distance) {
                    heap[i] = heap[right(i)];
                    i = right(i);
                }
                else {
                    heap[i] = heap[left(i)];
                    i = left(i);
                }
            }
            else if (right(i) < size) {
                heap[i] = heap[right(i)];
                i = size;
            }
            else if (left(i) < size) {
                heap[i] = heap[left(i)];
                i = size;
            }
            else {
                i = size;
            }
        }
    }
}

Accident MaxHeap::MaxTop() {
    return heap[0];
}
