#include<bits/stdc++.h>
#include <fstream>
using namespace std;
#define int long long

int inf= 1e18;

int findoptimaldp(string s,vector<vector<int>>&opt){
    ///
    /// The findoptimaldp function is used to find maximum number of loops present between any two indices in the DNA string
    /// by using dynamic programming and store the result in 2-Dimentional opt vector.
    ///
    int n = s.length();
    
    
    int k=5;        // window size
    int q=5;        // the end point of the window
    int p=0;        // the start point of the window

    map< char,int> m;
    m['A'] = -1;
    m['U'] = 1;
    m['C'] = -2;
    m['G'] = 2;
    
    if(n <6)
    {
        cout<<0<<endl;
        return 0;
    }
    
    /**
    *We initialize the opt vector by putting 0 for all the pair of indices whose difference of both indices is less than 5.
    *For the window size of 5, if the pair of indices create a matching(A-U || G-C) we initialize the opt vector to 1.
    */
    for( q=5; q<n; q++ )
    {
        if(m[s[q]]+ m[s[q-k]] == 0)
        {
            opt[q-k][q] = 1;
        }
    }

    if(n== 6)
    {
        cout<<opt[0][5]<<endl;
        return 0;
    }
    
    ///
    /// The algorithm iterates through different window sizes starting from 6. For each window size 'k', it iterates through the 
    /// substring whose endpoint start from k and traverse till n. The starting point of the substring is calculated by (p=endpoint-k).
    /// It calculates the optimal solution for each substring of length 'k' by considering all possible split points within the substring.
    ///
    for( k=6; k<n; k++)
    {
        for( q=k; q<n; q++)
        {
            ///
            /// here p and q represents the beginning and end point of window of size k and we store opt[p][q] where this values represents maximum number of pairs betweeen indices p and q
            /// we either choose the same value as opt[p][q-1] or iterate between p and q to find a nucleotide forming base pair with s[q]
            /// and choose maximum of all such pairs.
            /// The maximum of both the approaches will be considered as optimal solution for substring(p,q).
            ///
            int p= q-k;
            int x= opt[p][q-1];
            int y= -inf;
            
            ///
            /// We iterate through the substring(p,q-4). For each position 't' within this substring, it checks whether s[t] and s[q] create a matching pair using map 'm'.
            /// If it forms a matching pair, we split the optimal solution of substring into two parts by solving for substring(p,t-1) and substring(t+1,q-1).
            /// By choosing maximum values given by all such pairs by the formula opt[p][t-1] + opt[t+1][q-1] + 1, we choose maximum value betwenn this and opt[p][q-1].
            ///
            for(int t=p; t<q-4; t++)
            {
                if(m[s[t]]+ m[s[q]] == 0)
                {
                    if(t==p)
                    {
                        y= max(y, opt[t+1][q-1]+1);
                    }
                    else if(t== q-5)
                    {
                        y= max(y, opt[p][t-1]+1);
                    }
                    else
                    {
                        y = max(y, opt[p][t-1] +opt[t+1][q-1]+1);
                    }
                }
            }

            opt[p][q] = max(x,y);
        }
    }
    return 0;
}

