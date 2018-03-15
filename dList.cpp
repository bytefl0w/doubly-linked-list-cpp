// dList.cpp - Project 2
// Erik Mortimer - CS 101-001
// ===================
// Description
// ===================
// dList.cpp creates, deletes, adds, searches, finds, moves, sorts, and outputs
// doubly linked-lists using nodes that contain a integer and character (named key
// and type respectly)

//Struct definition of node
struct node {
    int key; 
    char type; 
    node *next = NULL, *prev = NULL;
};

//Class definition of dList (Doubly Linked-list) containing both data members and defined member functions
class dList{
    private:
		node *head;
		node *tail;
		int size;
    public:

        //Default constructor - creates an empty list
		dList(){ 
		    head = NULL;
		    tail = NULL;
		}

		//Constructor where the first two parameters are arrays and the third
		//is the length of the arrays. The constructor should initialize the list
		//with the contents of the arrays.
		dList(int key[], char type[], int len){
		    buildDLL(key, type, len);
		}

		//Creates a new node at the front of the list
		void addFront(int key, char type){
		    node *temp = new node;
		    temp->key = key;
		    temp->type = type;
		    temp->next = head;
		    if(head == NULL && tail == NULL)
		    	tail = temp;
		    else
		    	head->prev = temp;
		    head = temp;
		}

		//Creates a new node at the back of the list
		void addBack(int key, char type){
		    node *temp = new node;
		    temp->key = key;
		    temp->type = type;
		    temp->prev = tail;
		    if(head == NULL && tail == NULL)
		    	head = temp;
		    else 
			tail->next = temp;
		    tail = temp;
		}

		//Searches the list for the occurrence of the int parameter in the list and
		//returns a pointer to the node containing that key
		node *search(int key){
		    node *temp = head;
		    while(temp != NULL){
			if(temp->key == key)
			    return temp;
			else
			    temp = temp->next;
		    }
		    return NULL;
		}

		//Outputs all keys that have the type equation to the character parameter.
		//Should start at the front of the list and output the keys in list order
		void find(char type){
		    node *temp = head;
		    while(temp != NULL){
			if(temp->type == type)
			    cout << temp->key << " " << temp->type << "\t";
			temp = temp->next;
		    }
		    cout << endl;
		}

		//Move the node pointed to by the parameter to the front of the list
		void moveFront(node *index){
		    if(index->prev == NULL) 
			return;
		    else if(index->next == NULL){ 
		    	index->prev->next = NULL;
		    	tail = index->prev;
		    }
		    else{
				index->prev->next = index->next;
		    	index->next->prev = index->prev;
		    }
		    index->next = head;
		    index->prev = NULL;
		    head->prev = index;
		    head = index;
		}

		//Moves the node pointed to by the paramenter to the back of the list
		void moveBack(node *index){
		    if(index->next == NULL) 
				return;
		    else if(index->prev == NULL){
				index->next->prev = NULL;
				head = index->next;
		    }
		    else{ 
		    	index->prev->next = index->next;
		    	index->next->prev = index->prev;
		    }
		    index->prev = tail;
		    index->next = NULL;
		    tail->next = index;
		    tail = index;
		}
		
		//Outputs the first k elements of the list where 'k' is the int
		//parameter. 
		//direction = 'f' means the output starts at the front of the list
		//direction = 'b' means the output strats at the back of the list

		void out(int amount, char direction = 'f'){
		    node *temp;
		    if(direction == 'f'){
		    	temp = head;
		    	for(int i = 0; i < amount; i++){
		    	    cout << temp->key << " " << temp->type << "  ";
		    		if(temp->next != NULL)
		    	    	temp = temp->next;
				}
				cout << endl;
		    }
		    else{
		    	temp = tail;
				for(int i = 0; i < amount; i++){
		 		    cout << temp->key << " " << temp->type << "  ";
		 		    if(temp != NULL)
		    		    temp = temp->prev;
				}
				cout << endl;
		    }
		    
		}
		
		// Implementation of the MergeSort algorithm
		void sort(){
		    node *temp = head;
		    int keyArr[size];
		    char typeArr[size];
		    for(int i = 0; i < size; i++){
				typeArr[i] = temp->type;
				keyArr[i] = temp->key;
				temp = temp->next;
		    }
		    mergeSort(keyArr, 0, size - 1, typeArr);
		    clearDLL();
		    buildDLL(keyArr, typeArr, size); 
		}
		
		//Part of the MergeSort algorithm, recursively splits array
		void mergeSort(int kArr[], int left, int right, char tArr[]){
		    if(left < right){
				int mid = left + (right - left)/2;
				mergeSort(kArr, left, mid, tArr);
				mergeSort(kArr, mid + 1, right, tArr);
				merge(kArr, left, mid, right, tArr);
		    }
		}

		// merge part of the MergeSort algorithm	
		void merge(int keyArr[], int left, int mid, int right, char typeArr[]){
		    int i, j, k;
		    int pos1 = mid - left + 1;
		    int pos2 = right - mid;

		    int aTemp[pos1], bTemp[pos2];
		    char cTemp[pos1], dTemp[pos2];

		    for(i = 0; i < pos1; i++){
				aTemp[i] = keyArr[left + i];
				cTemp[i] = typeArr[left + i];	
		    }
		    for(j = 0; j < pos2; j++){
				bTemp[j] = keyArr[mid+j+1];
				dTemp[j] = typeArr[mid+j+1];
		    }
		    i = 0; j = 0; k = left;

		    while(i < pos1 && j < pos2){
				if(aTemp[i] <= bTemp[j]){
				    keyArr[k] = aTemp[i];
				    typeArr[k] = cTemp[i];
				    i++;
				}
				else{
				    keyArr[k] = bTemp[j];
				    typeArr[k] = dTemp[j];
				    j++;
				}
				k++;
		    }
		    while(i < pos1){
				keyArr[k] = aTemp[i];
				typeArr[k] = cTemp[i];
				i++;
				k++;
		    }
		    while(j < pos2){
				keyArr[k] = bTemp[j];
				typeArr[k] = dTemp[j];
				j++;
				k++;
		    }
		}
		
		// Clears the whole doubly linked-list
		void clearDLL(){
		    node *temp = tail;
		    while(temp != NULL){
		    	tail = temp->prev;
				if(tail == NULL) 
				    head = NULL;
				else
				    tail->next = NULL;
				delete temp;
				temp = tail;
		    }
		}

		// Builds the doubly linked-list
		void buildDLL(int key[], char type[], int len){
		    head = new node;
		    tail = new node;
		    head->key = key[0];
		    head->type = type[0];
		    size = len;
		    head->next = new node;
		    node *temp = head->next;
		    temp->prev = head; 
		    for(int i = 1; i < size-1; i++){
				temp->key = key[i];
				temp->type = type[i];
				temp->next = new node;
				temp->next->prev = temp;
				temp = temp->next;
		    }
		    tail = temp;
		    tail->key = key[size-1];
		    tail->type = type[size-1];
		    tail->next = NULL; 

		}
		//Destructor
		~dList(){
		   clearDLL(); 
		}
	       
    };


