
void Load_Queue_From_txt(Queue*q1, Queue*q2, Queue*q3, string fname){
    fstream f1;
    string line;
    string sym;
    string fst;
    f1.open(fname+ ".txt", ios::in);
    getline(f1, sym);
    getline(f1, fst);
    while(!f1.eof()){
        getline(f1, line);
        enqueueS(q1, line);
    }
    f1.close();

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

void Save_Queue_To_txt(Queue*q1, Queue*q2, Queue*q3, string fname){
    fstream f1;
    Element*e;
    f1.open(fname+".txt", ios::out);
     e=q3->myfront;
     while(e!=NULL){
        f1<<e->c;
        if(e!=q3->myrear) f1<<',';
        e=e->next;
     }f1<<endl;

    e=q2->myfront;
    while(e!=NULL){
        f1<<e->data;
        if(e!=q2->myrear) f1<<',';
        e=e->next;
    }f1<<endl;

    e=q1->myfront;
    while(e!=NULL){
        f1<<e->data;
        if(e!=q1->myrear) f1<<endl;
        e=e->next;
    }
    f1.close();

}

void Save_File_Name(string fname){
    int n=1;
    fstream f1;
    string line;
    f1.open("File_name.txt", ios::app);
        f1<<endl<<fname;
        if(!f1.eof());
    f1.close();

}

int exist_file(string fname){
    int n=0;
    fstream f1;
    string line;
    f1.open("File_name.txt", ios::in);
    while(!f1.eof()){
        getline(f1, line);
        if(line==fname){
            n=1;
            break;
        }
    }
    f1.close();
    return n;//1 when file exist
}

void delete_file(string fname){

    char c[fname.length()+5];
    strcpy(c, (fname+".txt").c_str());

    remove(c);
    fstream f1;
    string line;
    Queue*q;
    q=createEmptyQueue();
    f1.open("File_name.txt", ios::in);
    getline(f1, line);
    while(!f1.eof()){
        getline(f1, line);
        enqueueS(q, line);
    }
    f1.close();

    Element*e;
    e=q->myfront;
    f1.open("File_name.txt", ios::out);
    while(e!=NULL){
        if(e->data!=fname){
            f1<<endl<<e->data;
        }
        e=e->next;
    }
    f1.close();
    cout<<"\t\tFA deleted successfully."<<endl;
}


void show_All_file_data(){
    fstream f1;
    string line;
    QueueLL*Q;
    Queue*q;
    Queue*q1;
    Queue*q2;
    Queue*q3;
    q=createEmptyQueue();

    f1.open("File_name.txt", ios::in);
    getline(f1, line);
    while(!f1.eof()){
        getline(f1, line);
        enqueueS(q, line);
    }
    f1.close();
    if(q->n==0) cout<<"\t\tNo FA data found, insert them first."<<endl;
    else{
        Element*e;
        e=q->myfront;
        while(e!=NULL){
            Q=createEmptyQueueLL();
            q1=createEmptyQueue();
            q2=createEmptyQueue();
            q3=createEmptyQueue();
            Load_Queue_From_txt(q1,q2,q3, e->data);
        cout<<"\n\t      >>>ID: "<<e->data;
            storeNFA(Q, q1, q3);
            FA_Table(Q, q2, q3);
cout<<endl;
            e=e->next;
        }
    }
}
void update_FA(string fname){

    fstream f1;
    QueueLL*Q;
    Queue*q1;
    Queue*q2;
    Queue*q3;
    Q=createEmptyQueueLL();
    q1=createEmptyQueue();
    q2=createEmptyQueue();
    q3=createEmptyQueue();

    Load_Queue_From_txt(q1,q2,q3, fname);
    storeNFA(Q, q1, q3);
    cout<<"\n\t      >>>ID:"<<fname;
    FA_Table(Q, q2, q3);


    q1=createEmptyQueue();
    q2=createEmptyQueue();
    q3=createEmptyQueue();
    designFA(q1, q2, q3);

    f1.open(fname+".txt", ios::out);
    Save_Queue_To_txt(q1, q2, q3, fname);
    f1.close();
    cout<<"\t\tFA updated successfully."<<endl;
}
