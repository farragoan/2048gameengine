#include<bits/stdc++.h>
using namespace std;

vector<string> variableNames[4][4];

bool checkValidTile(int i,int j) {
	return i>=0&&j>=0&&i<4&&j<4;
}

bool checkValidName(string name) {
	for(int w=0;w<4;w++) 
	{
		for(int q=0;q<4;q++)
		{
			for(auto i:variableNames[w][q]) {
				if(name.compare(i)==0) {
					return false;
				}
			}
		}
	}
	return true;
}

void addVars(int a[4][4],int i,int j,string s,int *e) {
	if(checkValidName(s)) {
		if(checkValidTile(i,j)) {
			if(a[i][j]>0) {
				variableNames[i][j].push_back(s);
			}
			else {
				printf("Variables can only be assigned to nonzero tiles.\n");
			}
		}
		else {
			printf("Try again with a valid tile index");
            *e=1;
		}
	}
	else {
		printf("Try again with a unique variable name.\n");
        *e=1;
	}
}

int getValue(int a[4][4],int i,int j,int * err) {
	if(!checkValidTile(i,j)) {
		printf("Try again with valid tile.\n");
		*err=1;
		return -1;
	}
	return a[i][j];
}

void setValue(int a[4][4],int i,int j,int *err,int val) {
	if(val<0||!checkValidTile(i,j)) {
		if(val<0) {
			printf("Try again with a positive integral value.\n");
		}
		else {
			printf("The tile specified does not exist.\n");
		}
		*err=1;
	}
	a[i][j]=val;
	if(a[i][j]==0) {
		variableNames[i][j].clear();
	}
}

void operateVars(int i,int j,int li, int ri, int op) {
	if(op!=1)
	{
		for(auto i:variableNames[i][j]) {
			variableNames[li][ri].push_back(i);
		}
		variableNames[i][j].clear();
	}
	else if(op==1)
	{
		variableNames[li][ri].clear();
		variableNames[i][j].clear();
	}
}

void printBoard(int state[4][4]) {

    printf("_ _ _ _ _ _ _ _ _\n");

    for (int i = 0; i < 4; i++)
    {
        printf("| ");
        for (int j = 0; j < 4; j++)
        {
            if (state[i][j])
            {
                printf("%d ", state[i][j]);
            }
            else
            {
                printf("  ");
            }

            printf("| ");
        }
        printf("\n_ _ _ _ _ _ _ _ _\n");
    }

}

void addElement(int state[4][4]) {
    int k=rand()%100;
    int e;
    if(k<80) {
        e=2;
    }
    else {
        e=4;
    }
    int i,j;
    while(1) {
        i=rand()%4;
        j=rand()%4;
        //cout<<i<<" "<<j<<" ";
        if(state[i][j]==0) {
            state[i][j]=e;
            //cout<<state[i][j]<<" ";
            break;
        }
    }
}

void initGrid(int state[4][4]) {
    for(int i=0;i<4;i++) {
        for(int j=0;j<4;j++) {
            state[i][j]=0;
        }
    }
    addElement(state);
}

void operate(int a[4][4],int li,int ri,int op)
{
	if(op==0) //add
	{
		a[li][ri]*=2;
	}
	else if(op==1)	//subtract
	{
		a[li][ri]=0;
	}
	else if(op==3)	//divide
	{
		a[li][ri]=1;
	}
	else if(op==2)	//multiply
	{
		a[li][ri]*=a[li][ri];
	}
}

void upmove(int a[4][4], int op)
{
	int i,j,li,ri;
	for(j=0;j<4;j++)
	{
		li=0,ri=j;
		for(i=1;i<4;i++)
		{
			if(a[i][j]!=0)
			{
				if(a[i-1][j]==0 || a[i-1][j]==a[i][j])
				{
					if(a[li][ri]==a[i][j])
					{
						operate(a,li,ri,op);
						operateVars(i,j,li,ri,op);
						a[i][j]=0;
					}
					else
					{
						if(a[li][ri]==0)
						{
							a[li][ri]=a[i][j];
							a[i][j]=0;
						}
						else
						{
							a[++li][ri]=a[i][j];
							a[i][j]=0;
						}
					}
				}
				else li++;
			}
		}
	}
    addElement(a);
}

