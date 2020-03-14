#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <array>
#include <queue>
#include <algorithm>


using namespace std;

class snakes{



};

struct oldTracker
{
    int old = -1;
    vector<int> ladderOptions;
    bool isSnake;
};
struct queueEntry 
{ 
    int v;     
    int dist; 
    vector<int> options;  
}; 



int getMinDiceThrows(oldTracker move[], int N) 
{ 
    int parent[N];
    bool *visited = new bool[N]; 

    for (int i = 0; i < N; i++){
        visited[i] = false;
        parent[i] = -1; 
    }

    queue<queueEntry> q; 
     
    visited[0] = true; 
    queueEntry s = {0, 0};  
    q.push(s);  
  
    queueEntry qe; 
    while (!q.empty()) 
    { 
        qe = q.front(); 
        int v = qe.v; 

        if (v == N-1)
            break; 
  
        q.pop(); 
        for (int j=v+6; j >=(v+1); --j) 
        { 
        
            if (!visited[j] && j < N) 
            { 

                queueEntry a; 
                a.dist = (qe.dist + 1); 
                visited[j] = true;
                parent[j] = v; 
                a.options = qe.options;
                a.options.push_back(qe.v);
  
                if (move[j].old != -1) 
                    a.v = move[j].ladderOptions[0]; 
                else
                    a.v = j; 
                q.push(a); 
            } 
        } 
    } 

    cout<<qe.dist;
    cout<<"\n";
    
   int k = N-1; 
   vector<int> printPath;
   printPath.push_back(N-1);
  
   while(parent[k] != -1){
       printPath.insert(printPath.begin(),parent[k]);
       k = parent[k];

   }
     /*
    for(int i=0; i < N;i++){
       cout<<parent[i];
       cout<<" ";
   }
   
    
    for(int i=0; i < printPath.size(); i++){
        int res = printPath[i]+1;
        cout<<res;
        cout<<" ";
    }
   */
    qe.options.push_back(N-1);
  for(int i=0; i < qe.options.size();i++){
      cout<<qe.options[i]+1;
      cout<<" ";
  }
    cout<<"\n";
     
  
    return qe.dist; 
}

void bfs(vector<int> temp1, vector<int> tempLadder, vector<int> tempSnakes){

    int boardSize = temp1[0] * temp1[0];
    int numOfLadders = temp1[1];
    int numOfSnakes = temp1[2];

    int moves[boardSize];
    oldTracker movesTwo[boardSize];
   
    for(int i =0;i < boardSize; i++){
        moves[i] = -1;
       
    }

    for(int i=0; i < tempLadder.size(); i = i+2){
        moves[tempLadder[i]-1] = tempLadder[i+1] -1;
        movesTwo[tempLadder[i]-1].old = tempLadder[i]-1;
        movesTwo[tempLadder[i]-1].ladderOptions.push_back(tempLadder[i+1]-1);
        movesTwo[tempLadder[i]-1].isSnake = false;

    }

    for(int i=0; i < tempSnakes.size(); i = i+2){
        moves[tempSnakes[i]-1] = tempSnakes[i+1]-1;
        movesTwo[tempSnakes[i]-1].old = tempSnakes[i]-1;
        movesTwo[tempSnakes[i]-1].ladderOptions.push_back(tempSnakes[i+1]-1);
        movesTwo[tempSnakes[i]-1].isSnake = true;        
    } 

/*
    for(int i=0;i<boardSize;i++){
        cout<<moves[i];
        cout<<" ";
    }   
*/
    int result = getMinDiceThrows(movesTwo, boardSize);
      //cout<<result;
   

}

void parseCommand(string a){
    
    snakes s;
    //vector<string> inputVec = StringToLines(a);
    std::vector<std::string> inputVec;
    std::string temp;
    int markbegin = 0;
    int markend = 0;

    a += "\n";
    for (int i = 0; i < a.length(); i++) {     
        if (a[i] == '\n') {
            markend = i;
            inputVec.push_back(a.substr(markbegin, markend - markbegin));
            markbegin = (i + 1);
        }
    }
    
    int numOfGames = stoi(inputVec[0]);
    
   
    for(int i =1; i <= 3*numOfGames; i = i+3){
        stringstream ss(inputVec[i]);
        stringstream ssLadders(inputVec[i+1]);
        stringstream ssSnakes(inputVec[i+2]);
        string word;
        vector<int> temp1;
        vector<int> tempLadders;
        vector<int> tempSnakes;

      
        while(ss >> word){
            temp1.push_back(stoi(word));
        }

        while( ssLadders >> word){
            tempLadders.push_back(stoi(word));
        }

        while( ssSnakes >> word){
            tempSnakes.push_back(stoi(word));
        }
        cout<<"Board Game #1: ";
        cout<<"\n";
        bfs(temp1, tempLadders, tempSnakes);

        temp1.clear();
        tempLadders.clear();
        tempSnakes.clear();
    }

   



}

int main(int argv, char** argc) {

        if( argv != 2)  {
            return 1;
        }

        parseCommand(argc[1]);
         
    return 0; 
}