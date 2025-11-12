#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main()
{
char rem[50],a[50],s[50],c,msj[50],gen[30];
int i,genlen,t,j,flag=0,k,n;
printf("enter the generation\n");
gets(gen);
printf("generator polynomial is crc :CCITT:%s\n",gen);
genlen=strlen(gen);
k=genlen -1;
printf("enter the message\n");
n=0;
while((c=getchar())!='\n')
{
msj[n]=c;
n++;
}
msj[n]='\0';
for(i=0;i<n;i++)
a[i]=msj[i];
for(i=0;i<k;i++)
a[n+i]='0';
a[n+k]='\0';
printf("\n message polynomial appended witrh zero \n");
puts(a);
for(i=0;i<n;i++)
{
if(a[i]=='1')
{
t=i;
for(j=0;j<=k;j++)
{
if(a[t]==gen[j])
a[t]='0';
else
a[t]='1';
t++;
}
}
}
for(i=0;i<k;i++)
rem[i]=a[n+i];
rem[k]='\0';
printf("the checksum appended \n");
puts(rem);
printf("\n the message with checksum appended\n");
for(i=0;i<n;i++)
a[i]=msj[i];
for(i=0;i<k;i++)
a[n+i]=rem[i];
a[n+k]='\0';
puts(a);
n=0;
printf("enter the received messgae\n");
while((c=getchar())!='\n')
{
s[n]=c;
n++;
}
s[n]='\0';
for(i=0;i<n;i++)
{
if(s[i]=='1')
{
t=i;
for(j=0;j<=k;j++,t++)
{
if(s[t]==gen[j])
s[t]='0';
else
s[t]='1';
}
}
}
for(i=0;i<k;i++)
rem[i]=s[n+i];
rem[k]='\0';
for(i=0;i<k;i++)
{
if(rem[i]=='1')
flag=1;
}
if(flag==0)
printf("received polynomial is errorfree\n");
else
printf(" received polynomial is error\n");
return 0;
}
