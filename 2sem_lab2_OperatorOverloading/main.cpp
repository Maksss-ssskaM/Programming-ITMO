#include<iostream>
#include<fstream>
#include<string.h>
using namespace std;
class Polynom
{
public:
    int N; //������� ��������
    double *kf; //��������� �� ����������� ��� i-� �������

    Polynom();//�����������
    Polynom(int N_);

    ~Polynom();//����������

    Polynom(const Polynom &);//�����������

    Polynom operator=(const Polynom &);//�������� ������������

    Polynom operator+=(const Polynom &);//�������� ��������

    Polynom operator- (const Polynom &);//�������� �������� ������

    Polynom operator-=(const Polynom &);//�������� ���������

    Polynom operator*=(const Polynom &);//�������� ���������

    Polynom operator/=(const Polynom &);//�������� �������

    int operator[] (const int i);//�������� ��������������

    bool operator== (Polynom&); //�������� ���������

    friend ostream &operator<< (ostream &s, const Polynom &c); // ������������� �������� ������

    friend istream &operator>> (istream &s, Polynom &c); // ������������� �������� �����


};

Polynom::Polynom()                                                         //�����������
{
    kf = NULL;
}

Polynom::Polynom(int N_)
{
    int i;
    N = N_;

    kf = new double[N + 1];
    for (i = 0; i <= N; i++)
    {
        kf[i] = 0;
    }
}

Polynom::~Polynom()                                                        //����������
{
    delete[]kf;
}

Polynom::Polynom(const Polynom &f)                                        //�����������
{
    N = f.N;
    kf = new double[N + 1];
    for (int i = 0; i <= N; i++)
    {
        kf[i] = f.kf[i];
    }
}

Polynom Polynom::operator= (const Polynom &t)                             //�������� ������������
{
    if(this!=&t)
    {
        delete[] kf;
        N = t.N;
        kf = new double[N + 1];
        for (int i = 0; i <= N; i++)
        {
            kf[i] = t.kf[i];
        }
    }
    return *this;
}

Polynom Polynom::operator+= (const Polynom &t)                           //�������� ��������
{
    int i;
    //A ������ B
    if (N >= t.N)
    {
        Polynom Z=*this;
        for (i = 0; i <= N; i++)
        {
            Z.kf[i] = kf[i] + t.kf[i];
        }
        return Z;
    }
    //A ������ B
    else
    {
        Polynom Z=t;
        for (i = 0; i <= N; i++)
        {
            Z.kf[i] = t.kf[i] + kf[i];
        }
        return Z;
    }
}

Polynom Polynom::operator- (const Polynom &t)                           //�������� �������� ������
{
    int i;
    Polynom Z = *this;
    for (i = 0; i <= N; i++)
    {
        Z.kf[i] = -Z.kf[i];
    }
    return Z;
}

int Polynom::operator[] (int i)                                         //�������� ��������������
{
    int a = -1;
    if(N >= 0 && i <= N)
    {
        return kf[i];
    }
    else
    {
        return a;
    }
}

Polynom Polynom::operator-=(const Polynom &t)                           //�������� ���������
{
    int i;
    if (N >= t.N)//� ������ B
    {
        Polynom Z = *this;
        for (i = 0; i <= t.N; i++)
        {
            Z.kf[i] = kf[i] - t.kf[i];
        }
        return Z;
    }
    else//B ������ A
    {
        Polynom Z(t.N);
        for (i = 0; i <= N; i++)
        {
            Z.kf[i] = -t.kf[i] + kf[i];
        }
        for (i = N + 1; i <= t.N; i++)
        {
            Z.kf[i] = -t.kf[i];
        }
        return Z;
    }
}

bool Polynom::operator== (Polynom&t)                                    //�������� ���������
{
    return(t.N==N);
}

Polynom Polynom::operator*=(const Polynom &t)                           //�������� ���������
{
    int i, j, s = 0;
    Polynom Y(N + t.N);
    for (i = 0; i <= N; i++)
    {
        for (j = 0; j <= t.N; j++)
        {
            Y.kf[i + j] += kf[i] * t.kf[j];
        }
    }
    return Y;
}

