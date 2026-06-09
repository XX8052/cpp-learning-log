--- cpp
        else if(choice==4){
            int id;
            cout<<endl<<"--Bank Account Showing System--"<<endl<<"please enter your account id "<<endl;
            cin>>id;
            bool found=false;
            for(int i=0;i<bankaccounts.size();i++){
                if(bankaccounts[i].verify(id)){
                    bankaccounts[i].show();
                    bool found = true;
                    pauseScreen();
                    break;
                }
            }
            if(!found){
                cout << "Account not found" << endl;
            }
        }
---
