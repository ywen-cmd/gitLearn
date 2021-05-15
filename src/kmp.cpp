#include<iostream>
#include<string>
#include<memory.h>
using namespace std;

//fd eda:ywen
void getNext(int* next, const string& s) {
    int j = -1;
    next[0] = j;
    for(int i = 1; i < s.size(); i++) {  
        //回溯能回溯多次，直到-1
        //但是前进只能在之前的基础上前进1个
        //下面这段代码就是在进行一个动态规划的逻辑  
        while (j >= 0 && s[i] != s[j + 1]) { 
            j = next[j]; 
        }
        if (s[i] == s[j + 1]) { 
            j++;
        }
        next[i] = j; 
    }
}

// error here
// int a=4;
// int m[a];

//O(m+n)
int main(){
    string s("aabaaf");
    int next[s.size()];
    memset(next,0,sizeof(next)/sizeof(int));
    //getNext
    getNext(next,s);
    cout<<"next[]:";
    for(int i = 0;i<s.size();i++){
        cout<<next[i]<<" ";
    }
    //debug string
    string t("aabaaraaabbbaabaafffaaafdabafbafbabababaababababaabaafsdaasaabbbfbfafbababfabfabbbabaabaababbaabaafffaa");
    //test limit about 1.5,more will std::bad alloc,num:10000000
    //2 is high level bound
    for(int i = 0;i<10;i++){
        t.append("aabaaraaabbbaabaafffaaafdabafbafbabababaababababaabaafsdaasaabbbfbfafbababfabf");
    }
    //KMP
    int i,j,times=0;
    int init_i=0;
    bool off =0;
    bool kmp_done =0;
    //debug
    int ops_count=0;
    while(!off){    
        //Multi
        for(i = init_i, j = 0; i < t.size() && j < s.size(); ) {
            if(t[i] == s[j]) {
                i++;
                j++;
                //
                ops_count++;
            }
            else if(j == 0){
                i++;
                ops_count++;
            }
            else{
                j = next[j-1] + 1;
                ops_count++;
            }
        }

        if(j == s.size()){
            cout<<"\nKMP "<<times<<" Launch"<<endl;
            times++;
            // cout<<"pos:"<<i-s.size()<<"\t";
            cout<<"pos:"<<i-s.size()<<"\n";
            // for(int k=i-s.size();k<i;k++){
            //     cout<<t[k];
            // }            
            
            for(int k=0;k<i-s.size();k++){
                cout<<"->";
            }

            cout<<s<<endl;
            //compare
            // for(int k=0;k<i;k++){
            //     cout<<t[k];
            // }          
            // cout<<t<<endl;
            // cout<<endl;
            kmp_done = 1;
        }
        //init change
        init_i = i - s.size()+1;
        //set off
        if(i==t.size()) off=1;
    }

    if(kmp_done == 0)
        cout<<"\nkmp:false\n";

    cout<<"\nops:"<<ops_count<<endl;
    cout<<"m+n:"<<t.size()+s.size()<<endl;
    cout<<"n:"<<t.size()<<endl;
    cout<<"rate[ops/(m+n)]:"<<double(ops_count)/(t.size()+s.size())<<endl;

    return 0;
}