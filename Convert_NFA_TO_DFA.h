

///Do eclosure on a state, Use Recursive

void EClose0(QueueLL*Q,///NFA data
                Queue*qn,///store result after this Eclosure
                int idxst,///index of state to do Eclosure
                Element*e){

        if(stateNFA(Q, idxst, Q->myfrontll->datall->nl-1)->n==0){///if this state doesn't have epsilon transition
            if(existElementInQ(qn,idxst)==0){///if it hasn't added to qn
                enqueueI(qn,idxst);
            }
        }else if(existElementInQ(qn,idxst)==0){///if this state hasn't added to qn, if it does, means it's already do Eclosure
                enqueueI(qn,idxst);
                e=stateNFA(Q, idxst, Q->myfrontll->datall->nl-1)->myfront;///access to rear element for epsilon
                while(e!=NULL){
                    idxst=e->num;
                    EClose0(Q, qn, idxst, e);
                    e=e->next;
            }
        }
}


void EClose(QueueLL*Q,///NFA data
            Queue*qs, ///set  if state to do Eclosure
            Queue*qm){/// store result and sort

    Queue*qn;
    qn=createEmptyQueue();
    Queue*qt[qs->n];
    for(int i=0;i<qs->n;i++){
        qt[i]=createEmptyQueue();
    }//displayQueueN(qs);
    Element*tmp;
    Element*e;
    tmp=qs->myfront;
    int j=0;
    while(tmp!=NULL){
        EClose0(Q, qt[j],tmp->num,e);
        j++;
        tmp=tmp->next;
    }
//////////////////////////////////////
    //put all states of qt[] together in to qn without duplicate number
    Element*E;
    for(int i=0;i<qs->n;i++){
        E=qt[i]->myfront;
        while(E!=NULL){
            if(existElementInQ(qn, E->num)==0){//
                enqueueI(qn, E->num);
            }
            E=E->next;
        }
    }
////////////////////////////////////
    //sort them
    SortQueue(qn, qm);///sort them to compare in next function
   // cout<<" reacesesewswh: ";

}

void sstate(QueueLL*Q, ///NFA data
            Queue*qs, /// set state ...fine what its transition when do EClosure
            int idxsym, ///index symbol
            Queue*qn){/// store new state and do Elcosure after input idxsym


    Queue*qm;///to store new set of state from qs after transition by idxsym then do Eclosure below
    qm=createEmptyQueue();
    Element*e;
    Element*T;
    e=qs->myfront;
    while(e!=NULL){//access to qs
       T=stateNFA(Q, e->num, idxsym)->myfront;
       while(T!=NULL){
        if(existElementInQ(qm, T->num)==0){
            enqueueI(qm, T->num);
        }
        T=T->next;
       }
       e=e->next;
    }
    EClose(Q, qm, qn);///do EClosure and output store in qn;
}



int q=0;///state
void ConvertNFAtoDFA(QueueLL*Q,///Data of NFA----constant
                     int nsym,///number of symbol
                     QueueL*Q0, ///List of state, we dont know how many we will create so use QueueL, Can call New DFA---upadate
                     QueueL*N, ///Store all set of state when process sstate, from T---upadate
                     Queue*T, ///store sstate result, then reset to store another sstate result---upadate
                     Queue*qs, ///set of number to put in sstate---upadate
                     Queue*tmp, ///store new state for DFA, then insert to qo---upadate
                     ElementL*e){


tmp=createEmptyQueue();
    if(q==0){///start state
        enqueueI(qs,0);
        EClose(Q, qs, T);///do EClosure
        enqueueL(N,T);///here we have set for q'0
        e=N->myfrontl;
        q++;

        ConvertNFAtoDFA(Q, nsym, Q0, N, T, qs, tmp, e);
    }
    else if(e==NULL){///if we still cant find new set to store in N, the recursive ends
        q=0;/// recursive end here, reset q to 0
    }
    else{

        qs=e->datal;/// access to set that we got from...storing in N,
        T=createEmptyQueue();/// if meet empty set, this program assign -2 to it
        enqueueI(T,-2);
        if(cmp_Q1_Q2(qs, T)==1){///if qs=T mean reach empty set, also mean it already exist in N
            for(int i=0;i<nsym;i++){
                enqueueI(tmp, cmpQ2L(N, T));///get what its index, it reach empty set unless
                                            ///it has already meet before in down(else) condition
            }
            enqueueL(Q0, tmp);
            e=e->next;///move to next set
        }else{
            for(int i=0;i<nsym;i++){
                T=createEmptyQueue();
                sstate(Q, qs,i, T);

                if(T->myfront==NULL){/// in case we get empty set, so need assign a value
                    enqueueI(T, -2);///so if other also empty will also use this...state
                                    ///can use any number except 0,1,2....but here we decide to assign it -2
                                    /// because state can not be negative here
                }
                if(cmpQ2L(N,T)==-1){///if not yet in N
                    enqueueL(N, T);
                    enqueueI(tmp, q);
                    q++;
                }else{/// if in N, so find which state/index
                    enqueueI(tmp,cmpQ2L(N, T));
                }
        }
        enqueueL(Q0,tmp);
        e=e->next;
        }
        ConvertNFAtoDFA(Q, nsym, Q0, N, T, qs, tmp, e);///continue until no new set input to N then e==NULL, recursive ends
    }
}

void New_DFA_after_Convert(QueueLL*Q, ///NFA data
                           QueueL*Q0, ///New DFA after convert
                           Queue*q2, ///old final state (NFA)
                           Queue*q22){///New final state for DFA
    int nsym=Q->myfrontll->datall->nl-1;///number of  symbol, -1 to exclude epsilon
    QueueL*N;
    Queue*T;
    Queue*qs;
    Queue*tmp;
    ElementL*e;

    N=createEmptyQueueL();
    T=createEmptyQueue();
    qs=createEmptyQueue();
    tmp=createEmptyQueue();

    ConvertNFAtoDFA(Q, nsym, Q0, N, T, qs, tmp, e);

    GetFinalSt(N, q2, q22);
}




