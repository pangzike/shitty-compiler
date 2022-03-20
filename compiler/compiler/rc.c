
int main()
{
    int missile[100005]={0};
    char a=0;
    int i,j,lenup=0,lendown=0;
    for(i=0;a!='\n';i++)
    {
        scanf("%d",&missile[i]);
        if(lendown==0)
            down[lendown++]=missile[i];
        else
        {
            if(down[lendown-1]>=missile[i])
            {
                down[lendown++]=missile[i];
            }
            else
            {
                j=searchdown(missile[i],lendown);
                down[j]=missile[i];
            }
            
        }
        if(lenup==0)
           up[lenup++]=missile[i];
        else
        {
            if(up[lenup-1]<missile[i])
            {
                up[lenup++]=missile[i];
            }
            else
            {
                j=searchup(missile[i],lenup);
                up[j]=missile[i];
            }
        }
        scanf("%c",&a);
    }
    printf("%d\n%d\n",lendown,lenup);
    return 0;
}
