// Note: Enter -1 after you have been entered all the terms.
#include<iostream>
#include<fstream>
using namespace std;

int* findbinary(int length, int minterms) {
	int* binary = new int[length];
	for (int i = 0; i < length; i++) {
		binary[(length - 1) - i] = minterms % 2;
		minterms/=2;
	}
		return binary;
}
int checkones(int row, int length, int** table) {
	int countones = 0;
	for (int j = 0; j < length; j++) {
		if (table[row][j] == 1) {
			countones++;
		}
	}
	return countones;
}
void strcpy(int* oldarray, int* newarray, int col) {
	for (int i = 0; i < col; i++) {
		newarray[i] = oldarray[i];
	}
}
void regrow(int*& oldarray, int col, int value) {
	int* newarray = NULL;
	newarray = new int[col + 1];
	strcpy(oldarray, newarray, col);
	newarray[col] = value;
	delete[] oldarray;
	oldarray = newarray;
}
void compare(int size, int length, int** table,int**& pairs,int *minterms,int*&cols) {
	int check1 = 0, check2 = 0,*oldarray=NULL;
	cols = new int[size] {};
	pairs = new int* [size];
	for (int k = 0; k < size; k++) {
		check1 = checkones(k, length, table);
		for (int i = 0; i < size; i++) {
			check2 = checkones(i, length, table);
			if (check1 == check2 - 1) {          
				regrow(oldarray,cols[k],i);
				cols[k]++;
			}
			check2++;
		}
		pairs[k] = oldarray;
		oldarray = NULL;
		check1++;
	}
}
void strcpy(int* newarray,int*oldarray,int size,int value) {
	int l=0;
	for(int i=0; i<size; i++) {
		if(oldarray[i]!=value) {
			newarray[l]=oldarray[i];
			l++;
		}
	}
}
void shrink(int*&oldarray,int& size,int value) {
	int *newarray=NULL;
	newarray=new int[size-1];
	strcpy(newarray,oldarray,size,value);
	size--;
	delete[] oldarray;
	oldarray=newarray;
}
void requiredpairs(int size, int length, int** table,int** pairs,int *minterms,int *cols) {
	int count=0;
	for(int i=0; i<size; i++) {
		for(int j=0; j<cols[i]; j++) {
			for(int k=0; k<length; k++) {
				if(table[i][k]==table[pairs[i][j]][k]) {
					count++;
				}
			}
			if(!(count== length-1)) {

				shrink(pairs[i],cols[i],pairs[i][j]);//here pairs[i] will act as our old pointer, cols will act as our size,and pairs[i][j] will act as our value, we will find the index of that value and delete it.
				j--;//because when we remove an element in the middle, the next coming element will automatically come behind without any need of incrementing j so we should stop j from being j++ and should remain at the same position becasuse on shrinking all elements shits towards left, therefore we are doing j-- to cancel the effect of j++.	
			}
			count=0;
		}
	}
}
int findrows(int** pairs,int*cols,int size)
{
	int count=0;
	for(int i=0;i<size;i++)
	{
		for(int j=0;j<cols[i];j++)
		{
			count++;
		}
	}
	return count;
}
void eliminating(int size,int length,int** table,int** pairs,int* cols,int**&table1,int& size1)
{
	int l=0;//l is being used to increment values
	//count all pairs to get the  number of  rows which will be stored in size1 variable
	size1=findrows(pairs,cols,size);
	table1=new int*[size1];
	for(int i=0;i<size1;i++)
	{
		table1[i]=new int[length];
	}
	for(int i=0;i<size;i++)
	{
		for(int j=0;j<cols[i];j++)
		{
			for(int k=0;k<length;k++)
			{
				if(table[i][k]==table[pairs[i][j]][k])
				{
					table1[l][k]=table[pairs[i][j]][k];
				}
				else
					table1[l][k]=-1;
			}
			l++;
		}
	}
	
}
void method1(int*& implicants1,int& total1,int size,int* cols)
{
	 
	bool flag=false;
	for(int i=0;i<size;i++)
	{
		if(cols[i]==0)
		{
		
			flag=true;			
		}
		if(flag)
		{
		
			regrow(implicants1,total1,i);
			total1++;
		}	
		flag=false;
 	}
}
void method2(int*& implicants2,int& total2,int** pairs,int size,int* cols)
{

	bool flag=false;
	for(int k=0;k<size;k++)//k is to match all min terms have used or not.
	{
	 for(int i=0;i<size;i++)
		{
			for(int j=0;j<cols[i];j++)
			{
				if(k==pairs[i][j])
				{
			
					flag=true;
					break;
				}
				else
					flag=false;
			}
			if(flag)
			{
				break;
			}
		}
		if(!flag)
		{
			regrow(implicants2,total2,k);
			total2++;
		}
		flag=false;
	}
}
void common(int*& implicants,int* implicants1,int* implicants2,int& total,int total1,int total2)
{
	for(int i=0;i<total1;i++)
	{
		for(int j=0;j<total2;j++)
		{
			if(implicants1[i]==implicants2[j])//The equality no doubt is the result of XOR not of AND but the sense used to combine two function to get result is the intersection of two sets which is AND in propositional logic.
			{
				regrow(implicants,total,implicants1[i]);//or you may use regrow(implicants,total,implicants2[j]); becuase this value is common in both
				total++;
			}
		}
	}
}
void strcpy2d(int**oldarray,int**newarray,int rows,int cols) {
	for(int i=0; i<rows; i++) {
		newarray[i]=new int[cols];
		for(int j=0; j<cols; j++) {
			newarray[i][j]=oldarray[i][j];
		}
	}
}
void addnewcolumn(int** newarray,int*newcolumn,int rows,int cols) {
	newarray[rows]=new int[cols];
	for(int j=0; j<cols; j++) {
		newarray[rows][j]=	newcolumn[j];
	}
}
void regrow2d(int**&oldarray,int rows,int cols,int*newcolumn) {
	int**newarray;
	newarray=new int*[rows+1];
	strcpy2d(oldarray,newarray,rows,cols);
	addnewcolumn(newarray,	newcolumn,rows,cols);
	for(int i=0; i<rows; i++) {
		delete[] oldarray[i];
	}
	delete[] oldarray;
	oldarray=newarray;
}
void strcpyshrink(int** oldarray, int** newarray, int row, int column,int removerowindex)
{
	int l = 0;
	for (int i = 0;i < row;i++)
	{
		if (i != removerowindex) {
			newarray[l] = new int[column];
			for (int j = 0;j < column;j++)
			{
				newarray[l][j] = oldarray[i][j];
			}
			l++;
		}
	}
}
void shrink2d(int**& oldarray, int row, int column,int removerowindex)
{
	int** newarray=nullptr;
	newarray = new int*[row-1];
	strcpyshrink(oldarray, newarray, row, column,removerowindex);
	for (int i = 0;i < row;i++)
	{
		delete[]oldarray[i];
	}
	delete[]oldarray;
	oldarray = newarray;
}
void RemovingDuplication(int**& primeimplicants,int& row,int length)
{//the reason of using & with row and primeimplicants is that i'm shrinking and changing the allocation place to which the point is pointing.
	bool flag=false;
	int count=0;
	for(int k=0;k<row;k++)
	{
		for(int i=0;i<row;i++)
		{
			for(int j=0;j<length;j++)
			{
				if(primeimplicants[k][j]==primeimplicants[i][j])
				{
					flag=true;
				}
				else
				{
					flag=false;
					break;
				}
			}
			if(flag)
			{
				count++;
			}
				if(flag&&count>1)
			{
				shrink2d(primeimplicants, row, length,i);
				row--;
				i--;//becausenext row has been shifted in the place which is removed therefore we donot to increment this time
			}
		}
//OR		if(flag&&count>1) but above one is better, you may delete what is here in the comment
//			{
//				cout<<"implicants "<<k<<" are duplicates"<<endl;
//				shrink2d(primeimplicants, row, length,k);
//				row--;
//				k--;//becausenext row has been shifted in the place which is removed therefore we donot to increment this time
//			}
		count=0;
	}
}
void CheckingTermsUsed(int size,int length,int** table,int** pairs,int* cols,int**& primeimplicants,int& row)
{
	/*
	way 1
	-------------------------------------------------------------------------------------------------------------------------------------
	The following two steps will be taken place to check which term is,remaining and has not take part in any pair, or you may say, prime implicant
	Test data number of variables= 4, total minterms=8, minterms=1,3,4,5,10,12,13,15
	1- I will see for which row the col[i] is zero if it is zero
	   it may mean that this minterm or row number may have not taken place in any pairing.
	for example if i use the test data, then I see that by using first method I get the terms: 1,4,7, which implies 3,10,15 ,
	however actual result is 4 only, which implies 10. 
	2-  The min terms(0-size) will be compared with all terms in the pairs, if these terms matces with any of the term
	in "pairs" 2d array, it means they have come in pairs, and those terms which donot match with any terms in 2darray"pairs",
	it means that these are the our prime implicants and has not take part in any pairing. 
	for example. if i use the test data when i use 2nd method,then I see that by using second method I get the terms: 0,2,4, which implies 1,4,10. So, if 
	I use AND, I will get the result common in both which is term 4 or term 10. For more clarification you can see image with quine mccluskey
	way2
	Way 1 takes more variables
	---------------------------------------------------------------------------------------------------------------------------------------
	To get the actual result we can also use these two steps
	1- Pass(input) the result, acquired from step 1, to step 2. 
	2-The terms come from 1st method whould be compared with the terms in 2darray'pairs' those, which would match, will not remove from implicants and those,which will not match, will remain in impliant array. But the program will have to be changed for way 2
	because the first way is being used here in which boolean operation AND is used. But you can also use way2.
	Way 2 takes less variables
	------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	*/
	// i donot want to use the word "size" again because i have already used it for total no of given terms
	int *implicants1=nullptr,total1=0;
	int *implicants2=nullptr,total2=0;
	int *implicants=nullptr,total=0;//to store actual results
	method1(implicants1, total1,size,cols);
	method2(implicants2,total2,pairs,size,cols);
	common(implicants,implicants1,implicants2,total,total1,total2);//here intersection operation of set which is called AND, in boolen language, will be applied. The "implicant" array will store the common term in both "implicant1" and "implicant2" and "total" will store the actual no of terms not being used in any pairing
	for(int i=0;i<total;i++)
	{
		regrow2d(primeimplicants,row,length,table[implicants[i]]);
		row++;
	}
	RemovingDuplication(primeimplicants,row,length);
}
void delete2d(int **pointer,int rows)
{
	for(int i=0;i<rows;i++)
	{
		delete[]pointer[i];
	}
	delete[]pointer;
}
void copy(int** table1,int size1,int length,int**& table)
{
	table=new int*[size1];
	for(int i=0;i<size1;i++)
	{
		table[i]=new int[length];
		for(int j=0;j<length;j++)
		{
			table[i][j]=table1[i][j];
		}
	}
}
bool stopingloop(int size1)
{
	if(size1==0)
	{
		return false;
	}
	else 
		return true;
}
int** MintermsBinaryTable(int size,int length,int* minterms)
{
	int **table;
	table=new int*[size];
	for (int i = 0; i < size; i++) {
		table[i] = findbinary(length, minterms[i]);
	}
	return table;
}
void findingTermsCoveredByEactPrimeImplicant(int**& termscovering,int** primeimplicants,int row,int length,int** table,int MintermsTableRows,int*& columns)
{
	bool flag=false;
	for(int i=0;i<row;i++)
	{
		for(int j=0;j<MintermsTableRows;j++)
		{
			for(int k=0;k<length;k++)
			{
				if( (primeimplicants[i][k]==table[j][k]) || (primeimplicants[i][k]==-1) )
				{
					flag=true;
				}
				else
				{
					flag=false;
					break;
				}
			}
			if(flag)
			{
				regrow(termscovering[i],columns[i],j);//j is the term 0 to size, which relative actual terms number is stored in 'minterms' 1d array
				//termscovering[i] is refering to something garbage which you're going to send by call by reference and may not accept or swallow by the pointer in the dummy parameter of the defined function
				columns[i]++;
			}
		}
	}
	//displaying the terms corresponding to each prime Implicants
}
bool checkingduplicate(int* array,int lengthOfArray,int termscovering)
{
	bool flag;
	for(int i=0;i<lengthOfArray;i++)
	{
		if(array[i]!=termscovering)
		{
			flag=true;
		}
		else
		{
			flag=false;
			break;
		}
	}
	return flag;
}
void SeparatingEssentialfromNonEssentialPrimeImplicants(int**& primeimplicants,int& row,int length,int MintermsTableRows,int** termscovering,int* columns)
{
	int lengthOfArray=0,*arr=nullptr; //array should store without duplicates terms from 0 to so on
	bool flag=true;
	for(int i=0;i<row;i++)
	{
		flag=true;
		for(int j=0;j<row;j++)
		{ 
			if(i!=j)
			{
				for(int k=0;k<columns[j];k++)
				{		
					if(lengthOfArray!=0)
					{
						flag=checkingduplicate(arr,lengthOfArray,termscovering[j][k]);// this is to store each term without any duplicate
					}
					if(flag)
					{
						regrow(arr,lengthOfArray,termscovering[j][k]);
						lengthOfArray++;
					}
				}
				
			}
		}
		if(lengthOfArray==MintermsTableRows)
		{
			shrink2d(primeimplicants,row,length,i);
			row--;
			i--;
		}
		delete[] arr;
		arr=nullptr;
		lengthOfArray=0;
	}
}
void input_minterms(int& size, int*& minterms, int& length) {
	int num = 0;
	cout << "Enter the number of variables:";
	cin >> length;
	cout << "Press -1 to after have been input all minterms:" << endl;
	while (num != -1) {
		cout << "Enter Min No. " << size + 1 << ":";
		cin >> num;
		if (num != -1)
		{
			regrow(minterms, size, num);
			size++;
		}
	}
}
int main() {
	//length will store the number of variables. Size is the total number of minterms
	//table is storing binary. pairs variable is storing pairs. cols is the columns of 2d array pairs.
	// prime implicants are still storing all those terms which are unchecked.
	// row here are the number of rows for 2d array "primeimplicants", where 'length' is its number of columns
	//size1 is the number of rows for table1 storing immediate results like -1101 or 0-1-11, where 'length' is its number of columns
	int* minterms=NULL, ** table=NULL,MintermsTableRows=0,**pairs=NULL, size=0, length=0,*cols=NULL,**primeimplicants=nullptr,row=0,**table1=nullptr,size1=0;
	bool flag=1; //or bool flag=true;
	input_minterms(size, minterms, length);
	table=MintermsBinaryTable(size,length,minterms);
	MintermsTableRows=size;//the purpose of storing size in this varibable is that, we need it at last and till last size changes many time.
	/*
	The Queen McCluskey Method consits of two steps
	step 1 of Queen McCluskey Method
	Comparing terms and Determining Prime implicants
	*/
//-----------------------------------------------------------------------------------------	
	while(flag){
	compare(size, length, table,pairs,minterms,cols);
	requiredpairs(size, length, table,pairs,minterms,cols);
	//process
	eliminating(size, length, table,pairs,cols,table1,size1);// i am also making next level table in this function
	//copy
	CheckingTermsUsed(size, length,table,pairs,cols,primeimplicants,row);//checking whether all terms has come in used and finding which term is not stored to store its boolean expression for final expression
	flag=stopingloop(size1);//loop should stop when there is nothing more in first level table and it happens when size1=0,meaning no minterm have been marked, so no more group is made or will be made,nothing in first level table.Hence the loop should stop if x=1; loop should run, if x=0 loop should stop
	delete2d(table,size);
	table=nullptr;
	copy(table1,size1,length,table);
	delete2d(table1,size1);
	table1=nullptr;
	delete2d(pairs,size);
	size=size1;//because value in 'size' is needed to deallocate 'pairs' 
	size1=0;
	}
/*------------------------------------------------------------------------
Step2: Separating Essential Prime Implicants and Finishing Non Essential Prime Implicants 
---------------------------------------------------------------------------*/
//At the end of step 1, table1 has nothing which is copying to table so table will also has nothing but it will be refering a memory address given by table1 having size 0.By the way. table1 is referring to none and has size1=0, i may utilize it but i donot want to burden on memory and want to use table
	delete table;
	table=nullptr;
	int**termscovering=nullptr,* columns=nullptr;//the 1d array 'columns' will be used for storing total no. of minterms which can be different, becuase different prime implicant may cover different number of minterms
	termscovering=new int*[row];//In terms covering the terms will be stored corresponding to primeimplicants which are covered by each prime implicants
	for(int i=0;i<row;i++)
	{
		termscovering[i]=nullptr;
	}
	columns=new int[row]{};
	table=MintermsBinaryTable(MintermsTableRows,length,minterms);
	findingTermsCoveredByEactPrimeImplicant(termscovering,primeimplicants,row,length,table,MintermsTableRows,columns);
	SeparatingEssentialfromNonEssentialPrimeImplicants(primeimplicants,row,length,MintermsTableRows,termscovering,columns);//The idea used here is that those terms without which all minterms 0 to size get covered are our minterms.
	
//----------------------------------------------------------	

ofstream file;
	file.open("result.txt");
	if(file)
	{
	 cout<<"Final Expression"<<endl<<"= ";
	 for(int i=0;i<row;)
	 {
		for(int j=0;j<length;j++)
		{
			if(primeimplicants[i][j]!=-1)
			{
				cout<<"A"<<(length-1)-j;
				file<<"A"<<(length-1)-j;
			}
			if(primeimplicants[i][j]==0)
			{
				cout<<"'";
				file<<"'";
			}
		}
		i++;
		if(i<row){
		cout<<" + ";
		file<<" + ";
		}
	 }
	}
//------------------------------------------------------------------
}                         
                                   