#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <fstream>
#include "heap.h"

using namespace std;

static int icount=0;

void Heap::PrintHeap(){//print in vector order
	for(int i=0; i<=last;i++){
		printf("%d ",data[i]);	
	}
	printf("\n");
	
}

void Heap::PrintWHeap(){//print whole vector
	for(int i=0; i<=llast;i++){
		printf("%d ",data[i]);	
	}
	printf("\n");
	
}

int Heap::ReturnValue(int index){
	if(index<=last){
		return data[index];
	}else{
		return -1;
	}
}

int Heap::Return(){
	if(data[0]!=-1){
		return data[0];
	}
	return -1;
}

int Heap::InsertHeap( int newthing){
	data.push_back(newthing);
	last+=1;
	llast=llast+1;
	if (last==0) return -1;//only one item in Heap
	int child_index=last;
	int par_index=0;
	bool swapping=true;
	while (swapping){//fix the heap
		swapping=false;
		if(child_index%2==0) par_index=child_index/2-1;//right
		else par_index=child_index/2;//left
		if(par_index>=0){
			icount++; //COMPARISON COUNT
			if(data[child_index]>data[par_index]) {
				swap(data[child_index],data[par_index]);
				swapping=true;
				child_index=par_index;
			}
		}
	}
	return icount;
 }


int Heap::DeleteRoot(){
	
	if(last<0) return -1;
	//unsigned int deletedvalue=data[0];//the root
	//cout<<"Deleting = "<<deletedvalue<<endl;
	data[0]=data[last];
	data[last]=0;//deleting...
	last=last-1;
	int parindex=0;//root at the moment
	int leftindex=parindex*2+1;//left child
	int rightindex=parindex*2+2;//right child
	//Fixing the Heap
	
	int count=0;

	//if(rightindex >= last){return -1;}
	if(leftindex <=last){
		if(rightindex <= last){
			count+=2;
		}else{
			count++;
		}
	}
	
	while (data[parindex]<data[leftindex]||data[parindex]<data[rightindex]){
		//PROBLEM: what happens if last=1 or last=0? One or both indices for the children may be invalid
		
		if (data[rightindex]<data[leftindex]){//follow left
			swap(data[leftindex],data[parindex]);
			parindex=leftindex;
		}
		else{//else follow right
			swap(data[rightindex],data[parindex]);	
			parindex=rightindex;
		}
		
		leftindex=parindex*2+1;
		rightindex=parindex*2+2;
		
		//Andre Count
		if(leftindex > last) break;   //0 children, reached the bottom of the tree
		else if(leftindex <=last){
			if(rightindex<=last){
				count+=2;// 2 children, count 2 comparisons
				}
				else{
				count++;//1 child, count 1 comparison
			}	
		}			
		
		if(leftindex>last) { break;}
		else {
			if(rightindex>last){
				if (data[parindex]<data[leftindex]) {
					//count++;
					swap(data[parindex],data[leftindex]);
				}
				break;	
			}
		}
	}
	return count;
}

/* this is a possible prototype for the heapsort function */
/* the char* filename is just for printing the name, the file is opened and dealt with in the main() */
void heapsort(vector<int> &sortingvector,int number_of_elements, char* filename){
	Heap myHeap; //declare a Heap instance here */
	cout<<"Heap before sorting: "<<filename<<endl;
	/* Using the sortingvector, INSERT elements into the Heap */
	int inscomp=0;
	icount=0;
	for(int i=0; i<sortingvector.size(); i++){
		inscomp=myHeap.InsertHeap(sortingvector[i]);
	}
	// After building the heap from the file, PRINT the current state of the heap before sorting */
	myHeap.PrintHeap();
	/* STORE how many comparisons were made until this point */	
	/* PRINT the number of comparisons for the Insert and Deletion tasks */
	cout<<"InsertHeap: "<<inscomp<<" comparisons"<<endl;
	
	/* DELETE elements from the Heap, copying it back to the vector in a way that it is sorted */
	/* STORE how many comparisons were made for the deletion process */
	int delcomp=0;
	int y = sortingvector.size();
	for(int i=y-1; i>=0; i--){
		final_vector.push_back(myHeap.Return());
		delcomp+=myHeap.DeleteRoot();
	}
	
	/* Print the state of the vector after sorting */
	cout << "DeleteRoot: " << delcomp << " comparisons" << endl;
	cout << "Vector after sorting:" <<endl;
	int x = final_vector.size();
	//myHeap.PrintWHeap();	
	for(int i=x-1; i>=0; i--){
		printf("%d ", final_vector[i]);
		final_vector.pop_back();
	}
	
	cout<<endl;
	//cout <<"final_vector.size()="<<final_vector.size()<<endl;
}