#include<fstream>
using namespace std;
ifstream fin("cruce.in");
ofstream fout("cruce.out");
long long columnSum[501]={0};
long long lineSum[501]={0};
void read(int &n, int &k, int matrix[501][501])
{
    fin>>n>>k;
    for(int index=1; index<=n; ++index)
    {
        for(int next=1; next<=n; ++next)
        {
            fin>>matrix[index][next];
            lineSum[index]+=matrix[index][next];
            columnSum[next]+=matrix[index][next];
        }
    }
}



void solveTask2(int k, int n, int matrix[501][501])
{
    int colIndex = 0, lineIndex = 0;
    long long currentSum=0;
    long long globalSum=0;
    //solving for the lines first
    int current_start=1, current_end=k;
    

    currentSum=lineSum[1]+lineSum[k];
    while(current_end<=n)
    {
        if(currentSum>globalSum)
        {
            globalSum=currentSum;
            lineIndex=current_start;
        }
        current_end++;
        current_start++;
        currentSum+=lineSum[current_end];
        currentSum-=lineSum[current_start-1];
    }
    

    //solving then for the collumns
    current_end=k;
    current_start=1;
    currentSum=0;
    globalSum=0;
    currentSum=columnSum[1]+columnSum[k];
    while(current_end<=n)
    {
        if(currentSum>globalSum)
        {
            globalSum=currentSum;
            colIndex=current_start;
        }
        current_end++;
        current_start++;
        currentSum+=columnSum[current_end];
        currentSum-=columnSum[current_start-1];
    }
    ///
    ///
    //
    //
    //
    //
    //
    //
    long long bigSum=0;
    for(int index=lineIndex; index<lineIndex+k; ++index)
    {
        bigSum+=lineSum[index];
    }
    for(int index=colIndex; index<colIndex+k; ++index)
    {
        bigSum+=columnSum[index];
    }
    for(int index=lineIndex; index<lineIndex+k; ++index)
    {
        for(int next=colIndex; next<colIndex+k; ++next)
        {
            bigSum-=matrix[index][next];
        }
    }
    fout<<bigSum<<" ";
    fout<<lineIndex<<" "<<colIndex<<'\n';
}
int main()
{
    int n, k, matrix[501][501];
    read(n, k, matrix);
    solveTask2(k, n, matrix);
    fin.close();
    fout.close();
    return 0;
}
