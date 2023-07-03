struct Element{
    string data;
    char c;
    int num;
    Element*next;
};

struct Queue{
    int n;
    Element *myrear,*myfront;
};
Queue *createEmptyQueue(){
    Queue *q;
    q=new Queue;
    q->myrear=NULL;
    q->myfront=NULL;
    q->n=0;
    return q;
};


struct ElementL{
    Queue* datal;
    ElementL*next;
};


struct QueueL{
    int nl;
    ElementL *myrearl,*myfrontl;
};


QueueL *createEmptyQueueL(){
    QueueL *ql;
    ql=new QueueL;
    ql->myrearl=NULL;
    ql->myfrontl=NULL;
    ql->nl=0;

    return ql;
};

struct ElementLL{
    QueueL* datall;
    ElementLL*next;
};


struct QueueLL{
    int nll;
    ElementLL *myrearll,*myfrontll;
};

QueueLL*createEmptyQueueLL(){
    QueueLL *ql;
    ql=new QueueLL;
    ql->myrearll=NULL;
    ql->myfrontll=NULL;
    ql->nll=0;

    return ql;
}


void enqueueS(Queue *q, string newData){///to insert string
    Element *e;
    e=new Element;
    e->data=newData;
    e->next=NULL;
    if(q->n==0){
        q->myrear=e;
        q->myfront=e;
        q->n=q->n+1;
    }else{
        q->myrear->next=e;
        q->myrear=e;
        q->n=q->n+1;
    }
}


void enqueueC(Queue *q, char newData){///to insert char
    Element *e;
    e=new Element;
    e->c=newData;
    e->next=NULL;
    if(q->n==0){
        q->myrear=e;
        q->myfront=e;
        q->n=q->n+1;
    }else{
        q->myrear->next=e;
        q->myrear=e;
        q->n=q->n+1;
    }
}
void enqueueI(Queue *q, int newData){///to insert integer
    Element *e;
    e=new Element;
    e->num=newData;
    e->next=NULL;
    if(q->n==0){
        q->myrear=e;
        q->myfront=e;
        q->n=q->n+1;
    }else{
        q->myrear->next=e;
        q->myrear=e;
        q->n=q->n+1;
    }
}

void enqueueL(QueueL *q,Queue* newData){///insert queue to QueueL
    ElementL *e;
    e=new ElementL;
    e->datal=newData;
    e->next=NULL;
    if(q->nl==0){
        q->myrearl=e;
        q->myfrontl=e;
        q->nl=q->nl+1;
    }else{
        q->myrearl->next=e;
        q->myrearl=e;
        q->nl=q->nl+1;
    }
}

void enqueueLL(QueueLL *q,QueueL* newData){///insert queue to QueueL
    ElementLL *e;
    e=new ElementLL;
    e->datall=newData;
    e->next=NULL;
    if(q->nll==0){
        q->myrearll=e;
        q->myfrontll=e;
        q->nll=q->nll+1;
    }else{
        q->myrearll->next=e;
        q->myrearll=e;
        q->nll=q->nll+1;
    }
}



void InsertionSort(int a[], int size1, Queue *l){//input list then turn into array to sort, and return the sort array
    Element *e;
    e=l->myfront;
    int i=0;
    while(e!=NULL){
        a[i]=e->num;
        e=e->next;
        i++;
    }
	for(int k=1; k<size1; k=k+1){
		int key = a[k];
		int j = k - 1;

		while(key < a[j] && j>=0){
			a[j+1] = a[j];
			j=j-1;
		}
		a[j+1] = key;
}
}
void SortQueue(Queue*l, Queue*l2){/// l is unsorted queue, after sort it goes to l2

    int arr[l->n];
    InsertionSort(arr, l->n, l);
	for(int i=0;i<l->n;i++){
        enqueueI(l2,arr[i]);
	}
}





