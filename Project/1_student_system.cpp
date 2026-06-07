#include<iostream>
#include<string>
#include<vector>
using namespace std;
//自定义类型只能对单个变量设置函数方法 只针对一个变量
class Student{
private:
    string n;
    int s;
public:
    Student(string name,int score){
        n= name;
        s=score;
    }
    void show() const{
        cout<<"name: "<<n<<"    score: "<<s<<endl;
    }
    int getscore() const{
        return s;
    }
};
//设置函数 数组 进行全部展示 对多
void addstudents(vector<Student>& students ){
    string name;
    int score;
    cout<<"please enter:name score";
    cin>>name>>score;
    students.push_back(Student(name,score));
}
void showstudents(const vector<Student>& students){
    if(students.empty()){
        cout<<"haven't added any.";
    }
    else {
        for(int i=0;i<students.size();i++){
            students[i].show();//指明单个自定义变量
        }
    }
}
void studentsaverage(const vector<Student>& students){
    double average;
    int sum=0;
    for(int i=0;i<students.size();i++){
        sum=sum+students[i].getscore();
    }
    average=sum/(students.size());
    cout<<average;
}
int main(){
    vector<Student> students;
    int choice;
    cout<<endl<<"choose your intention"<<endl;
    cout<<"1 add student"<<endl<<"2 show students"<<endl<<"3 get average score"<<endl<<"4 break the syestem";
    while(true){
        cin>>choice;
        if(choice==1){
            addstudents(students);

        }
        else if(choice==2){

            showstudents(students);
        }
        else if(choice==3){
            studentsaverage(students);
        }
        else{
            break;
        }
        cout<<endl<<"what next";
    }
    return 0;
}
