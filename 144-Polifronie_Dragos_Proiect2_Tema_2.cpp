#include <iostream>

using namespace std;

class Nod {
friend std::ostream& operator<< (std::ostream &os, const Nod &Nod);
friend std::istream &operator>>(std::istream &is,  Nod &nod);
protected:
    int info;
    Nod * next;
public:
    void set_data_value(int d){info= d;
    }
    int get_data_value(){
    return info;}
    void set_next(Nod *nod){
    next = nod;}
    virtual Nod * get_next(){
    return next;}
    Nod();
    Nod(int d);
    Nod(const Nod &source);
    virtual ~Nod();
    Nod& operator=(const Nod &n);

};

std::ostream& operator<< (std::ostream &out,const Nod &Nod)
{

    out << "Nodul" << Nod.info << ", cu next: " << Nod.next << " " ;

    return out;
}
std::istream &operator>>(std::istream &is, Nod &nod){

  is >> nod.info;
  return is;}
Nod& Nod::operator= (const Nod &n)
{   if(this == &n){
        return *this;}

    this->info = n.info;
    delete this->next;
    this->next = new Nod();
    this->next = n.next;
    cout<<" OVERLOAD ";
    return *this;
}
Nod::Nod(){
cout<<" constructor fara argm ";
info = 0;
next = NULL;}
Nod::Nod(int d){
cout << " Constructor parametrizat ";
info = d;
}
Nod::~Nod(){


    cout <<" DESTRUCTOR ";
}
Nod::Nod(const Nod &source){

 //   delete this->next;
   // this -> next = new Nod;
    this->next = source.next;
    this->info = source.info;
    cout<< " Copy constructor ";}




class Nod_dublu : public Nod {
friend istream& operator>>(istream &in, Nod_dublu &n)
{   n.ante = NULL;
    n.set_next(NULL);
    int data;
    in >> data;
    n.set_data_value(data);
    return in;
}
friend ostream& operator<<(ostream &out, Nod_dublu &n)
        {
            out<<"Nodul: "<<" Cu atributele:"<< n.get_data_value()<<" "<<n.get_next();
            return out;
        }

friend class LDI;
protected:
    Nod * ante;
public:
    void set_ante(Nod *nod){
    ante = nod;}
    Nod *get_ante(){
    return ante;}
    Nod_dublu() : Nod(){
    ante = NULL;}
    Nod_dublu(int d)
        : Nod(d){
            }
    Nod_dublu(const Nod_dublu &source): Nod(source)
        {
            this->ante = source.ante;
        }
    ~Nod_dublu(){
    cout<<"destructor dublu";

}
    Nod_dublu &operator= (Nod_dublu n)
        {
            delete ante;
            delete this -> get_next();
            this -> set_data_value(n.get_data_value());
            ante = NULL;
            this -> set_next(NULL);
            return *this;
        }
};




class LDI{
friend ostream& operator<<(ostream &out, LDI &ld)
{
    Nod_dublu *n;
    n = ld.h1;
    while(n != NULL)
    {
        out << n -> get_data_value() << " ";
        n = dynamic_cast<Nod_dublu *>(n ->get_next());
    }
    return out;
}
friend istream& operator>>(istream &in, LDI &ld)
{



    int info, ind;
    in >> ld.lung;
    in >> info;
    ld.h1 = new Nod_dublu();
    ld.h1->set_data_value(info);
    ld.h2 = ld.h1;
    for(ind=1;ind<ld.lung;++ind)
    {
        in >> info;
        ld.AppendNode(info);
    }
    return in;
}
protected:
    Nod_dublu *h1;
    Nod_dublu *h2;
    int lung;
public:
    void set_varf1(Nod_dublu *vf){
    h1 = vf;}
    Nod_dublu *get_varf1(){return h1;}
    void set_varf2(Nod_dublu *vf){
    h2 = vf;}
    Nod_dublu *get_varf2(){return h2;}
    void set_lung_LDI(int x){lung =x;}
    int get_lung_LDI(){return lung;}

    LDI(){
    lung = 0;
    h1 = new Nod_dublu();
    h2 = h1;}
    LDI(int data_varf){
    lung = 1;
    h1 = new Nod_dublu();
    h1->set_data_value(data_varf);
    h2 = h1;}
    LDI(const LDI &ld){
    if(ld.lung==0){
        lung = 0;
        h1 = NULL;
        h2 = NULL;}
    else {
            lung = ld.lung;
            Nod_dublu *i,*j;
            h1 = new Nod_dublu();
            h1->set_data_value(ld.h1->get_data_value());
            h2 = h1;
            i = ld.h1;
            i = dynamic_cast<Nod_dublu *>(i->get_next());
            while(i != NULL)
            {
                j = new Nod_dublu();
                h2 ->set_next(j);
                j = h2;
                h2 = dynamic_cast<Nod_dublu *>(h2-> get_next());
                h2 -> set_data_value(i -> get_data_value());
                h2 -> set_ante(j);
                i = dynamic_cast<Nod_dublu *>(i -> get_next());
            }
        }
            cout<<"LDI COPY ......"<<endl;}
    virtual ~LDI()
{

        Nod_dublu *nd;
        nd = h2;
        while(nd != NULL && lung > 0)
         {
            lung = lung-1;
            Nod_dublu *aux = nd;
            nd = dynamic_cast<Nod_dublu *>(nd->get_ante());
            delete aux;
            }
       cout<<"TEST 9   ??"<<endl; }
    virtual void AppendNode(int i, bool mare = false)
{
        Nod_dublu *x = new Nod_dublu;
        if(lung == 0)
        {h1 = x;}

        h2 -> set_next(x);
        x = h2;
        h2 = dynamic_cast<Nod_dublu *>(h2 ->get_next());
        h2 ->set_data_value(i);
        h2 -> set_ante(x);
        h2-> set_next(NULL);
            if(mare)
            lung++;
        cout<<"nod "<< i << "alipit"<<endl;}
        virtual void Delete_node(Nod_dublu * p){
            Nod_dublu * pointer1 = h1;
          while (dynamic_cast<Nod_dublu  *>(pointer1 -> get_next()) != p)
          {
            pointer1 = dynamic_cast<Nod_dublu  *>(pointer1 -> get_next());
          }
          pointer1->set_next(p->get_next());
          Nod_dublu * pointer2 = h2;
          while (dynamic_cast<Nod_dublu  *>(pointer1 -> get_ante()) != p)
          {
            pointer1 = dynamic_cast<Nod_dublu  *>(pointer1 -> get_ante());
          }
          pointer2->set_ante(p->get_ante());
          delete p;

        }


};

