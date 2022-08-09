#include<iostream>
int n, x[16], ap[16], size=0, vec[16];
void getVal(int k)
{
    for(int index=1; index<=size; ++index)
    {
        if(ap[vec[index]]==0 and vec[index]>x[k])
        {
            if(x[k]>-1)
                ap[x[k]]=0;
            x[k]=vec[index];
            ap[vec[index]]=1;
            return;
        }
    }
    if(x[k]>-1)
        ap[x[k]]=0;
    x[k]=-1;
}
void back(int k)
{
    if(k==0)
    {
        return;
    }
    getVal(k);
    if(x[k]==-1)
        back(k-1);
    else if(k<size)
        back(k+1);
    else if(k==size)
    {
        int nr=2;
        for(int index=1; index<size; ++index)
        {
            std::cout<<x[index]<<" "<<nr<<" ";
            nr+=2;
        }
        if(n%2==0)
        {
            std::cout<<x[size]<<" ";
            std::cout<<nr;
        }
        else
            std::cout<<x[size];
        std::cout<<'\n';
        ap[x[k]]=0;
        x[k]=-1;
        back(k-1);
    }
}
int main()
{
    std::cin>>n;
    for(int index=1; index<=n; ++index)
    {
        if(index%2==1)
        {
            ++size;
            vec[size]=index;
            x[size]=-2;
        }
    }
    back(1);
    return 0;
}