void downmove(int a[4][4], int op)
{
	int i,j,li,ri;
	for(j=0;j<4;j++)
	{
		li=3,ri=j;
		for(i=2;i>=0;i--)
		{
			if(a[i][j]!=0)
			{
				if(a[i+1][j]==0 || a[i+1][j]==a[i][j])
				{
					if(a[li][ri]==a[i][j])
					{
						operate(a,li,ri,op);
						operateVars(i,j,li,ri,op);
						a[i][j]=0;
					}
					else
					{
						if(a[li][ri]==0)
						{
							a[li][ri]=a[i][j];
							a[i][j]=0;
						}
						else
						{
							a[--li][ri]=a[i][j];
							a[i][j]=0;
						}
					}
				}
				else li--;
			}
		}
	}
    addElement(a);
}

void leftmove(int a[4][4], int op)
{
	int i,j,li,ri;
	for(i=0;i<4;i++)
	{
		li=i,ri=0;
		for(j=1;j<4;j++)
		{
			if(a[i][j]!=0)
			{
				if(a[i][j-1]==0 || a[i][j-1]==a[i][j])
				{
					if(a[li][ri]==a[i][j])
					{
						operate(a,li,ri,op);
						operateVars(i,j,li,ri,op);
						a[i][j]=0;
					}
					else
					{
						if(a[li][ri]==0)
						{
							a[li][ri]=a[i][j];
							a[i][j]=0;
						}
						else
						{
							a[li][++ri]=a[i][j];
							a[i][j]=0;
						}
					}
				}
				else ri++;
			}
		}
	}
    addElement(a);
}

void rightmove(int a[4][4], int op)
{
	int i,j,li,ri;
	for(i=0;i<4;i++)
	{
		li=i,ri=3;
		for(j=2;j>=0;j--)
		{
			if(a[i][j]!=0)
			{
				if(a[i][j+1]==0 || a[i][j+1]==a[i][j])
				{
					if(a[li][ri]==a[i][j])
					{
						operate(a,li,ri,op);
						operateVars(i,j,li,ri,op);
						a[i][j]=0;
					}
					else
					{
						if(a[li][ri]==0)
						{
							a[li][ri]=a[i][j];
							a[i][j]=0;
						}
						else
						{
							a[li][--ri]=a[i][j];
							a[i][j]=0;
						}
					}
				}
				else ri--;
			}
		}
	}
    addElement(a);
}

void print_stderror(int state[4][4])
{
	for(int i=0;i<4;i++) {
		for(int j=0;j<4;j++) {
			fprintf(stderr,"%d ",state[i][j]);
		}
	}
	for(int i=0;i<4;i++) {
		for(int j=0;j<4;j++) {
			if(variableNames[i][j].size()!=0) {
                cerr<<i+1<<","<<j+1<<variableNames[i][j][0];
				//fprintf(stderr,"%d,%d%s",i,j,variableNames[i][j]);
				if(variableNames[i][j].size()>1) {
					for(int io=1;io<variableNames[i][j].size();io++) {
                        cerr<<","<<variableNames[i][j][io];
						//fprintf(stderr,",%s",variableNames[i][j][io]);
				}
				fprintf(stderr," ");
				}
			}
		}
	}
    fprintf(stderr,"\n");
}

void makemove(int state[4][4],int k,int o) {

    if(k==0) {
        //cout<<"\nMOVING UP";
        upmove(state,o);
        //display(state.curr);
    }
    else if(k==1) {
        //cout<<"\nMOVING DOWN";
        downmove(state,o);
        //display(state.curr);
    }
    else if(k==2) {
        //cout<<"\nMOVING LEFT";
        leftmove(state,o);
        //display(state.curr);
    }
    else {
        //cout<<"\nMOVING RIGHT";
        rightmove(state,o);
        //display(state.curr);
    }
    addElement(state);
}