class CircularList : public LDI {
friend ostream &operator<<(ostream &out, CircularList &CLL)
{
    Nod_dublu *n;
    n = CLL.get_varf1();
    out << n -> get_data_value() << " ";
    n = dynamic_cast<Nod_dublu *>(n -> get_next());
    while(n != CLL.get_varf1())
    {  out << n -> get_data_value() << " ";
        n = dynamic_cast<Nod_dublu *>(n -> get_next());
    }
    return out;
}
friend istream &operator>>(istream &in, CircularList &CLL)
    {
        CLL.set_lung_LDI(0);
        Nod_dublu *i,*j;
        i = CLL.get_varf1();
        j = i;
        j = dynamic_cast<Nod_dublu *>(i -> get_next());
        delete i;
        while(j != NULL)
        {
            i = j;
            j = dynamic_cast<Nod_dublu *>(i -> get_next());
            delete i;
        }

        int data, mr;
        in >> data;
        CLL.set_lung_LDI(data);
        in >> data;
        CLL.set_varf1(new Nod_dublu(data));
        CLL.set_varf1(CLL.get_varf1());
        CLL.get_varf2() -> set_next(CLL.get_varf1());
        CLL.get_varf2() -> set_ante(CLL.get_varf1());
        for(mr=1;mr<CLL.get_lung_LDI();++mr)
        {
            in >> data;
           CLL.AppendNode(data);
        }}

    public:
    CircularList():LDI(){}
    CircularList(int data):LDI(data){
    get_varf2() -> set_next(get_varf1());
    get_varf2() -> set_ante(get_varf2());}
    ~CircularList(){ /* ?? Nu stiu daca este ok asa, dar n-am avut idei */};
    void AppendNode(int i, bool mare = false){
    LDI::AppendNode(i, mare);
    Nod_dublu *vf1, *vf2;
    vf1 = get_varf1();
    vf2=get_varf2();
    vf1->set_ante(vf2);
    vf2->set_next(vf1);}
    void Delete_node(Nod_dublu *p)  { LDI::Delete_node(p);
    }
    int operator[] (int numar)
    {
        int i;
        Nod_dublu *j;
        j = get_varf1();
        for(i= 1; i < numar; i++)
            j = dynamic_cast<Nod_dublu *>(j -> get_next());
        return j-> get_data_value();
    }
};

void afis(){

 LDI l;
 cin>>l;
 cout<<l;}
int Josephus(int n, int p){
{
    if (n == 1)
        return 1;
    else
        return (Josephus(n - 1, p) + p-1) % n + 1;
}}
int main()
{  /* Nod * k = new Nod();
    Nod * p = new Nod();
    p->set_data_value(24);
    k -> set_data_value(22);
    p->set_next(k);
    cout<<k->get_data_value()<<" "<<k->get_next()<<" "<<k<<endl;
  //  cout<<p->get_data_value()<<" "<<p->get_next()<<" "<<p<<endl;


    Nod l;
    l.set_data_value(22);
    Nod s;
    l.set_next(k);
    Nod * b = new Nod(4, NULL);
    cout << b <<" "<<b->get_data_value()<<" " << b->get_next() << endl;;

    Nod_dublu f = Nod_dublu(k, 20, b);
  //  cout << f.get_ante() << " "<<f.get_next()<< " "<<f.get_data_value();
    Nod_dublu z=f;
    cout << z << endl;
    s=l;
    cout<<"DA BINE?   "<<p->get_data_value()<<" "<<p->get_next()<<" "<<p<<endl;

    cout << z.get_ante() <<"DA MERGE"<< z.get_data_value();

*/ //afis();
    CircularList lc;
    int k, nr, j, i;
    int op;
    do {
        cout<<"\n Selecteaza optiunea dorita:"<<endl;
        cout<<"1. Creare lista noua"<<endl;
        cout << "2. Priveste jocul"<<endl;
        cout<<"3. Afla direct castigatorul!"<<endl;
        cout<<"EXIT. Apasati 0 pentru a iesi"<<endl;
        cin>>op;
        switch (op){
        case 0:
            break;
        case 1:
            cout<<"Numarul de noduri:";
            cin>>lc;
            cout<<lc<<endl;
            cout<<lc[2];
            break;
        case 2:
            cout<<"Introdu numarul k (numarul de pasi): ";
            cin >> k;
            cout << endl;
            break;
        case 3:
            cout<<"Introdu numarul k (numarul de pasi): ";
            cin >> k;
            cout << endl;
             nr = lc.get_lung_LDI();
             i = Josephus(nr , k);
             cout << "castigatorul este: "<<lc[i];
            break;



        default:
            cout << "Optiune invalida!" << endl;}

        }while (op!=0);


    return 0;
}
