#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <array>
#include <queue>
#include <algorithm>


using namespace std;


class queueEntry 
{ 
    public:
        queueEntry(){
            int oldEntry = -1;
            int nextEntry = -1;
            bool visited = false;
            int ladderIndex = -1;
            int snakeIndex = -1;
            bool tookSnake = false;
            bool tookLadder = false;
        }
        
    
        int oldEntry;
        int nextEntry; 
        bool visited;
        int ladderIndex;
        int snakeIndex;
        bool tookSnake;
        bool tookLadder;
        vector<queueEntry> prevVertex;
}; 

void printPath(queueEntry& qe){

    queueEntry temp = qe;
    string output;
    vector<string> out;
    int repeatCheck;
    while(temp.prevVertex.size() != 0){
       if(temp.oldEntry != temp.nextEntry && temp.tookLadder){
           string s;
            repeatCheck = temp.oldEntry;
           s+= to_string(temp.oldEntry);
           s+= "+";
           s+= to_string(temp.nextEntry);
            s+= " ";
            out.insert(out.begin(), s);
       }
       else if(temp.oldEntry != temp.nextEntry && temp.tookSnake){
           string s;
           repeatCheck = temp.oldEntry;
           s+= to_string(temp.oldEntry);
           s+= "-";
           s+= to_string(temp.nextEntry);
           s+= " ";
           out.insert(out.begin(), s); 
       }   
       else{

        
           string s;
           if(repeatCheck != temp.nextEntry){
                s+= to_string(temp.nextEntry);
                s+= " ";
                out.insert(out.begin(), s);
           }
           repeatCheck = -1;
        
       } 

       temp = temp.prevVertex.at(0); 
    }
        cout<<out.size();
        cout<<"\n";
        out.insert(out.begin(), "1 ");
        out[out.size()-1].substr(0, out[out.size()-1].size() -1);
     for(int i =0; i < out.size(); i++){
           cout<<out[i];
       }
       
      

}

void getMinDiceThrows(queueEntry move[], int N) 
{ 
    
    queue<queueEntry> q; 
     
    move[1].visited = true;
    
    queueEntry s = move[1];
    q.push(s);  
   
    queueEntry qe; 
    while (!q.empty()) 
    { 
        qe = q.front(); 
        int v = qe.nextEntry;

        if (v == N-1)
            break; 
  
        q.pop(); 
        
        if(move[v].snakeIndex != -1){
            queueEntry curr;
            

            curr.nextEntry = move[v].snakeIndex;
            curr.oldEntry = v;
            curr.tookSnake = true;
            curr.tookLadder = false;
            curr.prevVertex.push_back(qe);
            move[v].visited = true;
            //parent[v] = qe;
            q.push(curr);
        }
       
        else if(move[v].ladderIndex != -1){
            queueEntry curr;
            curr.nextEntry = move[v].ladderIndex;
            curr.oldEntry = v;
            curr.tookSnake = false;
            curr.tookLadder = true;
            curr.prevVertex.push_back(qe);
            move[v].visited = true;
           // parent[v] = qe;
            q.push(curr);

        }
         else{
            for (int j=v+6; j >=(v+1); --j) 
            { 
            
                if (j < N && !move[j].visited) 
                { 
                    queueEntry a;
                    move[j].visited = true;
                    
                        
                    
                        a.oldEntry = j;
                        a.nextEntry = j;
                        a.tookLadder = false;
                        a.tookSnake = false;
                        a.prevVertex.push_back(qe);
                        //parent[j] = qe; 
                        
                        q.push(a); 
                    
                } 
            } 
         }
       
    }   
    
    printPath(qe);
    
}



void bfs(vector<int> temp1, vector<int> tempLadder, vector<int> tempSnakes){

    int boardSize = temp1[0] * temp1[0]+1;
    //int numOfLadders = temp1[1];
    //int numOfSnakes = temp1[2];

    queueEntry moves[boardSize];


    for(int i =1;i< boardSize; i++){
            moves[i].oldEntry = -1;
            moves[i].nextEntry = -1;
            moves[i].visited = false;
            moves[i].ladderIndex = -1;
            moves[i].snakeIndex = -1;
            moves[i].tookSnake = false;
            moves[i].tookLadder = false;
    }

        moves[1].oldEntry = 1;
        moves[1].nextEntry = 1;
    for(int i=0; i < tempLadder.size(); i = i+2){
       moves[tempLadder[i]].oldEntry = tempLadder[i];
       moves[tempLadder[i]].ladderIndex = tempLadder[i+1];

    }

    for(int i=0; i < tempSnakes.size(); i = i+2){
        moves[tempSnakes[i]].oldEntry = tempSnakes[i];
        moves[tempSnakes[i]].snakeIndex = tempSnakes[i+1];     
    } 

    //  for(int i =1;i< boardSize; i++){
    //      cout<<moves[i].oldEntry;
    //      cout<<" ";
    //  }

    getMinDiceThrows(moves, boardSize);
      //cout<<result;
   

}

void parseCommand(string a){
    

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
        cout<<"Board Game #1:";
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