#include <iostream>
#include <algorithm>
#include <cmath>
#include <string>
using namespace std;

bool valid(string a)
{
     int c1 = 0;
     if (a[0]=='-')
        a = a.substr(1);
     cout << a << endl;
     for (int i=0;i<a.length();++i)
     {
         int c = (int) (a[i]) -48;
         if (a[i]=='.')
         {
            c1++;
            if (c1>1)
               return false;
               continue;
         }
         if (c<0||c>9)
            return false;
     }
     cout << endl;
     return true; 
}
int main ()
{
    bool stop = false;
    while (!stop)
    {
          char command; 
          string number;
          string sign = "";
          string exponent = "";
          string mantissa = "";
          string ans = "";
          string res = "";
          int e,m,ll,c, maxlength;
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
             if (command=='1')
             {
                e = 8;
                m = 23;
                ll = 32;
                c = 127;
                maxlength = 38;
             }
             else
             {
                 e = 11;
                 m = 51;
                 ll = 64;
                 c = 1023;
                 maxlength = 308;
             }              
             if (!valid(number))
             {
                sign = "0"; 
                for (int i=0;i<e;++i)
                    exponent += "1";
                exponent += "1";
                for (int i=1;i<m;++i)
                    mantissa += "1"; 
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
                continue;
             }
             if (number[0]=='-')
                sign = "1";
             else
                 sign = "0";            
                string temp;
                if (number[0]=='-')
                   temp = number.substr(1,number.find_first_of('.'));
                else                    
                   temp = number.substr(0,number.find_first_of('.'));
                if (number.length()>maxlength)
                {
                   for (int i=0;i<e;++i)
                       exponent += '1';
                   for (int i=0;i<m;++i)
                       mantissa += '0';
                   // INF CASE
                }
                else
                {
                long long exp = atoi(temp.c_str());
//                cout << "Exponent: " << exp << endl;
                bool start = false;
                for (int i=ll-1;i>=0;--i)
                {
                    int bit = (exp >> i) & 1;
                    if (bit==1)
                       start = true;
                    if (start)
                       res += (char) (bit+48);
                }
//               cout << res << endl;
                /// CUT THE INTEGER PART
                int l = res.length();
                double rest = abs(atof (number.c_str()));
                rest -= (double) exp;
                int count = 0;
                double t = 1.0;
//                cout << rest << endl;
//                cout << res << endl;                 
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
                      {
                         if (rest>0)                            
                         break;                                               
                      }
                }                
//                cout << res << endl;
    //            cout << res << endl;
                exp = (l-1) + c;
  //              cout << exp << endl;
                for (int i=e-1;i>=0;--i)
                {
                    int bit = (exp >> i) & 1;
                    exponent += (char) (bit+48);
                }                
//                cout << exponent << endl;
                if (res.length()==0)
                {
                   exponent = "";
                   for (int i=0;i<e;++i)                
                       exponent += "0";
                   for (int i=0;i<m;++i)
                       mantissa += "0";
                }
                else
                    mantissa = res.substr(1);                
                while (mantissa.length()<m)
                      mantissa += "0";
                if (mantissa.length()>m)
                   mantissa = mantissa.substr(0,m);
                ans = sign + exponent + mantissa;    
                }                       
          }
          else if (command=='3'||command=='4')
          {
               string sign;
               string exponent;
               string mantissa;
               double ans = 1.0;
               cout << "Enter the sign: ";
               cin >> sign;
               cout << "Enter the exponent: ";
               cin >> exponent;
               cout << "Enter the mantissa: ";
               cin >> mantissa;
             if (command=='3')
             {
                e = 8;
                m = 23;
                ll = 32;
                c = 127;
                maxlength = 38;
             }
             else 
             {
                 e = 11;
                 m = 51;
                 ll = 64;
                 c = 1023;
                 maxlength = 307;
             }
             bool digitcheck = true;
             for (int i=0;i<exponent.length();++i)
             if (exponent[i]!='0'&&exponent[i]!='1')
             {
                digitcheck = false;
                break;
             }                            
             for (int i=0;i<mantissa.length();++i)
             if (mantissa[i]!='0'&&mantissa[i]!='1')
             {
                digitcheck = false;
                break;
             }
             if (sign.length()!=1||exponent.length()!=e||mantissa.length()!=m||!digitcheck)
             {
                cout << endl;                                                                              
                cout << "WRONG INPUT. " << endl << endl;
                continue;
             }
             // CHECK INFINITY 
             bool check1 = true;
             bool check2 = true;
             for (int i=0;i<e;++i)
             if (exponent[i]=='0')
             {
                check1 = false;
                break;
             }                 
             for (int i=0;i<m;++i)
             if (mantissa[i]=='1')
             {
                check2 = false;
                break;
             }                                                                     
             if (check1&&check2)
             {
                cout << "INFINITY" << endl;
                continue;                                                                                   
             }
             else if (check1&&!check2)
             {
                  cout << "NaN" << endl;
                  continue;
             }
             else
             {
                 if (sign=="-")
                    ans *= -1;
                 // CONVERT EXPONENT TO DECIMAL
                 long long exp = 0;
                 long long t = 1;
                 if (exponent[e-1]=='1')
                    exp = 1;
                 else
                     exp = 0;
                 for (int i=e-2;i>=0;--i)
                 {
                     int temp = ((int) exponent[i])-48;
                     t *= 2;
                     exp += temp*t;
                 }
                 exp -= c;
                 cout << "Exponent = " << exp << endl;
                 cout << (exp << 1) * 1.0 << endl;
                 if (exp>0)                 
                 {
                    double tt = 1.0;
                    while (exp>0)
                    {
                          tt *= 2;
                          exp--;
                    }
                    ans *= tt;
                 }
                  //  ans *= (exp << 1)*1.0;                 
                 else if (exp<0)
                 {
                      double tt = 1.0;
                      while (exp<0)
                      {
                            tt /= 2;
                            exp ++;
                      }
                      ans *= tt;
                 }
                 // DONE WITH EXPONENT
                 double res = 0.0;
                 double tt = 1.0;
                 for (int i=0;i<m;++i)
                 {
                     tt /= 2;
                     if (mantissa[i]=='1')
                        res += tt;
                 }
//                 cout << "MANTISSA: " << res << endl;
                 ans *= (1+res);
                 cout << "Decimal conversion is: " << ans << endl;
             }
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
