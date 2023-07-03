


void Non_accessible_state(QueueL*Q, ///DFA data
                          Queue*qn,///non accessible state
                            Queue*qa){/// accessible state

    enqueueI(qa, 0);
    for( int i=1;i<Q->nl;i++){
        int m=0;
        int a=0;//a=0 if that state  cant access to state n
        ElementL*e;
        e=Q->myfrontl;
        while(e!=NULL){
            if(m!=i && existElementInQ(e->datal,i)==1){
                a=1;//when i state can be accessed
            }
            e=e->next;
            m++;
        }
        if(a==0){
            enqueueI(qn, i);
        }else{
            enqueueI(qa, i);
        }
    }
}




int Distinguishable_a_pair(Queue*q2, int m, int n){///check if state n, m distinguishable or not
                                            ///not distinguishable if both m and n are not final state or  both are final state
    int h=1;
        if(existElementInQ(q2,m)==1 && existElementInQ(q2,n)==1){///if both final states
            h=0;
        }
        if(existElementInQ(q2,m)==0 && existElementInQ(q2,n)==0){///if both are not final state
            h=0;
        }
        return h;///h=1 if is distinguishable,
}



void Distinguishable_all_pair(QueueL*Q,/// dfa data
                              QueueL*D, ///store pair of distinguishable state
                              QueueL*D1, /// store non distinguishable state
                              Queue*q2){///final states
    Queue*qn;
    Queue*qa;
    qn=createEmptyQueue();
    qa=createEmptyQueue();
   Non_accessible_state(Q, qn, qa);
    Element*e;
    Queue*d;;
    Queue*d1;
        for(int i=0;i<Q->nl;i++){
            for(int j=0;j<i;j++){///these 2 loops are to create ...like a triangle table, in lesson
                    d=createEmptyQueue();
                    d1=createEmptyQueue();
                    e=qn->myfront;
                    int z=1;
                    while(e!=NULL){
                        if(i!=e->num && j!=e->num){///make exception for non accessible state
                           z=1;
                        }else{
                            z=0;
                            break;
                        }
                        e=e->next;
                    }
                    if(z==1){
                            if(Distinguishable_a_pair(q2,j,i)==1){
                                enqueueI(d,j);
                                enqueueI(d,i);
                                enqueueL(D,d);
                            }else{
                                enqueueI(d1,j);
                                enqueueI(d1,i);
                                enqueueL(D1,d1);
                            }
                    }
            }
    }
}




Queue* unmarked_pair(QueueL*Q, Queue*qm,int idxsym){///to get new pair when transition by idxsym
    int m=qm->myfront->num;
    int n=qm->myrear->num;//as it only have 1 pair or 2 data, so can put like this
    Queue*q;
    q=createEmptyQueue();

    m=stateDFA(Q, m, idxsym);
    n=stateDFA(Q, n, idxsym);

    enqueueI(q, m);
    enqueueI(q, n);
    Queue*qn;
    qn=createEmptyQueue();
    SortQueue(q, qn);
    return qn;///this just return the new pair when input a symbol
}

///This function is to retrieve all marked pair by doing recursive

int n=0,k=0;
void examine_all_unmarked_pair(QueueL*Q, ///All old dfa data
                               QueueL*D, ///  distinguishable pair or marked pair
                               QueueL*D1, /// non distinguishable pair or unmarked pair
                               ElementL*e,///to take elementL from D, as it store Distinguishable pair
                               int nsym){///index of symbol

        n=D->nl;//number of queue in marked pair
        e=D1->myfrontl;
        while(e!=NULL){//load all unmarked pair
                k=0;
            for(int i=0;i<nsym;i++){//loop symbol index
                if(cmpQ2L(D,unmarked_pair(Q, e->datal, i))!=-1){
                    k=1;
                    break;//when this pair equal to one of marked pair
                    }
            }
            if(k==1){//add to marked pair
                if(cmpQ2L(D, e->datal)==-1){//if it hasn't added to D
                    enqueueL(D, e->datal);
                }
            }
        e=e->next;
    }
   if(D->nl!=n){/// here call it again if got new marked pair into D2
     examine_all_unmarked_pair(Q, D, D1, e, nsym);
   }else{///stop if no new mark pair
    n=0,k=0;///reset both value to 0;
   }
}

