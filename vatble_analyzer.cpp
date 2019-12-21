#include<iostream>

using namespace std;

class Base
{
    public:
        virtual void fun()                      // function address 1000
        {
            cout<<"\nInside Base::fun()";
        }
        virtual void gun()                      // function address 2000
        {
            cout<<"\nInside Base::gun()";
        }
        virtual void sun()
        {
            cout<<"\nInside Base::sun()";       // function address 3000
        }
};

class Derived:public Base
{
    public:
        void fun()
        {
            cout<<"\nInside Derived::fun()";    // function address 4000
        }
        void gun()
        {
            cout<<"\nInside Derived::gun()";    // function address 5000
        }
};

int main()
{
    Base bobj;                      // object of Base class

    Base *bptr=&bobj;               // pointer of Base class pointing to object of Base class

    int *ptr=(int *)bptr;           // integer pointer which gets the address of vptr which is in first four bytes of Base class object

    int *vptr=(int *)*ptr;          // integer pointer which points to memory allocated to the array of virtual function addresses i.e. VTABLE

    void (*fp)();                   // function pointer which will points to the function having prototype void function_name()

    fp=(void(*)())(*vptr);          // function pointer currently holds the address of first function in VTABLE i.e. Base::fun()
    fp();    //1000                 // call to the Base::fun()

    fp=(void(*)())(*(vptr+1));      // function pointer currently holds the address of first function in VTABLE i.e. Base::gun()
    fp();    //2000                 // call to the Base::gun()

    fp=(void(*)())(*(vptr+2));      // function pointer currently holds the address of first function in VTABLE i.e. Base::sun()
    fp();    //3000                 // call to the Base::sun()

    bptr=new Derived;               // Base class pointer points to Derived class object i.e. Up casting hence overriding will take place
                                    // After overriding in VTABLE  at 0 th index which was holding the address of Base::fun() will get replaced with address of Derived::fun()
                                    // After overriding in VTABLE  at 1 st index which was holding the address of Base::gun() will get replaced with address of Derived::gun()
                                    // After overriding in VTABLE  at 2 nd index which was holding the address of Base::sun() will will not override because of there no definition of gun() in Derived class

    ptr=(int *)bptr;                // integer pointer which gets the address of vptr which is in first four bytes of Derived class object
    vptr=(int *)*ptr;               // integer pointer which points to memory allocated to the array of  virtual function addresses which were overred previously.e. VTABLE after overriding

    fp=(void(*)())(*vptr);           // function pointer currently holds the address of first function in VTABLE i.e. Derived::fun()(overriding)
    fp();     //4000                 // call to the Derived::fun()

    fp=(void(*)())(*(vptr+1));       // function pointer currently holds the address of first function in VTABLE i.e. Derived::gun()(overriding)
    fp();     //5000                 // call to the Derived::gun()

    fp=(void(*)())(*(vptr+2));       // function pointer currently holds the address of first function in VTABLE i.e. Derived::sun()
    fp();     //3000                 // call to the Base::sun()

    return 0;
}
