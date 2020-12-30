#include<iostream>
#include<cmath>
#include<cstdlib>
#include<cstring>
 
using namespace std;
 
//Kiểm tra số nguyên tố
bool CheckIsPrime(long int num)
{
    if(num < 2)
        return false;
    long int i = 2;
    while(i <= num/2)
    {
        if(!(num % i))
            return false;
        i++;
    }
    return true;
}
 
// Tìm n = p*q
long int Multiply(long int num1, long int num2)
{
    return num1 * num2;
}
 
// Kiểm tra nguyên tố cùng nhau
bool CheckCoPrime (long int num1, long int num2)
{
    long int lowest, r, a, b;
    bool coprime;
    if (num1 > num2)
    {
        a = num1;
        b = num2;
    }
    else
    {
        a = num2;
        b = num1;
    }
    while(b != 0)
    {
        r = a % b;
        a = b;
        b = r;
    }
    if(a == 1)
        coprime = true;
    else
        coprime = false;
    return coprime;
}
 
// Tìm số e là nguyên tố cùng nhau với phi_n
long int FindE(long int phi_n)
{
    long int e = 0;
    do
    {
        cout << "Choose an integer number e (e must be coprime of phi_n): ";
        cin >> e;
    }
    while(!CheckCoPrime(phi_n,e));
    return e;
}
 
// Tìm số d là nghịch đảo của e
long int FindD(long int phi_n, long int e)
{
    long int a = phi_n, b = e;
    long int x1 = 0, x2 = 1, y1 = 1, y2 = 0, x, y, q, r;
//long int gcd = b;
    while (b!=0)
    {
        q = a/b;
        r = a% b;
        x = x2 - x1 * q;
        y = y2 - y1 * q;
        a = b ;
        b = r;
        x2 = x1;
        x1=x;
        y2 = y1;
        y1=y;
    }
    if (a != 1)
    {
        cout<< "Choose a suitable \"e\" value" <<endl;
        e = FindE(phi_n);
        FindD(phi_n, e);
    }
    x = x2;
    y = y2;
    if(y < 0)
        y = phi_n + y;
    return y;
 
}
 
// Thuật toán mã hóa và giải mã
long int Encrypt_Decrypt(long int t, long int e, long int n)
{
    long int rem;
    long int x = 1;
//if(e>0)x=t;
    while(e != 0)
    {
        rem = e % 2;
        e = e / 2;
        if(rem == 1)
            x = (x * t) % n;
        t = (t * t) % n;
 
    }
    return x;
 
}
 
// Hàm mã hóa
void EncDecStr(long int e, long int n)
{
    char *str = new char[1000];
    char *str1 = new char[1000];
    cout << "\nEnter a string: ";
    cin >> str;
    cout << "Encrypting using Public Key: " << endl;
    int i = 0;
    while(i != strlen(str))
    {
        str1[i] = Encrypt_Decrypt(str[i],e,n);
        i++;
    }
    cout << str1 << endl;
 
}
 
// Hàm mã hóa số thập phân
void EncDecNum(long int n1, long int n2)
{
    long int pn;
    cout << "\nEnter an integer number: ";
    cin >> pn;
    cout << Encrypt_Decrypt(pn, n1, n2) << endl;
}
void generate_key(long int &n, long int &e, long int &d)
{
    long int p, q, phi_n, pt, ct;
    do
    {
        cout<< "Enter a prime number: ";
        cin >> p;
    }
    while(!CheckIsPrime(p));
 
    do
    {
        cout << "Enter another prime number: ";
        cin >> q;
    }
    while (!CheckIsPrime(q));
    n = Multiply(p, q);
    cout << "n is " << n << endl;
    phi_n = Multiply(p-1, q-1);
    cout << "phi_n is " << phi_n << endl;
    e = FindE(phi_n);
    cout<< "e is " << e << endl;
    if(!e)
    {
        cout << "Choose two suitable prime number" << endl;
        exit(1);
    }
    d = FindD(phi_n,e);
    cout << "d is " << d << endl;
}
int main()
{
    cout << endl << endl << "##IMPLEMENTATION OF R.S.A ALGORITHM USING C++##" << endl << endl;
    long int n, e = 0, d;
    generate_key(n, e, d);
    cout << "Public Key : (" << e << "," << n << ")" <<endl;
    cout << "Private Key : (" << d <<"," << n <<")" <<endl;
    cout << endl << "Press 1: for encrypting numbers & 2: for encrypting string: ";
    int choice;
    cin >> choice;
    switch (choice)
    {
    case 1:
        EncDecNum(e, n);
        break;
    case 2:
        EncDecStr(e, n);
        break;
    default:
        cout<< "Wrong choice. Try again." <<endl;
        exit(1);
    }
    cout<<endl<< "Press 1: for decrypting numbers & 2: for decrypting string: ";
    cin>> choice;
    switch (choice)
    {
    case 1:
        EncDecNum(d, n);
        break;
    case 2:
        EncDecStr(d, n);
        break;
    default:
        cout<< "Wrong choice. Try again." << endl;
        exit(1);
    }
    return 0;
}