Polynom Polynom::operator/= (const Polynom &o)
{

    bool a = true;

    Polynom R;
    Polynom o1;
    Polynom o2;
    Polynom o3;

    R.N = N - o.N;
    R.kf = new double[R.N + 1];
    memset(R.kf, 0, (R.N + 1)*sizeof(double));

    o1.N = N;
    o1.kf = new double[N + 1];
    for (int i = N; i >= 0; i--)
    {
        o1.kf[i] = kf[i];
    }
    o2.N = o.N;
    o2.kf = new double[o.N + 1];
    for (int i = o.N; i >= 0; i--)
    {
        o2.kf[i] = o.kf[i];
    }
    o3.N = o1.N;
    o3.kf = new double[o1.N + 1];

    double mnoj;
    int k = 0;
    int i, j;
    while (a)
    {

        for (int i = o.N; i >= 0; i--)
        {
            o3.kf[i] = o.kf[i];
        }

        if (o2.N < o1.N)
        {
            for (i = o1.N,j = o2.N; i >= 0; i--, j--)
            if (j < 0)
            {
                o3.kf[i] = 0;
            }
            else
            {
                o3.kf[i] = o2.kf[j];
            }
        }
        mnoj = o1.kf[o1.N] / o3[o1.N];

        R.kf[R.N - k] = mnoj;
        k++;

        for (int i = 0; i <= o1.N; i++)
        {
            o3.kf[i] *= mnoj;
        }

        for (int i = 0; i <= o1.N; i++)
        {
            o1.kf[i] -= o3.kf[i];
        }

        o1.N--;
        if (o2.N > o1.N)
        {
            a = false;
        }

    }
    cout << "������� �� �������: " << o1 << endl;
    cout << "���������: ";
    return R;
}
istream &operator>>(istream &s, Polynom &c)// ������������� �������� �����
{
    int i;
    for (i = 0; i <= c.N; i++)
    {
        s >> c.kf[i];
    }
    return s;
}

ostream &operator<<(ostream &s, const Polynom &c)// ������������� �������� ������
{
    int i, n=0;
    for (i = 0; i <= c.N; i++)
    {
        if (c.kf[i] != 0)
        {
            n++;
        }
    }
    if (n != 0)
    {
        if (c.kf[0] != 0)
        {
            s << c.kf[0];
        }
        for (i = 1; i <= c.N; i++)
        {
            if (c.kf[i] < 0)
            {
                if(c.kf[i]!=-1)
                {
                    s << c.kf[i] << "X^" << i;
                }
                else
                {
                    s << " - " << "X^" << i;
                }
            }
            else
            {
                if (c.kf[i] != 0)
                {

                    if(c.kf[i] != 1)
                    {
                        s << " + " << c.kf[i] << "X^" << i;
                    }
                    else
                    {
                        s << " + " << "X^" << i;
                    }
                }
            }
        }
        s << '\n';
    }
    else
    {
        s << 0;
    }
    return s;
}
int main()
{
    setlocale(LC_ALL, "");
    int n, m, i;

    cout << "������� ������� �������� A:" << '\n';
    cin >> n;

    cout << "������� ������� �������� B:" << '\n';
    cin >> m;

    Polynom A(n), B(m), R;

    cout << "������� ����������� �������� A:" << '\n';
    cin >> A;

    cout << "������� ����������� �������� B:" << '\n';
    cin >> B;

    cout << "������� ������ �������� A:" << '\n';
    cin >> i;

    cout << "��������� �: " << A;
    cout << '\n';

    cout << "��������� B: " << B;
    cout << '\n';

    cout << "��������� R = A+B: " << (A += B);
    cout << '\n';

    cout << "��������� R = A-B: " << (A -= B);
    cout << '\n';

    cout << "��������� R =  A*B: " << (A *= B);
    cout << '\n';

    cout << "��������� R = A/B: " << (A /= B);
    cout << '\n';

    cout << "if(������ A == ������ B): " << (A == B) << '\n';
    cout << '\n';

    cout << "��������� R = -A: " << (A - B);
    cout << '\n';

    cout << "��������� R = A[i]: " << A[i];
    cout << '\n';

    A.~Polynom();

    system("pause");
}