void getEquivalence_pair(QueueL*D, /// all marked pairs
                         QueueL*D1, /// unmarked pair (before marked)
                         QueueL*D2){/// to remaining unmarked pair or equivalence pair

    ElementL*E1;
    E1=D1->myfrontl;
    while(E1!=NULL){
        if(cmpQ2L(D, E1->datal )==-1){//if pair  D1 are not in D then it is remaining unmarked pair
            enqueueL(D2, E1->datal);
        }
        E1=E1->next;
    }
}

void groupEquivalence(QueueL*D2, QueueL*D3){///to group them so have to compare themselves
    ElementL*E;
    ElementL*T;
    E=D2->myfrontl;
    int n=0;///start from first ElementL
    while(E!=NULL){
        T=D2->myfrontl;
        int m=0;///also first ElementL
        while(T!=NULL){
            if(m!=n && cmp_Q1_Q2(E->datal, T->datal)==1){
                    if(cmpQ2L(D3, T->datal)==-1){
                        enqueueL(D3, T->datal);
                    }

            }else{
                    if(cmpQ2L(D3, T->datal)==-1){
                        enqueueL(D3, T->datal);
                    }
            }
            m++;
            T=T->next;
        }
        n++;
        E=E->next;
    }
}
void GroupNew_State(QueueL*D3, Queue*qa, QueueL*D4){
    Queue*tmp;

    ElementL*E;
    Element*e;
    e=qa->myfront;
    while(e!=NULL){
        E=D3->myfrontl;
        int y=0;
        while(E!=NULL){
            if(existElementInQ(E->datal, e->num)==1){///if this state is in equivalence group
               y=1;
               if(cmpQ2L(D4, E->datal)==-1){
                    enqueueL(D4, E->datal);
               }
               break;///meet condition so no need to loop more
            }
            E=E->next;
        }
        if(y==0){///that state not in equivalence group
            tmp=createEmptyQueue();
            enqueueI(tmp, e->num);
            enqueueL(D4, tmp);
        }
        e=e->next;
    }

}
void DFA_After_Minimize(QueueL*Q, ///Old DFA data
                        QueueL*D4, /// group of state for new DFA
                        QueueL*Q1){///to new DFA data after convert
    Queue*q;
    int nsym=Q->myfrontl->datal->n;///number of symbol
    ElementL*E;
    E=D4->myfrontl;
    while(E!=NULL){
            q=createEmptyQueue();
        for(int i=0;i<nsym;i++){
            enqueueI(q,  existElementInQL(D4, stateDFA(Q, E->datal->myfront->num, i)));
        }
    enqueueL(Q1, q);
        E=E->next;
    }
}


void Minimization(QueueL*Q,///old DFA data
                  QueueL*Q1, ///new DFA data after minimize
                  Queue*q2, ///old final state
                  Queue*q22){///new final for DFA
    int nsym=Q->myfrontl->datal->n;
    int nst=Q->nl;

    Queue*qn;
    Queue*qa;
    QueueL*D;
    QueueL*D1;
    QueueL*D2;
    QueueL*D3;
    QueueL*D4;
    ElementL*E;

    qn=createEmptyQueue();
    qa=createEmptyQueue();
    D=createEmptyQueueL();
    D1=createEmptyQueueL();
    D2=createEmptyQueueL();
    D3=createEmptyQueueL();
    D4=createEmptyQueueL();

    Non_accessible_state(Q, qn, qa);
    Distinguishable_all_pair(Q, D, D1, q2);
    examine_all_unmarked_pair(Q, D, D1, E, nsym);
    getEquivalence_pair(D, D1, D2);
    groupEquivalence(D2, D3);
    GroupNew_State(D3, qa, D4);
    DFA_After_Minimize(Q, D4, Q1);
    GetFinalSt(D4, q2, q22);
}
