#include<iostream>
#include<cstdlib>
#include<fstream>
#include<vector>
#include<cstring>
using namespace std;

int find(char**,int&,int,int);
void check(int);
int main()
{
    fstream file("area.txt", ios::in);
    int x,y;
    file >> x >> y;
    cout << x << " " << y << endl;
    char** arr = new char*[y];
    for(int i = 0; i < y; i++)
        arr[i] = new char[x];
    
    file.get();
    for(int i = 0; i < y; i++)
    {
        file.flush();
       // cout << i << endl;
        //file.getline(arr[i],x);
        file >> arr[i];
        //file.get();
       /// cout << arr[i] << endl;

    }
    vector<int> objs;
    int area = 0;
    for(int i = 0; i < y; i++)
    {
        for (int j = 0; j < x; j++)
        {
            if (arr[i][j] == '1')
            {
                area++;
                objs.push_back(find(arr,area,i,j));
                cout << "---------------"<< endl; 
                cout << objs.size() << " " << objs.back() << endl; 
                check(objs.back());
                 cout << "---------------"<< endl;
                area=0;
            }
        }
    }
    return 0;
    

}

int find(char** arr, int &area, int y,  int x)
{
    arr[y][x] = '*';
   //cout << y <<","<< x << endl;
    if(x+1<64)//strlen(arr[0]))
    {
        if(arr[y][x+1] == '1')
        {
            area++;
            find(arr,area,y,x+1);
        }
    }
   if(y+1<64)//strlen(arr))
   {
        if(arr[y+1][x] == '1')
        {
            area++;
            find(arr,area,y+1,x);
        }
   }
   if(x-1 >= 0)
   {
        if(arr[y][x-1] == '1')
        {
            area++;
            find(arr,area,y,x-1);
        }
   }
   
   if(y-1 >= 0)
    {
        if(arr[y-1][x] == '1')
        {
            area++;
            find(arr,area,y-1,x);
        }
   }
   return area;
}

void check(int size)
{
    if(size < 2)
    {
        cout << "Trash" << endl;
        return;
    }
    if(size < 5)
    {
        cout << "Object" << endl;
        return;
    }
    if(size >= 5)
    {
        cout << "Land" << endl;
        return;
    }
}
