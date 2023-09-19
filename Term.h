// Created by Muaaz Abed.
// Polynomial terms class created for use with Node class. Can use in your project if credited.

#ifndef TERM_H
#define TERM_H

#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>

using namespace std;
class Term
{
    private:
        int num, denom, exp, order, trig;
    public:
        Term()
        {
            num=1;
            denom=1;
            exp=1;
            order = 0;
        }
        //Overloaded constructor
        Term(int n, int d, int e, int o, int t)
        {
            num=n;
            denom=d;
            exp=e;
            order=o;
            trig=t;
        }

        //simplifies fraction
        void simplify()
        {
            //decides num of iterations based off of smallest num
            int iter;
            if(num<=denom)
                iter=abs(denom)+1;
            else
                iter=abs(num)+1;
            //iterates until it finds a common factor
            for(int i = 1; i<iter; i++)
            {
                if(((num%i)==0) && ((denom%i)==0))
                {
                    //simplifies fraction once and restarts loop again to find more factors
                    num/=i;
                    denom/=i;
                    i=1;
                    if(num<=denom)
                        iter=abs(num)+1;
                    else
                        iter=abs(denom)+1;
                }
            }
            if(num == 0)
                denom=1;
        }
        
        //Integrates given term
        void integrate()
        {
            if(trig!=-1) //If trig
            {
                if(trig==0)
                {
                    trig=1;
                    num*=-1;
                }
                else if(trig==1)
                {
                    trig=0;
                }
                if(exp!=1)
                {
                    if(num%exp==0)
                        num/=exp;
                    else
                        denom*=exp;
                }
                simplify();
                if(num == 0)
                {
                    denom=1;
                }
                return;
            }
            //If not trig
            exp++;
            if(num % exp == 0)
                num/=exp;
            else
                denom*=exp;
            simplify();
            if(num == 0)
                exp=0;
        }

        //Overloads +
        Term& operator+(Term& rhs)
        {
            num = (num * rhs.denom) + (rhs.num * denom);
            denom = (denom * rhs.denom);
            return *this;
        }
        
        //Overloads !=
        bool operator!=(const Term& lhs)
        {
            if(trig != -1)
                return false;
            return ((exp == lhs.exp) && (num != lhs.num));
        }

        //Overloads <
        bool operator<(const Term& lhs)
        {
            if(trig == -1 && lhs.trig != -1)
                return false;
            if(trig != -1)
                return true;
            return (exp < lhs.exp);
        }

        //Overloads ==
        bool operator==(const Term& lhs)
        {
            if(trig != -1)
                return false;
            return ((exp == lhs.exp) && (num == lhs.num));
        }
        
        //prints value
        ostringstream print()
        {
            ostringstream out;
            integrate();
            //if(obj.order != 0)
            if(true)
            {
                if((num*denom) < 0)
                {
                    if(num < 0)
                    {
                        out << " - ";
                        num*=-1;
                    }
                    else
                    {
                        out << " - ";
                        denom*=-1;
                    }
                }
                else if(num < 0)
                {
                    out << " + ";
                    num*=-1;
                    denom*=-1;
                }
                else
                    out << " + ";
            }
            if(denom == 1)
            {
                if(num != 1)
                    out << num;
            }
            else
            {
                out << "(" << num << "/" << denom << ")";
            }
            
            //If not trig
            if(trig==-1)
            {
                if(exp != 0)
                {
                    out << "x";
                    if(exp != 1)
                        out << "^" << exp;
                }
            }
            else //If trig
            {
                if(trig==0)
                    out << "sin ";
                else
                    out << "cos ";
                if(exp!=1)
                    out << exp;
                out << "x";
            }
            return out;
        }
};

#endif