

void designFA(Queue*q1,///store all transition functions
              Queue*q2,///store final state
              Queue*q3){///store symbol
    string nst;///number of state
    string sst;///start state
    string fst;///final state
    string sym;///symbol
    int n;
    cout<<"\t\tEnter number of state: ";
    cin>>nst;
    cout<<"\t\tStart state have to be: q0\n";
    cout<<"\t\tFinal state : ";
    cin>>fst;
    cout<<"\t\tSymbol: ";
    cin>>sym;
    istringstream(nst)>>n;
    cout<<"\t\tInput the transition function all "<<n<<" states\n";

    for(int i=0;i<n;i++){
        string data;
        cout<<"\t\tq"<<i<<": ";
        cin>>data;
        enqueueS(q1,data);
    }

           for(int i=0;i<fst.length();i++){
                if(fst[i]!=','){
                    if(fst[i+1]!=',' && fst[i+2]!=',' && fst[i+3]!=','){;
                        enqueueS(q2, fst.substr(i,4));
                        i=i+3;
                    }
                    else if(fst[i+2]!=','){
                        enqueueS(q2, fst.substr(i,3));
                        i=i+2;
                    }else{
                        enqueueS(q2, fst.substr(i,2));
                        i=i+1;
                    }
                }
        }
    for(int i=0;i<sym.length();i++){
            if(sym[i]!=','){
                enqueueC(q3,sym[i]);
                i++;
            }
    }
}


int DFA_or_NFA(QueueLL*Q){///FA data
    ElementLL*E;
    ElementL*T;
    Element*e;
    int n=0;
    E=Q->myfrontll;
    while(E!=NULL){
        if(E->datall->myrearl->datal->n!=0){///if there are at least one epsilon transition, so it is NFA
            n=1;
            break;
        }
        else{
            T=E->datall->myfrontl;
            while(T!=NULL && T!=E->datall->myrearl){///exclude epsilon as it is store at myrearl
                if(T->datal->n!=1){///if a symbol cause not 1 transition, can be zero  or more then one
                    n=1;
                    break;
                  }
                T=T->next;
            }
            if(n==1) break;
        }
        E=E->next;
    }

    return n;///n=1 if it's NFA
             ///n=0 if it's DFA
}






int Z=0;///start state
void Process_String(QueueLL*Q, ///FA data
                    Queue*qs, ///set of state to input into FA, change to qm as qm will be use to input next symbol
                    Queue*qm,/// outcome from input qs
                    Queue*q2,///set of final state
                    Queue*q3,/// set symbol
                    string str){///string to test
    if(Z==0){///start from start state
        enqueueI(qs, 0);
        EClose(Q, qs, qm);
        qs=qm;
        qm=createEmptyQueue();
        sstate(Q, qs, indexSym(q3, str[Z]), qm);//
        Z++;
        Process_String(Q, qs, qm, q2, q3, str);
    }else if(Z==str.length()){///stop recursive then check if qm, its outcome has a final state or not
            Z=0;//reset Z;
            if(cmpDataInQ(qm, q2)==1){
                cout<<"\t\tThe String "<<str<<" is accept"<<endl;
            }else{
                cout<<"\t\tThe String "<<str<<" is not accept"<<endl;
            }
    }else{
        qs=qm;
        qm=createEmptyQueue();
        sstate(Q, qs, indexSym(q3, str[Z]), qm);
        Z++;
        Process_String(Q, qs, qm, q2, q3, str);///do recursive until reach last symbol, then Z= length of symbol
    }
}


void Test_string_FA(QueueLL*Q, ///FA data to test
                    Queue*q2, ///finals state
                    Queue*q3, ///symbol
                    string str){///string to test
    Queue*qs;
    Queue*qm;
    qs=createEmptyQueue();
    qm=createEmptyQueue();
    Process_String(Q, qs, qm, q2, q3, str);
}
