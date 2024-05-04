#include<iostream>
using namespace std;

class Node{
    public:
        int value,row,col;
        Node(){
            value = row = col = -1;
        }
};

class Astar{
    public:
        int goalmat[3][3];
        int startmat[3][3];
        int intrmat[3][3];
        int prevmove;
        Node goalarr[9];

        void setStartmat();
        void displaymat(int mat[3][3]);
        int calDistance(int mat[3][3]);
        int checkMoveandDist(int x,int y);
        void makeMove(int x,int y);
        void nextItr();
        Astar(){
            //Initialize goal mat and arr
            int gnum = 1;
            for(int i = 0;i<3;i++){
                for(int j = 0;j<3;j++){
                    goalmat[i][j] = gnum;
                    goalarr[gnum - 1].value = gnum;
                    goalarr[gnum - 1].row = i;
                    goalarr[gnum - 1].col = j;                     
                    gnum++;
                }
            }
            goalmat[2][2] = -1;
            goalarr[8].value = -1;
            prevmove = -1;
        }
};

void Astar :: displaymat(int mat[3][3]){
    for(int i = 0;i<3;i++){
        for(int j = 0;j<3;j++){
            cout<<mat[i][j]<<"\t";
        }
        cout<<"\n";
    }
}

void Astar :: setStartmat(){
    cout<<"Enter the sequence of start matrix (for blank column enter -1) : \n";
    for(int i = 0;i<3;i++){
        for(int j = 0;j<3;j++){
            cin>>startmat[i][j];
            intrmat[i][j] = startmat[i][j];
        }
    }
}

int Astar :: calDistance(int mat[3][3]){
    int h = 0;
    for(int i = 0;i<3;i++){
        for(int j = 0;j<3;j++){
            // int tempdist = abs(i - goalarr[mat[i][j] - 1].row) + abs(j - goalarr[mat[i][j] - 1].col);
            // if(mat[i][j] == -1){
            //     // tempdist = abs(i - goalarr[8].row) + abs(j - goalarr[8].col); 
            //     // h += abs(i - goalarr[8].row) + abs(j - goalarr[8].col);
            //     // cout<<i<<" "<<j<<" "<<tempdist<<" "<<h<<endl;
            // } else {
            //     // tempdist = abs(i - goalarr[mat[i][j] - 1].row) + abs(j - goalarr[mat[i][j] - 1].col); 
            //     h += abs(i - goalarr[mat[i][j] - 1].row) + abs(j - goalarr[mat[i][j] - 1].col);
            //     // cout<<i<<" "<<j<<" "<<tempdist<<" "<<h<<endl;
            // }
            if(mat[i][j] != goalmat[i][j]){
                h += 1;
            }
        }
    }
    return h;
}

int Astar :: checkMoveandDist(int x,int y){
    int tempmat[3][3];
    int blank_x,blank_y;
    for(int i = 0;i<3;i++){
        for(int j = 0;j<3;j++){
            tempmat[i][j] = intrmat[i][j];
            if(intrmat[i][j] == -1){
                blank_x = i;
                blank_y = j;
            }
        }
    }

    if(blank_x + x < 0 || blank_x + x > 2){
        return -1;
    }
    if(blank_y + y < 0 || blank_y + y > 2){
        return -1;
    }

    int tempvar = tempmat[blank_x + x][blank_y + y];
    tempmat[blank_x + x][blank_y + y] = -1;
    tempmat[blank_x][blank_y] = tempvar;

    int dist = calDistance(tempmat);
    return dist;
}

void Astar :: makeMove(int x,int y){
    int blank_x,blank_y;
    for(int i = 0;i<3;i++){
        for(int j = 0;j<3;j++){
            if(intrmat[i][j] == -1){
                blank_x = i;
                blank_y = j;
            }
        }
    }
    if(blank_x + x < 0 || blank_x + x > 2){
        return;
    }
    if(blank_y + y < 0 || blank_y + y > 2){
        return;
    }

    int tempvar = intrmat[blank_x + x][blank_y + y];
    intrmat[blank_x + x][blank_y + y] = -1;
    intrmat[blank_x][blank_y] = tempvar;
}

void Astar :: nextItr(){
    int dist[4]; //l r t b
    dist[0] = checkMoveandDist(-1,0);
    dist[1] = checkMoveandDist(1,0);
    dist[2] = checkMoveandDist(0,-1);
    dist[3] = checkMoveandDist(0,1);
    // cout<<"Distances : ";
    // for(int i = 0;i<4;i++){
    //     cout<<dist[i]<<" ";
    // }
    // cout<<endl;
    if(prevmove != -1){
        switch (prevmove)
        {
        case 0:
            dist[1] = -1;
            break;
        case 1:
            dist[0] = -1;
            break;
        
        case 2:
            dist[3] = -1;
            break;
        case 3:
            dist[2] = -1;
            break;
        }
    }

    int smallest_itr;
    for(int i = 0;i<4;i++){
        if(dist[i] != -1){
            smallest_itr = i;
        }
    }

    for(int i = 0;i<4;i++){
        if(dist[i] != -1 && dist[i] < dist[smallest_itr]){
            smallest_itr = i;
        }
    }
    prevmove = smallest_itr;
    switch (smallest_itr)
    {
    case 0:
        makeMove(-1,0);
        break;
    case 1:
        makeMove(1,0);
        break;
    
    case 2:
        makeMove(0,-1);
        break;
    case 3:
        makeMove(0,1);
        break;
    }

    displaymat(intrmat);
}

int main(){
    Astar obj;
    obj.displaymat(obj.goalmat);
    obj.setStartmat();
    obj.displaymat(obj.intrmat);
    // cout<<obj.calDistance(obj.startmat)<<endl;
    // for(int i = 0;i<20;i++){
    //     cout<<"Itr "<<i+1<<endl;
    //     obj.nextItr();
    //     if(obj.calDistance(obj.intrmat) == 0){
    //         break;
    //     }
    // }
    int itr = 0;
    while(obj.calDistance(obj.intrmat) != 0){
        cout<<"Itr "<<itr+1<<endl;
        obj.nextItr();
        itr++;
    }

    return 0;
}