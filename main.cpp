#include<iostream>
#include<iomanip>
#include<string>
#include<fstream>
#include<string.h>
using namespace std;
#include"List_Queue.h"
#include"general_function.h"
#include"Display.h"
#include"FA_data.h"
#include"Convert_NFA_TO_DFA.h"
#include"Design_Test_string_FA_NFAorDFA.h"
#include"Minimization.h"
#include"save_load_delete_update.h"
void Menu(){

    cout<<"\n\t\tMenu"<<endl;
    cout<<"\t\t1. Design a Finite Automation(FA)."<<endl;
    cout<<"\t\t2. Test if FA is deterministic or non-deterministic."<<endl;
    cout<<"\t\t3. Test if a string is accepted by FA."<<endl;
    cout<<"\t\t4. Construct an equivalence DFA from an NFA."<<endl;
    cout<<"\t\t5. Minimize a DFA."<<endl;
    cout<<"\t\t6. Load, Delete and Update FA."<<endl;

}

void Enter_option(int *n, int p, int q){
    string s1;
    int s=0;
    while(s==0){
        cout<<"\n\t     >>>Enter option: ";
        cin>>s1;
        if(s1.length()!=1 ||(s1[0]<p+48 || s1[0]>q+48)) cout<<"\tMake sure to enter number from "<<p<<" to "<<q<<"!";
        else s=1;
        }s=0;
        istringstream(s1)>>*n;
}

void Enter_option2(string *fname, int p=NULL){
    while(1){
        cout<<"\t\t   0. Cancel this feature. \n\t\t   1. See all data. \n\t\t   Otherwise enter ID."<<endl;
        cout<<"\t    >>>Enter ID: ";
        cin>>*fname;
        if(*fname=="0")  break;
        else if(*fname=="File_name")  cout<<"\t\tThis ID is banned, try another one."<<endl;
        else if(*fname=="1") show_All_file_data();
        else if(p!=NULL &&exist_file(*fname)==1) cout<<"\t\tID's already existed, try another one."<<endl;
        else if(p==NULL &&exist_file(*fname)==0)    cout<<"\t\tID not found, try again."<<endl;
        else break;
    }
}

