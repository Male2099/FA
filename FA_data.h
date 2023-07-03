/**
void storeNFA(): if fa is NFA store data using this function
void storeNFA(): if fa is DFA store data using this function
void stateDFA(): input a symbol the state then return state transition by input symbol

no state NFA because it has no use unless we do Eclose so it is in sstate in NFA_To_DFA.h header file
*/

void storeNFA( QueueLL*Q,///QueueLL, its element is QueueL store 1 state transition and QueueL store transition by s symbol or 1 symbol need 1 queue
              Queue*q1,///set of transition form as string for each state
              Queue*q3)///symbols
    {
    QueueL*QN;///to store
    Queue*q;///store each state of q1, then reset when move to other state
    int i;
    int n=q3->n+1;///symbol+1 for epsilon transition, so one more queue

    Element*e;
    e=q1->myfront;
    while(e!=NULL){///ex: q1,q2,q3;q4;;q4,q5;
        QN=createEmptyQueueL();
        string s=e->data;///state transition
        int y=0;/// update when storing other transition by any symbol
        for(int j=0;j<n;j++){
            q=createEmptyQueue();
            for(i=y;i<s.length();i++){//ex: s="q123;q2;q3,q1"
                if(s[i]==';'){//when transition by next symbol
                    i++;
                    break;
                }
                if(s[i]!=','){//when a symbol can cause to transition more then 1 state
                    if(s[i+1]!=',' && s[i+2]!=',' &&s[i+2]!=';' && s[i+3]!=',' && s[i+3]!=';'){;
                        enqueueS(q, s.substr(i,4));
                        i=i+3;
                    }
                    else if(s[i+2]!=',' && s[i+2]!=';'){
                        enqueueS(q, s.substr(i,3));
                        i=i+2;
                    }else{
                        enqueueS(q, s.substr(i,2));
                        i=i+1;
                    }
                }
            }
            enqueueL(QN, q);
        y=i;
        }
        enqueueLL(Q, QN);
        e=e->next;
    }
}



void storeDFA(QueueLL*Q, QueueL*QD){///store data in QueueL, each Queue in QueueL store data of one state
    Queue*q;
    ElementLL*E;
    ElementL*e;
    E=Q->myfrontll;
    while(E!=NULL){
        e=E->datall->myfrontl;
        q=createEmptyQueue();
        while(e!=NULL && e!=E->datall->myrearl){
            enqueueS(q, e->datal->myfront->data);
            e=e->next;
        }
        enqueueL(QD, q);
        E=E->next;
    }
}

int stateDFA(QueueL*Q/// state to choose
             ,int idxst///index of state
             ,int idxsym){//consider it is DFA so we just retrieve the index state when input symbol in r
    int r;//index of state to return only because it is DFA
    ElementL*E;
    Element*e;
    E=Q->myfrontl;
    int n=0;
    while(E!=NULL){
        if(n==idxst){
            e=E->datal->myfront;
            int m=0;
            while(e!=NULL){
                if(m==idxsym){
                    r=e->num;
                    break;
                }
                m++;
                e=e->next;
            }
        }
        n++;
        E=E->next;
    }
    return r;/// return index of state when receive symbol index idxsym
}

Queue* stateNFA(QueueLL*Q, ///nfa data
              int idxst, ///index of state
              int idxsym ///index of symbol
              ){
    Queue*qr;
    qr=createEmptyQueue();
    ElementLL*E;
    ElementL*e;
    Element*s;
    E=Q->myfrontll;
    int n=0;//begin from 1st state
    while(E!=NULL){
        if(n==idxst){
            e=E->datall->myfrontl;
            int m=0;
            while(e!=NULL){
                if(m==idxsym){
                    s=e->datal->myfront;
                    while(s!=NULL){
                        enqueueI(qr, s->num);
                        s=s->next;
                    }
                    break;
                }
                m++;
                e=e->next;
            }
            break;
        }
        n++;
        E=E->next;
    }
    return qr;
}
