

int cmpDataInQ(Queue*q, Queue*q1){///check if it has atleast one same data/number, work for number only
    int n=0;

    Element*e;
    Element*e1;
    e=q->myfront;
    while(e!=NULL){
        e1=q1->myfront;
        while(e1!=NULL){
            if(e1->num==e->num){
                n=1;
            }
            e1=e1->next;
        }
        e=e->next;
    }
    return n;  ///n=1 when at least it has one same number
}



int indexSym(Queue*q3,char str){///turn a symbol into index
    Element*e;
    e=q3->myfront;
    int tmp=0;//index of symbol
    while(e!=NULL){
        if(str==e->c){
            break;
        }
        tmp=tmp+1;
        e=e->next;
    }
    return tmp;
}
int indexState(string str){///convert string of state, q1,q2,q99... to integer, q1->1 , q5->5, q99->99
    int i;
    str=str.substr(1,str.length());
    istringstream(str) >>i;
    return i;
}
string r_indexState(int idxst){///convert index of state to form it as state back, 1 to q1, 99 to q99
    string s=to_string(idxst);
    s="q"+s;
    return s;
}



int  existElementInQ(Queue*q,int n){///check element exist in q or not, work for integer n
    Element*e;
    e=q->myfront;
    int h=0;
    while(e!=NULL){
        if(e->num==n){
            h=1;
        }
        e=e->next;
    }
    return h;///h=1, if its already exsit
}


int existElementInQL(QueueL*Q, int n){///check if a number exists in QL or not
    int h=-1;
    ElementL*E;

    E=Q->myfrontl;
    int j=0;
    while(E!=NULL){
        if(existElementInQ(E->datal, n)==1){///mean it exist in QL
            h=j;
        }
        j++;
        E=E->next;
    }

    return h;///h=-1 n is not in QueueL*Q
            ///else return the index of Queue in QueueL*Q
}

void Concatenate2Q(Queue*q1, Queue*q2, Queue*qp){///put data in l2 to l1 without duplicate into qp
    Queue*q;
    q=createEmptyQueue();
    Element*e1;
    Element*e2;
    e1=q1->myfront;
    while(e1!=NULL){
        enqueueI(q, e1->num);
        e1=e1->next;
    }

    e2=q2->myfront;
    while(e2!=NULL){
        if(existElementInQ(q, e2->num)==0){
            enqueueI(q, e2->num);
        }
        e2=e2->next;
    }

    SortQueue(q, qp);
}


int cmp_Q1_Q2(Queue*q1, Queue*q2){
    int h=1;
    if(q1->n==q2->n){
        Element*e1;
        e1=q1->myfront;
        Element*e2;
        e2=q2->myfront;
        for(int i=0;i<q1->n;i++){
            if(e1->num!=e2->num){
                    h=0;
                break;
            }
        }
    }else h=0;

    return h;
    /// h=1 both are same, h=0 not the same

}



int cmpQ2L(QueueL*N,Queue*l2){//check if l2 exist in N or not
    int n=-1;
    ElementL*t;
    t=N->myfrontl;
    int k=0;
    while(t!=NULL){
        if(t->datal->n!=l2->n){
        }else{
            int p=0;
            Element*e;
            Element*E;
            e=t->datal->myfront;
            E=l2->myfront;
            for(int i=0;i<l2->n;i++){
                if(e->num==E->num){
                    p=1;
                }else{
                    p=0;
                    break;
                }
                e=e->next;
                E=E->next;
            }
            if(p==1){
                n=k;
            }
        }
            t=t->next;
            k++;
    }
    return n;///if n=-1, then l2 are not in N, if l2 in N so will returns what its index
}




Queue*IndexToState_Q(Queue*q){///turn q data from integer into string form as 0=q0,1=q1....n=qn
    Queue*qp;
    qp=createEmptyQueue();
    Element*e;
    e=q->myfront;
    while(e!=NULL){
        enqueueS(qp, r_indexState(e->num));
        e=e->next;
    }

    return qp;
}
Queue*StateToIndex_Q(Queue*q){///turn Queue data from string, q1,q2,q3..., into integer form as q0=0, q1=1, q99=99
    Queue*qp;
    qp=createEmptyQueue();
    Element*e;
    e=q->myfront;
    while(e!=NULL){
        enqueueI(qp, indexState(e->data));
        e=e->next;
    }

    return qp;
}

QueueL* StateToIndex_QL(QueueL*q0){
    QueueL*qp;
    qp=createEmptyQueueL();
    ElementL*e;
    e=q0->myfrontl;
    while(e!=NULL){
        enqueueL(qp, StateToIndex_Q(e->datal));
        e=e->next;
    }
    return qp;
}


QueueL*IndexToState_QL(QueueL*q0){
    QueueL*qp;
    qp=createEmptyQueueL();
    ElementL*e;
    e=q0->myfrontl;
    while(e!=NULL){
        enqueueL(qp, IndexToState_Q(e->datal));
            e=e->next;
        }
    return qp;
}
QueueLL*StateToIndex_QLL(QueueLL*Q){
    QueueLL*QP;
    QP=createEmptyQueueLL();
    ElementLL*E;
    E=Q->myfrontll;
    while(E!=NULL){
        enqueueLL(QP, StateToIndex_QL(E->datall));
        E=E->next;
    }
    return QP;
}

QueueLL*IndexToState_QLL(QueueLL*Q){
    QueueLL*QP;
    QP=createEmptyQueueLL();
    ElementLL*E;
    E=Q->myfrontll;
    while(E!=NULL){
        enqueueLL(QP, IndexToState_QL(E->datall));
        E=E->next;
    }
    return QP;
}

void GetFinalSt(QueueL*N,///dfa data as index form
                Queue*q2, ///old final state
                Queue*q22){///new final state
    ElementL*e=N->myfrontl;
    int m=0;
    while(e!=NULL){
            if(cmpDataInQ(e->datal, q2)==1){
                  enqueueI(q22, m);
            }
        m++;///get what index of N that has final state
        e=e->next;
    }
}




