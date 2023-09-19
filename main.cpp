// Created by Muaaz Abed. Returns calculated integrals of integrals found in "calculator_input.txt" file.
// Use numbers before and after pipe for definite integrals.

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <cmath>
#include <sstream>

#include "Term.h"
#include "Node.h"
#include "BinTree.h"

using namespace std;

//Prototypes
double intCalc(int, int, int, int);

int main()
{
    try
    {
        //Gets input from cin
        cout << "Calculator Output:" << endl;
        string input = "calculator_input.txt";
        ifstream file;
        file.open(input);
        //Tests if file opened correctly
        if(file)
        {
            //BinTree<Term> tree;
            int num, denom, exp, pos, termNum, lower, upper, trig;
            double upSum, downSum, integral;
            string iter;
            //Iterates through lines of text file
            for (string line; getline(file, line);)
            {
                BinTree<Term> tree;
                pos = -2;
                num = 1;
                denom = 1;
                exp = 0;
                iter = "";
                termNum = 0;
                trig = -1;
                lower=-99;
                upper=-99;
                upSum=0;
                downSum=0;
                
                //States for pos variable:
                //-2: Looking for lower limit
                //-1: Looking for upper limit
                
                //0: Looking for numerator
                //1: Looking for denominator
                //2: Looking for exponent
                
                //5: Looking for trig param
                
                //trig: 0 = sine
                //trig: 1 = cosine
                
                //Iterates through line of file char by char
                for (int i = 0; i < int(line.length()); ++i)
                {
                    char letter = line.at(i);
                    //-2: Looking for lower limit
                    if(pos==-2)
                    {
                        if(letter=='|' && i==0)
                            pos=0;
                        else if(isdigit(letter) || letter == '-')
                            iter+=letter;
                        else if(letter=='|')
                        {
                            stringstream read(iter);
                            read >> lower;
                            pos=-1;
                            iter = "";
                        }
                    }
                    //-1: Looking for upper limit
                    else if(pos==-1)
                    {
                        if(isdigit(letter) || letter == '-')
                            iter+=letter;
                        else if(isspace(letter))
                        {
                            stringstream read(iter);
                            read >> upper;
                            pos=0;
                            iter = "";
                            continue;
                        }
                    }
                    //0: Looking for numerator
                    if(pos==0)
                    {
                        if((letter == '-' || letter == 'd') && iter != "")
                        {
                            stringstream read(iter);
                            read >> num;
                            Term data = Term(num,denom,exp,termNum,trig);
                            tree.insert(data);
                            termNum++;
                            if(lower!=-99)
                            {
                                downSum += intCalc(num, denom, exp, lower);
                                upSum += intCalc(num, denom, exp, upper);
                            }
                            iter = "-";
                            num=1;
                        }
                        else if(isdigit(letter) || letter == '-')
                            iter+=letter;
                        else if(letter=='/')
                        {
                            if(iter == "-" || iter == "")
                                iter+="1";
                            stringstream read(iter);
                            read >> num;
                            pos=1;
                            iter = "";
                        }
                        else if(letter=='x')
                        {
                            if(iter == "-" || iter == "")
                                iter+="1";
                            stringstream read(iter);
                            read >> num;
                            pos=2;
                            exp=1;
                            iter = "";
                        }
                        else if(letter=='s')
                        {
                            if(iter == "-" || iter == "")
                                iter+="1";
                            stringstream read(iter);
                            read >> num;
                            pos=5;
                            exp=1;
                            i+=3;
                            trig=0;
                            iter = "";
                        }
                        else if(letter=='c')
                        {
                            if(iter == "-" || iter == "")
                                iter+="1";
                            stringstream read(iter);
                            read >> num;
                            pos=5;
                            exp=1;
                            i+=3;
                            trig=1;
                            iter = "";
                        }
                        else if(isspace(letter) && iter.size()>0 && iter.at(0)!='-')
                        {
                            if(iter == "-" || iter == "")
                                iter+="1";
                            stringstream read(iter);
                            read >> num;
                            Term data = Term(num,denom,exp,termNum,trig);
                            tree.insert(data);
                            termNum++;
                            if(lower!=-99)
                            {
                                downSum += intCalc(num, denom, exp, lower);
                                upSum += intCalc(num, denom, exp, upper);
                            }
                            iter = "";
                            num=1;
                        }
                    }
                    //1: Looking for denominator
                    else if(pos==1)
                    {
                        if(isdigit(letter))
                            iter+=letter;
                        else if(letter=='s')
                        {
                            if(iter == "-" || iter == "")
                                iter+="1";
                            stringstream read(iter);
                            read >> denom;
                            pos=5;
                            exp=1;
                            i+=3;
                            trig=0;
                            iter = "";
                        }
                        else if(letter=='c')
                        {
                            if(iter == "-" || iter == "")
                                iter+="1";
                            stringstream read(iter);
                            read >> denom;
                            pos=5;
                            exp=1;
                            i+=3;
                            trig=1;
                            iter = "";
                        }
                        else if(letter=='x')
                        {
                            stringstream read(iter);
                            read >> denom;
                            pos=2;
                            exp=1;
                            iter = "";
                        }
                    }
                    //2: Looking for exponent
                    else if(pos==2)
                    {
                        if(letter == '-' && iter != "")
                        {
                            stringstream read(iter);
                            read >> exp;
                            if(exp==0)
                                exp=1;
                            pos=0;
                            Term data = Term(num,denom,exp,termNum,trig);
                            tree.insert(data);
                            termNum++;
                            if(lower!=-99)
                            {
                                downSum += intCalc(num, denom, exp, lower);
                                upSum += intCalc(num, denom, exp, upper);
                            }
                            iter = "-";
                            num=1;
                            denom=1;
                            exp=0;
                        }
                        else if((line.at(i-1) != '^') && letter == '-')
                        {
                            pos=0;
                            Term data = Term(num,denom,exp,termNum,trig);
                            tree.insert(data);
                            termNum++;
                            if(lower!=-99)
                            {
                                downSum += intCalc(num, denom, exp, lower);
                                upSum += intCalc(num, denom, exp, upper);
                            }
                            iter = "-";
                            num=1;
                            denom=1;
                            exp=0;
                        }
                        else if(isdigit(letter) || letter == '-')
                            iter+=letter;
                        else if(isspace(letter) || letter=='+')
                        {
                            stringstream read(iter);
                            read >> exp;
                            if(exp==0)
                                exp=1;
                            pos=0;
                            Term data = Term(num,denom,exp,termNum,trig);
                            tree.insert(data);
                            termNum++;
                            if(lower!=-99)
                            {
                                downSum += intCalc(num, denom, exp, lower);
                                upSum += intCalc(num, denom, exp, upper);
                            }
                            iter =  "";
                            num=1;
                            denom=1;
                            exp=0;
                        }
                    }
                    //5: Looking for trig param
                    else if(pos==5)
                    {
                        if(isdigit(letter))
                            iter+=letter;
                        if(letter == 'x')
                        {
                            stringstream read(iter);
                            read >> exp;
                            Term data = Term(num,denom,exp,termNum,trig);
                            tree.insert(data);
                            termNum++;
                            if(lower!=-99)
                            {
                                downSum += intCalc(num, denom, exp, lower);
                                upSum += intCalc(num, denom, exp, upper);
                            }
                            
                            iter = "";
                            num=1;
                            denom=1;
                            exp=0;
                            pos=0;
                            trig=-1;
                        }
                    }
                }
                //Prints and formats integral
                tree.print();
                if(downSum != 0)
                {
                    integral = upSum - downSum;
                    cout << ", " << lower << "|" << upper << " = ";
                    printf("%.3f",integral);
                    cout << endl;
                }
                else
                    cout << " + C" << endl;
                //cout << lower << "|" << upper << endl;
            }
        }
        file.close();
    }
    catch (const std::exception &e)
    {
        std::cout << "Catched";
        std::cerr << e.what() << '\n';
    }
}

//Calculates definite integral for term
double intCalc(int numer, int denom, int exp, int x)
{
    return ((numer * pow(x,exp+1))/ (denom*(exp+1)) + 0.0);
}

