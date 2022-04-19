#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <ctime>
#include <stack>
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
    void Heapify(int i);
    int parent(int i) { return ((i - 1) / 2); }
    int right(int i) { return (2 * i + 2); }
    int left(int i) { return (2 * i + 1); }
public:
    int size = 0;
    void Insert(Accident x);
    MaxHeap(double lat, double longi);
    void MaxPop();
    Accident MaxTop();
    void Print();
};

MaxHeap::MaxHeap(double lat, double longi) {
    Latitude = lat;
    Longitude = longi;
}

void MaxHeap::Insert(Accident x) {
    x.distance = sqrt(pow(x.latitude - Latitude, 2.0) + pow(x.longitude - Longitude, 2.0));
    size++;
    if (size >= capacity / 2) {
        capacity = capacity * 2;
        Accident* newHeap = new Accident[capacity];
        for (int i = 0; i < size; i++) {
            newHeap[i] = heap[i - Findex];
        }
        delete heap;
        heap = newHeap;
    }

    int i = size - 1;
    heap[i] = x;
    while (i != 0 && heap[parent(i)].distance < heap[i].distance){
	Accident temp = heap[i];
	heap[i] = heap[parent(i)];
	heap[parent(i)] = temp;
	i = parent(i);
    }
}
void MaxHeap::Heapify(int i) {
    int l = left(i);
    int r = right(i);
    int smallest = i;
    if (l < size && heap[l].distance > heap[i].distance)
	smallest = l;
    if (r < size && heap[r].distance > heap[smallest].distance)
	smallest = r;
    if (smallest != i)
    {
	Accident temp = heap[i];
	heap[i] = heap[smallest];
	heap[smallest] = temp;
	Heapify(smallest);
    }	    
}

void MaxHeap::MaxPop() {
    //Accident temp = heap[0]; this was for when returning the value
    if(size <= 0){
	return;
    }
    if(size == 1){
	size--;
	heap[0] = heap[1];
	return;
    }

    Accident root = heap[0];
    heap[0] = heap[size - 1];
    size--;
    Heapify(0);
}
Accident MaxHeap::MaxTop() {
    return heap[0];
}
void MaxHeap::Print(){
    cout << "[ ";
    for(int i = 0; i < size; i++){
	Accident curr = heap[i];
	cout << curr.latitude << ":" << curr.distance << " ";
    }
    cout << "]" << endl;
}

int main(int argc, char* argv[])
{
    fstream file;
    file.open("dataOut.csv", fstream::in);
    string line = "";
    double lati = stod(argv[1]);
    double loni = stod(argv[2]);
    int count = stoi(argv[3]);
    MaxHeap mh(lati, loni);
    time_t itr = time(NULL);
    if (file.is_open()) {
        while (getline(file, line)) {
            double latf = stod(line.substr(0, line.find(',')));
            line = line.substr(line.find(',') + 1);
            double lonf = stod(line.substr(0, line.find(',')));
            line = line.substr(line.find(',') + 1);
            int sev = stoi(line.substr(0, line.find(',')));
            double dist = sqrt(pow(latf - lati, 2) + pow(lonf - loni, 2));
            if (mh.size <= count) {
                mh.Insert(Accident(latf, lonf, sev));
            }
            else if (dist < mh.MaxTop().distance) {
		mh.MaxPop();
                mh.Insert(Accident(latf, lonf, sev));
            }
        }
        file.close();
    }
    time_t ftr = time(NULL);
    //cout << "Time taken to load file: " << ftr - itr << " seconds." << endl;
    stack<Accident> sa;
    for (int i = 0; i < count; i++) {
        sa.push(mh.MaxTop());
        mh.MaxPop();
    }
    for (int i = 0; i < count; i++) {
        Accident a = sa.top();
        cout << a.latitude << "," << a.longitude << "," << a.severity << endl;
        sa.pop();
    }
}
