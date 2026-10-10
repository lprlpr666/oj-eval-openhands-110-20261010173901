#include <bits/stdc++.h>
using namespace std;

class Date {
private:
    int year, month, day; // 1-indexed month and day
    static bool isLeap(int y) {
        return (y % 400 == 0) || (y % 4 == 0 && y % 100 != 0);
    }
    static int monthDays(int y, int m) {
        static const int mdays[] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
        if (m == 2 && isLeap(y)) return 29;
        return mdays[m];
    }
    // days since 1900-01-01 (day 0)
    static long long toOrdinal(int y, int m, int d) {
        long long days = 0;
        for (int yy = 1900; yy < y; ++yy) {
            days += isLeap(yy) ? 366 : 365;
        }
        for (int mm = 1; mm < m; ++mm) {
            days += monthDays(y, mm);
        }
        days += d - 1; // offset from first day
        return days;
    }
    static void fromOrdinal(long long ord, int &y, int &m, int &d) {
        y = 1900;
        while (true) {
            int yearDays = isLeap(y) ? 366 : 365;
            if (ord >= yearDays) { ord -= yearDays; ++y; }
            else break;
        }
        m = 1;
        while (true) {
            int md = monthDays(y, m);
            if (ord >= md) { ord -= md; ++m; }
            else break;
        }
        d = (int)ord + 1;
    }
    long long ordinal() const { return toOrdinal(year, month, day); }
    void setFromOrdinal(long long ord) {
        fromOrdinal(ord, year, month, day);
    }
public:
    Date() : year(1900), month(1), day(1) {}
    Date(int y, int m, int d) {
        if (y < 1900 || y > 2030) { year=1900; month=1; day=1; return; }
        if (m < 1 || m > 12) { year=1900; month=1; day=1; return; }
        int md = monthDays(y,m);
        if (d < 1 || d > md) { year=1900; month=1; day=1; return; }
        year=y; month=m; day=d;
    }
    // prefix ++
    Date& operator++() { setFromOrdinal(ordinal()+1); return *this; }
    // postfix ++
    Date operator++(int) { Date tmp=*this; ++(*this); return tmp; }
    // prefix --
    Date& operator--() { setFromOrdinal(ordinal()-1); return *this; }
    // postfix --
    Date operator--(int) { Date tmp=*this; --(*this); return tmp; }
    // add days
    Date operator+(int days) const { Date res=*this; res.setFromOrdinal(ordinal()+days); return res; }
    Date operator-(int days) const { Date res=*this; res.setFromOrdinal(ordinal()-days); return res; }
    // difference between dates (absolute)
    long long operator-(const Date& other) const { return llabs(ordinal() - other.ordinal()); }
    bool operator<(const Date& other) const { return ordinal() < other.ordinal(); }
    // output
    friend ostream& operator<<(ostream& os, const Date& dt) {
        os << dt.year << '-' << dt.month << '-' << dt.day;
        return os;
    }
    void out() const { cout << year << '-' << month << '-' << day << '\n'; }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int op; if(!(cin>>op)) return 0;
    int yy,mm,dd;
    if(op==1||op==0){
        Date d0; Date d1(2000,2,29); Date d2(1900,2,29);
        cout<<d0<<"\n"<<d1<<"\n"<<d2<<"\n";
    }
    if(op==2||op==0){
        cin>>yy>>mm>>dd; Date d0(yy,mm,dd);
        for(int i=0;i<5;++i) cout<<++d0<<"\n";
        for(int i=0;i<5;++i) cout<<d0++<<"\n";
        for(int i=0;i<5;++i) cout<<d0--<<"\n";
        for(int i=0;i<2;++i) cout<<--d0<<"\n";
        cout<<d0<<"\n";
    }
    if(op==3||op==0){
        cin>>yy>>mm>>dd; Date d0(yy,mm,dd);
        cout<<d0+100<<"\n";
        cout<<d0-1000<<"\n";
    }
    if(op==4||op==0){
        cin>>yy>>mm>>dd; Date d0(yy,mm,dd);
        Date d1(2020,12,21);
        cout<<(d0<d1)<<"\n";
    }
    if(op==5||op==0){
        cin>>yy>>mm>>dd; Date d0(yy,mm,dd);
        Date d1(1912,6,23);
        cout<<d0-d1<<"\n";
    }
    return 0;
}
