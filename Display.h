///most the function here are only for testing to see the result correct or not.



///display Queue as string
void displayQueueS(Queue *q){///also use to display DFA data
    Element *tmp;
    tmp=q->myfront;
     while(tmp!=NULL){
        cout<<tmp->data<<" ";

        tmp=tmp->next;
    }cout<<endl;
}



///display Queue, its data are integer
void displayQueueI(Queue *q){///only for testing
    Element *tmp;
    tmp=q->myfront;
     while(tmp!=NULL){
        cout<<tmp->num<<" ";

        tmp=tmp->next;
    }
    cout<<endl;
}
///display Queue data as character
void displayQueueC(Queue *q){
    Element *tmp;
    tmp=q->myfront;
    cout<<setw(28)<<("|");
    cout<<setw(7);
     while(tmp!=NULL){
        cout<<tmp->c;
        cout<<setw(17);
        tmp=tmp->next;
    }
}

void displayQueueC1(Queue *q){
    Element *tmp;
    tmp=q->myfront;
    cout<<setw(28)<<("");
    cout<<setw(7);
     while(tmp!=NULL){
        cout<<tmp->c;
        cout<<setw(17);
        tmp=tmp->next;
    }
}


///display QueueL data as string
void displayQueueLS(QueueL *q){///only for testing
    ElementL* tmpL;
    tmpL=q->myfrontl;
     while(tmpL!=NULL){
    displayQueueS(tmpL->datal);
        tmpL=tmpL->next;
    }
    cout<<endl;

}


///display QueueL data as integer
void displayQueueLI(QueueL *q){///only for testing
    ElementL* tmpL;
    tmpL=q->myfrontl;
     while(tmpL!=NULL){

    displayQueueI(tmpL->datal);
        tmpL=tmpL->next;
    }
}


///display QueueLL data as integer
void displayQueueLLI(QueueLL *q){
    ElementLL* tmp;
    tmp=q->myfrontll;
     while(tmp!=NULL){

    displayQueueLI(tmp->datall);
        tmp=tmp->next;
    }
}

///display QueueLL data as string
void displayQueueLLS(QueueLL *q){
    ElementLL* tmp;
    tmp=q->myfrontll;
     while(tmp!=NULL){

    displayQueueLS(tmp->datall);
        tmp=tmp->next;
    }
}





void displayQueue_DFA(Queue *q){
    Element *tmp;
    tmp=q->myfront;
     while(tmp!=NULL){
        cout<<tmp->data<<"\t\t    ";
        tmp=tmp->next;
    }
}



///use for NFA to display data
void displayQueue_FA(Queue *q){
    Element *tmp;
    tmp=q->myfront;
     while(tmp!=NULL){
        cout<<tmp->data<<" ";
        tmp=tmp->next;
    }
}

void displayQueueL_FA(QueueL *q){
    ElementL* tmpL;
    tmpL=q->myfrontl;
    //cout<<left<<setw(10);
    int n;
    string s1=" ";
    string s2="  ";
    string s3="   ";
    string s4="    ";
    string s5="     ";
    string s6="      ";
    string s7="       ";
    string s8="        ";
    string s9="         ";
    string s10="          ";
     while(tmpL!=NULL){
        n=tmpL->datal->n;
        if(n==0){
            displayQueue_FA(tmpL->datal);cout<<s10<<s4;
        }else if(n==1){
           displayQueue_FA(tmpL->datal);cout<<s10<<s2;
        }else if(n==2){
       displayQueue_FA(tmpL->datal);cout<<s9;
        }else if(n==3){
            displayQueue_FA(tmpL->datal);cout<<s6;
        }else if(n==4){
       displayQueue_FA(tmpL->datal);cout<<s3;
        }else if(n==5){
       displayQueue_FA(tmpL->datal);cout<<s1;
        }else displayQueue_FA(tmpL->datal);
        tmpL=tmpL->next;
        cout<<s2;
    }
}



void FA_Table(QueueLL*Q, Queue*q2, Queue*q3){
    int nst=Q->nll;///number of state
    ElementLL*E;
    E=Q->myfrontll;


    cout<<"\n\t\t ___________________________________________________________________________"<<endl;
    displayQueueC(q3);cout<<setw(17)<<"E";
    cout<<"\n\t\t ----------|----------------------------------------------------------------";
    for(int i=0;i<nst;i++){
        cout<<endl<<setw(24);
            if(i>9 && existElementInQ(StateToIndex_Q(q2), i)==1){
                cout<<"  *q"<<i<<" |\t";
            }else if(i>9){
                cout<<"   q"<<i<<" |\t";
            }else if(i==0 && existElementInQ(StateToIndex_Q(q2),0)==1){
                cout<<" ->*q"<<i<<"  |\t";
            }else if(i==0){
                cout<<"  ->q"<<i<<"  |\t";
            }else if(existElementInQ(StateToIndex_Q(q2), i)==1){
                cout<<"   *q"<<i<<"  |\t";
            }else{
                cout<<"    q"<<i<<"  |\t";
            }
        displayQueueL_FA(E->datall);
        E=E->next;
    }
    cout<<"\n\t\t __________|________________________________________________________________"<<endl;
}

void DFA_Table(QueueL*Q, Queue*q2, Queue*q3){
    ElementL*E;
    E=Q->myfrontl;
    cout<<"\t\t\t\t\tDFA Table"<<endl;
    cout<<"\t\t ___________________________________________________________________________"<<endl;
    displayQueueC(q3);
    cout<<"\n\t\t ----------|----------------------------------------------------------------";
    for(int i=0;i<Q->nl;i++){
        cout<<endl<<setw(24);

            if(i>9 && existElementInQ(StateToIndex_Q(q2), i)==1){
                cout<<"   *q"<<i<<" |\t  ";
            }else if(i>9){
                cout<<"    q"<<i<<" |\t  ";
            }else if(i==0 && existElementInQ(StateToIndex_Q(q2),0)==1){
                cout<<" ->*q"<<i<<"  |\t  ";
            }else if(i==0){
                cout<<"  ->q"<<i<<"  |\t  ";
            }else if(existElementInQ(StateToIndex_Q(q2), i)==1){
                cout<<"   *q"<<i<<"  |\t  ";
            }else{
                cout<<"    q"<<i<<"  |\t  ";
            }
        displayQueue_DFA(E->datal);
        E=E->next;
    }
   cout<<"\n\t\t __________|________________________________________________________________"<<endl;
}