void findallpairs(string s,vector<vector<int>>&opt,vector<pair<int,int>> &pairs,queue<pair<int,int>> &pair){
    ///
    /// findoptimaldp() returns maximum number of pairs possible for a sequence. This function returns all those pairs which are being formed in this sequence.
    /// The findallpairs function is used to find all the matching pairs in the string that create loops in the most optimal approach
    /// to create the secondary RNA structure .
    /// The result of the findoptimaldp function is used to find all the matching optimal loops by backtracking the opt vector which stores
    /// maximum number of base_pairs between any two indices.
    ///

    int n=s.size();
    
    map< char,int> m;
    m['A'] = -1;
    m['U'] = 1;
    m['C'] = -2;
    m['G'] = 2;

    
    pair.push({0,n-1});
    while(!pair.empty())
    {
        int p= pair.front().first;
        int q= pair.front().second;
        pair.pop();
        ///
        ///If the optimal solution value at opt[p][q] is 0, it means there are no valid substrings within this pair, so it continues to the next pair.
        ///
        if(opt[p][q] == 0)
        {
            continue;
        }
        
        ///
        /// If the optimal solution value at opt[p][q] is equal to the optimal solution value of the substring opt[p][q-1],
        /// so it pushes the pair (p, q-1) back into the queue for checking optimal pairs in (p,q-1)
        ///
        else if( opt[p][q] == opt[p][q-1])
        {
            pair.push({p,q-1});
        }
        else
        {
            int flag = 0;
            ///
            /// We iterate through possible split points 't' within the substring(p,q-4).
            /// For each split point 't',whether it creates a matching pair with q.
            /// we check if adding this split point would contribute to the optimal solution in (p,q-4).
            /// If yes, we updates the pairs vector with the new pair (t, q).
            ///
            for(int t=p; t<q-4; t++)
            {
                if(m[s[t]]+ m[s[q]] == 0)
                {
                    if(t==p)
                    {
                        if(opt[p][q] == opt[t+1][q-1] + 1)
                        {
                            pairs.push_back({t, q});
                            pair.push({t+1, q-1});
                            flag=1;
                            break;
                        }
                    }
                    else if(t== q-5)
                    {
                        if(opt[p][q] == opt[p][t-1] +1)
                        {
                            pairs.push_back({t,q});
                            pair.push({p,t-1});
                            flag=1;
                            break;
                        }
                    }
                    else
                    {
                        if(opt[p][q] == opt[p][t-1] + opt[t+1][q-1] +1)
                        {
                            pairs.push_back({t,q});
                            pair.push({p,t-1});
                            pair.push({t+1,q-1});
                            flag=1;
                            break;
                        }
                    }
                }
            }
            if(!flag)
            {
                pair.push({p,q-1});
            }
        }
    }
}

signed main()
{
   
    // Read input from the file into a string

    /// Take string input the rna sequence
    string s;
    cin>>s;

    int n = s.length();

    vector<vector<int>> opt(n,vector<int>(n,0));
    vector<pair<int,int>> pairs;
    queue<pair<int,int>> pair;
    
    
    /// call the function findoptimaldp()
    /// call the function findallpairs()
    findoptimaldp(s,opt);
    
    findallpairs(s,opt,pairs,pair);

    cout<<"Maximum number of base-pairs are : "<<opt[0][n-1]<<endl;
    
    set<int>open;
    set<int>close;
    
    for(auto p:pairs){
        open.insert(p.first);
        close.insert(p.second);
    }
    
    string bracketstr;
    for(int i=0;i<s.size();i++){
        if(open.find(i)!=open.end()){
            bracketstr.push_back('(');
        }
        else if(close.find(i)!=close.end()){
            bracketstr.push_back(')');
        }
        else
            bracketstr.push_back('.');
    }
    
    //char command[1000];
    // sprintf(command, "java -cp VARNAv3-93.jar fr.orsay.lri.varna.applications.VARNAcmd -sequenceDBN %s -structureDBN \"%s\" -o rna_structure_4.jpg -algorithm naview", s.c_str(), bracketstr.c_str());
    // int result = system(command);

    char command[1000];
    sprintf(command, "java -cp VARNAv3-93.jar fr.orsay.lri.varna.applications.VARNAcmd -sequenceDBN %s -structureDBN \"%s\" -o rna_structure_5.png -algorithm naview", s.c_str(), bracketstr.c_str());
    int result = system(command);

    cout<<pairs.size()<<endl;
    int ct=1;
    for ( auto p: pairs)
    {
        cout<<"pair :"<<" "<<ct<<" "<<endl;
        cout<<p.first+1<<" "<<p.second+1<<endl;
        cout<<s[p.first]<<"--"<<s[p.second]<<endl;   
        cout<<endl;
        ct++;
    }
    
    cout<<bracketstr<<endl;
    return 0;
}