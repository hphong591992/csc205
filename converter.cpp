#include <iostream>
#include <algorithm>
#include <cmath>
#include <string>
using namespace std;

bool valid(string a)
{
     return true;          
}
int main ()
{
    bool stop = false;
    while (!stop)
    {
          char command; 
          string number;
          string sign;
          string exponent;
          string mantissa;
          string ans;
          string res;
          int e,m,ll,c;
          cout << "1. Convert decimal to IEEE 754 single precision. " << endl;
          cout << "2. Convert decimal to IEEE 754 double precision. " << endl;
          cout << "3. Convert IEEE 754 single precision to decimal. " << endl;
          cout << "4. Convert IEEE 754 double precision to decimal. " << endl;
          cout << "5. Exit." << endl;
          cout << "Please enter one of the options listed above: ";
          cin >> command;
          if (command=='1'||command=='2')
          {
             cout << "Enter a decimal number: ";
             cin >> number;
             if (!valid(number))
             {
                cout << "Wrong input. " << endl;
                continue;
             }
             if (number[0]=='-')
                sign = "1";
             else
                 sign = "0";
             if (command=='1')
             {
                e = 8;
                m = 23;
                ll = 32;
                c = 127;
             }
             else
             {
                 e = 11;
                 m = 51;
                 ll = 64;
                 c = 1023;
             }
                string temp;
                if (number[0]=='-')
                   temp = number.substr(1,number.find_first_of('.'));
                else                    
                   temp = number.substr(0,number.find_first_of('.'));
                int exp = atoi(temp.c_str());
                bool start = false;
                for (int i=ll-1;i>=0;--i)
                {
                    int bit = (exp >> i) & 1;
                    if (bit==1)
                       start = true;
                    if (start)
                       res += (char) (bit+48);
                }
//                cout << res << endl;
                /// CUT THE INTEGER PART
                int l = res.length();
                double rest = abs(atof (number.c_str()));
                rest -= (double) exp;
                int count = 0;
                double t = 1.0;
                while (rest>0)
                {
                      t /= 2.0;
                      if (rest>=t)
                      {
                         res = res + "1";
                         rest -= t;
                      }
                      else
                          res = res + "0";                          
                      count++;
                      if (count+l==ll)
                         break;                      
                }                
    //            cout << res << endl;
                exp = (l-1) + c;
  //              cout << exp << endl;
                for (int i=e-1;i>=0;--i)
                {
                    int bit = (exp >> i) & 1;
                    exponent += (char) (bit+48);
                }
//                cout << exponent << endl;
                mantissa = res.substr(1);
                while (mantissa.length()<m)
                      mantissa += "0";
                ans = sign + exponent + mantissa;                           
          }
          else if (command=='3'||command=='4')
          {
          }
          else if (command=='5')
               break;
          else
              cout << "Wrong input. " << endl;
          cout << endl;
          if (command=='1')
          {
             cout << "SIGN   EXPONENT           MANTISSA" << endl;
             cout << sign << "      " << exponent << "           " << mantissa << endl;
          }
          else if (command=='2')
          {
             cout << "SIGN   EXPONENT           MANTISSA" << endl;
             cout << sign << "      " << exponent << "        " << mantissa << endl;
          }               
          cout << endl;
    }
    return 0;
}
