#include<fstream>
std::ifstream fin("input.txt");
std::ofstream fout("output.txt");
struct cards
{
    int32_t value;
    char type;
};
void solve(cards initial)
{
    cards current[9], min;
    min.value=10;
    char semicolon;
    bool ok=false, case1=false, case2=false;
    for(int32_t index=0; index<5; ++index)
    {
        fin>>current[index].value>>semicolon;
        fin>>current[index].type;
        if(current[index].type==initial.type)
        {
            ok=true;
            if(current[index].value>initial.value)
            {
                case2=true;
            }
        }
    }
    if(case2==false && ok==true)
    {
        case1=true;
    }
    if(ok==false)
    {
        fout<<"NONE"<<'\n';
    }
    else
    {
        if(case1==true)
        {
            for(int index=0; index<5; ++index)
            {
                if(current[index].value<min.value && current[index].type==initial.type)
                    min=current[index];
            }
            fout<<min.value<<" "<<min.type<<'\n';
        }
        else
        {
            for(int index=0; index<5; ++index)
            {
                if(current[index].value<min.value && current[index].value>initial.value)
                {
                    if(current[index].type==initial.type)
                        min=current[index];
                }
            }
            fout<<min.value<<" "<<min.type<<'\n';
        }
    }
}
int main()
{
    cards initial;
    char semicolon;
    for(int32_t index=0; index<1; ++index)
    {
        fin>>initial.value>>semicolon>>initial.type;
        fout<<index+1<<". ";
        solve(initial);
    }
    fin.close();
    fout.close();
    return 0;
}
