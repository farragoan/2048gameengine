#ifndef DRIVERFILE_H
#define DRIVERFILE_H

#include<bits/stdc++.h>
using namespace std;

extern void operateVars(int i,int j,int li,int ri,int op);

extern bool checkValidTile(int i,int j);

extern bool checkValidName(string Name);

extern void addVars(int a[4][4],int i,int j,string s,int * e);

extern void printBoard(int state[4][4]);

extern int getValue(int a[4][4],int i,int j,int * err);

extern void setValue(int a[4][4],int i,int j,int *err,int val);

extern void addElement(int state[4][4]);

extern void initGrid(int state[4][4]);

extern void operate(int a[4][4],int li,int ri,int op);

extern void upmove(int a[4][4],int op);
 
extern void downmove(int a[4][4],int op);

extern void rightmove(int a[4][4],int op);

extern void leftmove(int a[4][4],int op);

extern void print_stderror(int state[4][4]);

extern void makemove(int state[4][4],int k,int o);

#endif