main(){
    int n;
    string  m;
    int c=0;
    int d=0;
    string fname;//file name
    QueueLL*QN;//
    QueueL*QDM;//
    QueueL*QDC;//
    Queue*q1;
    Queue*q2;
    Queue*q3;
    Queue*qcf;
    Queue*qmf;
   cout<<"\t\t\t \t xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"<<endl;
    cout<<"\t\t\t\t<<<< Welcome to Finite Automation(FA) program >>>>>"<<endl;
    cout<<"\t\t\t \t xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"<<endl;
    Menu();
    cout<<"\t\t7. See menu again"<<endl;
    cout<<"\t\t8. Close the program."<<endl;;
    while(1){
        Enter_option(&n, 1, 8);
        if(n==8){
            cout<<"\t\t***Close program."<<endl;
            break;
        }else if(n==1){
            cout<<"\t\t1. Design a Finite Automation(FA)."<<endl;
            q1=createEmptyQueue();
            q2=createEmptyQueue();
            q3=createEmptyQueue();
            designFA(q1, q2, q3);
            QN=createEmptyQueueLL();
            storeNFA(QN, q1, q3);
            cout<<"\t\t\t\t\tFA Table";
            FA_Table(QN, q2, q3);
            cout<<"\t\tEnter 1 to save otherwise not"<<endl;
            cout<<"\t\tEnter:  ";
            cin>>m;
            if(m=="1"){
                Enter_option2(&fname, 1);
                if(fname!="0"){
                Save_Queue_To_txt(q1, q2, q3, fname);
                Save_File_Name(fname);
                 cout<<"\t\tFA saved successfully."<<endl;
                }
            }
            c=1;
        }else if(n==2 && c==1){
            cout<<"\t\t2. Test if FA is deterministic or non-deterministic."<<endl;
            if(DFA_or_NFA(QN)==1) cout<<"\t    >>>>FA is non-deterministic."<<endl;
            else                  cout<<"\t    >>>>FA is deterministic."<<endl;


        }else if(n==3 && c==1){
            cout<<"\t\t3. Test if a string is accepted by FA."<<endl;
            string str;
            cout<<"\t     >>>Enter string to test: ";
            cin>>str;
            Test_string_FA(StateToIndex_QLL(QN), StateToIndex_Q(q2), q3, str);

        }else if(n==4 && c==1){
            cout<<"\t\t4. Construct an equivalence DFA from an NFA."<<endl;
            cout<<"\t\t4. New DFA after conversion:"<<endl;
            qcf=createEmptyQueue();
            QDC=createEmptyQueueL();
            New_DFA_after_Convert(StateToIndex_QLL(QN), QDC, StateToIndex_Q(q2), qcf);
            DFA_Table(IndexToState_QL(QDC), IndexToState_Q(qcf), q3);
            d=1;
        }else if(n==5 && c==1){
            cout<<"\t\t5. Minimize a DFA."<<endl;
            if(DFA_or_NFA(QN)==1 && d==0)    cout<<"\t\tCan minimize unless it is DFA, convert it first."<<endl;
            else{
                if(d==0){
                    QDC=createEmptyQueueL();
                    storeDFA(QN, QDC);
                    QDC=StateToIndex_QL(QDC);
                    qcf=q2;
                    qcf=StateToIndex_Q(qcf);
                }
                cout<<"\t\t\DFA after minimization: "<<endl;
               QDM=createEmptyQueueL();
                qmf=createEmptyQueue();
                Minimization(QDC, QDM, qcf, qmf);
                DFA_Table(IndexToState_QL(QDM), IndexToState_Q(qmf), q3);
            }

        }else if(n==6){
            cout<<"\t\t6. load, Delete and update FA."<<endl;
            cout<<"\t\t   1. Load.\n\t\t   2. Delete. \n\t\t   Otherwise Update."<<endl;
            cout<<"\t    >>>Enter: ";   cin>>m;
            if(m=="1"){
                cout<<"\t\tLoad FA: "<<endl;
                Enter_option2(&fname);
                if(fname!="0"){
                    QN=createEmptyQueueLL();
                    q1=createEmptyQueue();
                    q2=createEmptyQueue();
                    q3=createEmptyQueue();
                    Load_Queue_From_txt(q1, q2, q3, fname);
                    storeNFA(QN, q1, q3);
                    FA_Table(QN, q2, q3);
                    c=1;
                }
            }else if(m=="2"){
                cout<<"\t\tDelete FA: "<<endl;
                Enter_option2(&fname);
                if(fname!="0") delete_file(fname);

            }else{
                cout<<"\t\tUpdate FA: "<<endl;
                Enter_option2(&fname);
                if(fname!="0"){
                    QN=createEmptyQueueLL();
                    q1=createEmptyQueue();
                    q2=createEmptyQueue();
                    q3=createEmptyQueue();
                    Load_Queue_From_txt(q1, q2, q3, fname);
                    storeNFA(QN, q1, q3);
                    FA_Table(QN, q2, q3);

                    QN=createEmptyQueueLL();
                    q1=createEmptyQueue();
                    q2=createEmptyQueue();
                    q3=createEmptyQueue();
                    designFA(q1, q2, q3);
                    Save_Queue_To_txt(q1, q2, q3, fname);
                    storeNFA(QN, q1, q3);
                    FA_Table(QN, q2, q3);
                    cout<<"\t\tFA updated successfully."<<endl;
                    c=1;
                }
              }
        }else if(n==7) Menu();
         else   cout<<"\t\tNo data found. Try to insert or load first."<<endl;
    }
}











