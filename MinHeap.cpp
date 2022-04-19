#include <math.h>
struct accident{
    double latitude = 0;
    double longitude = 0;
    double distance = 0;
    int severity = 0;
    accident(double lat, double longi, int sev){
    severity = sev;
    latitude = lat;
    longitude = longi;
}
    
accident(){
    severity = 0; 
    longitude = 0;
    latitude = 0;
    distance = 0;
}
};

class MinHeap{
    int Findex = 0;
    double Latitude = 0;
    double Longitude = 0;    
    int capacity = 5;
    int size = 0;
    accident *heap = new accident[5];
    void Heapify();
    int parent(int i){return ((i - 1) / 2);}
    int right(int i){return (2 * i + 2);}
    int left(int i){return (2 * i + 1);}
public:
    void Insert(accident x);
    void Print();
    MinHeap(double lat, double longi);
    accident MinPop();
};

MinHeap::MinHeap(double lat, double longi){
    Latitude = lat;
    Longitude = longi;
}

void MinHeap::Insert(accident x){
    x.distance= sqrt(pow(x.latitude - Latitude, 2.0) +pow(x.longitude - Longitude, 2.0));
    size++;
    if(size == capacity / 2){
       accident *newHeap = new accident[capacity * 2]; 
       for(int i = 0; i < size; i++){
           newHeap[i] = heap[i - Findex];
       }
       delete heap; 
       heap = newHeap;
    }
    heap[size - 1] = x;
    Heapify();
}
void MinHeap::Heapify(){
    int i = size - 1;
    while((i > 0) && (heap[parent(i)].distance>heap[i].distance)){
        accident temp = heap[parent(i)];
        heap[parent(i)] = heap[i];
        heap[i] = temp; 
        i = parent(i);
    }
}

accident MinHeap::MinPop(){
    accident temp = heap[0]; 
    if(heap[1].distance<heap[2].distance){
        heap[0] = heap[1];
        for(int i=1; i <size;){
            if(right(i)<size && left(i)<size){
            if(heap[left(i)].distance>heap[right(i)].distance){
                heap[i]=heap[right(i)];
                i=right(i);
            }else{
                heap[i]=heap[left(i)];
                 i=left(i);
            }
            }else if(right(i)<size){
                heap[i]=heap[right(i)];
                 i=size; 
            }else if (left(i)<size){
                heap[i]=heap[left(i)];
                 i=size; 
            }else {
                i=size; 
            }
        }

    }else{
        heap[0] = heap[2];
        for(int i=2;i<size;){
            if(right(i)<size && left(i)<size){
                 if(heap[left(i)].distance>heap[right(i)].distance){
                heap[i]=heap[right(i)];
                i=right(i);
            }   else{
                heap[i]=heap[left(i)];
                 i=left(i);
            }
            }else if(right(i)<size){
                heap[i]=heap[right(i)];
                 i=size; 
            }else if (left(i)<size){
                heap[i]=heap[left(i)];
                 i=size; 
            }else {
                i=size; 
            }
        }
    }
    return temp;
}
